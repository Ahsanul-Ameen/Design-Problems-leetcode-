#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define     endl               "\n"
#define     fast_io            ios::sync_with_stdio(false); cin.tie(0);
#define     file_io            freopen("input.txt", "r", stdin);   \
                               freopen("output.txt", "w", stdout);
#define     all(x)             begin(x), end(x)
#define     debug(x)           cerr <<"Line "<< __LINE__ <<" : "<< #x " = "<< x <<endl;
 
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T, TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T> &t) { for(auto& i: t) os<<i<<" "; return os; }
 


class Trie {
	
	struct TrieNode {
	private:
		TrieNode** links;
		bool end;
	public:
		TrieNode() {
			links = new TrieNode*[26];
			for(int i = 0; i < 26; ++i) *(links + i) = nullptr;
			end = false;
		} 
		bool containsKey(const char& ch) const {
			return links[ch - 'a'] != nullptr;
		}
		TrieNode* getNode(const char& ch) const {
			return links[ch - 'a'];
		}
		void putNode(const char& ch, TrieNode* node) {
			links[ch - 'a'] = node;
		}
		void setEnd() { end = true; }
		bool isEnd() const { return end; }
		
		~TrieNode() {
			for(int i = 0; i < 26; ++i) {
				if(links[i]) {
					delete links[i];
					links[i] = nullptr;
				}
			}
			delete []links;
			links = nullptr;
			end = false;
		}
		
	}* rootNode, * ptr;
	
	TrieNode* searchPrefix(const string& prefix) {	//O(word), space(O(1))
		ptr = rootNode;
		for(const auto& ch: prefix) {
			if(!ptr->containsKey(ch)) return nullptr;
			ptr = ptr->getNode(ch);
		}
		return ptr;
	}
	
public:
    /** Initialize your data structure here. */
    Trie() {
		rootNode = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) { // O(word.length()), space O(w.len)
        ptr = rootNode;
        for(const auto& ch : word) {
			if(!ptr->containsKey(ch)) {
				ptr->putNode(ch, new TrieNode());
			}
			ptr = ptr->getNode(ch);
		}
		ptr->setEnd();
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {	//O(word), space = O(1)
        ptr = searchPrefix(word);
		return ptr != nullptr && ptr->isEnd();
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) { // O(word), space = O(1)
        return searchPrefix(prefix) != nullptr;
    }
    
    ~Trie() {
		ptr = rootNode;
		delete ptr;
		rootNode = ptr = nullptr;
	}
};

/**
 * You may assume that all inputs are consist of lowercase letters a-z.
 * All inputs are guaranteed to be non-empty strings.
 * 
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */



int main(int argc, char** argv) {
    fast_io
    
    
	Trie trie;

	trie.insert("apple");
	cout << trie.search("apple") << endl;   // returns true
	cout << trie.search("app") << endl;     // returns false
	cout << trie.startsWith("app") << endl; // returns true
	trie.insert("app");   
	cout << trie.search("app") << endl;     // returns true
	
	
    return 0;
}








//---------------------------------------------------------------------------------------------------------------------


// this implementation includes remove(word) 






#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define     endl               "\n"
#define     fast_io            ios::sync_with_stdio(false); cin.tie(0);
#define     file_io            freopen("input.txt", "r", stdin);   \
                               freopen("output.txt", "w", stdout);
#define     all(x)             begin(x), end(x)
#define     debug(x)           cerr <<"Line "<< __LINE__ <<" : "<< #x " = "<< x <<endl;
 
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T, TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T> &t) { for(auto& i: t) os<<i<<" "; return os; }
 


class Trie {
	
	struct TrieNode {
	private:
		TrieNode** links;
		int linkCount, endCount, wordCount;
	public:
		TrieNode() : linkCount(0), endCount(0), wordCount(0) {
			links = new TrieNode*[26];
			for(int i = 0; i < 26; ++i) *(links + i) = nullptr;
		} 
		bool containsKey(const char& ch) const { return links[ch - 'a'] != nullptr; }
		TrieNode* getNode(const char& ch) const { return links[ch - 'a']; }
		void putNode(const char& ch, TrieNode* node) { links[ch - 'a'] = node; }
		
		void incLink() { ++linkCount; }
		void decLink() { --linkCount; }
		bool emptyLink()const { return !linkCount; }
		
		void incEnd() { ++endCount; }
		void decEnd() { --endCount; }
		int getEnd() const { return endCount; }
		void setEnd(const int& e) { endCount = e; }
		
		int getWordCount() const { return wordCount; }
		void incWord() { ++wordCount; }
					
		~TrieNode() {
			for(int i = 0; i < 26; ++i) {
				if(links[i]) {
					delete links[i];
					links[i] = nullptr;
				}
			}
			delete []links;
			links = nullptr, linkCount = 0, endCount = 0, wordCount = 0;
		}
		
	} *rootNode, *ptr;
	
	TrieNode* searchPrefix(const string& prefix) {	//O(word), space(O(1))
		ptr = rootNode;
		for(const auto& ch: prefix) {
			if(!ptr->containsKey(ch)) return nullptr;
			ptr = ptr->getNode(ch);
		}
		return ptr;
	}
		
public:
    /** Initialize your data structure here. */
    Trie() : rootNode(new TrieNode()) {}
    
    /** Inserts a word into the trie. */
    void insert(const string& word) { /// O(word.length()), space O(w.len)
        ptr = rootNode;
        for(const auto& ch : word) {
			if(!ptr->containsKey(ch)) {
				ptr->putNode(ch, new TrieNode());
				/// we can increment links here in ptr
				ptr->incLink();
			}
			ptr->incWord();
			ptr = ptr->getNode(ch);
		}
		ptr->incWord();
		ptr->incEnd();
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string& prefix) { // O(prefix), space = O(1)
        return searchPrefix(prefix) != nullptr;
    }
    
    /** Returns if the word is in the trie. */
    bool search(const string& word) {	///O(word), space = O(1)
        ptr = searchPrefix(word);
		return ptr != nullptr && ptr->getEnd() > 0;
    }
    
    /** removes a word from the trie if exists 
     *  Disclaimer: removing a word does not preserve
     * 	the word count of each node
     *  so, after a
     * 	trie.remove("word")
     *  trie.wordCount("prefix") will be error prone
     *  Be Careful
     * */
    /**
     * Explanation:
     * https://leetcode.com/problems/implement-trie-prefix-tree/discuss/156159/Java-solution-with-delete()-method 
    */
    bool remove(const string& word) {	/// O(word.length()), space O(w.len), little bit slower
		if(!search(word)) return false;
		ptr = rootNode;
		stack< pair<TrieNode*, char> > sequence;
		for(const auto& ch : word) {
			sequence.push({ptr, ch});
			ptr = ptr->getNode(ch);
		}
		sequence.push({ptr, '$'});
		
		bool nextDel = false;
		while(!sequence.empty()) {
			ptr = sequence.top().first;
			char ch = sequence.top().second;
			sequence.pop();
			if(ch == '$') {
				ptr->setEnd(0);
				if(ptr->emptyLink()) nextDel = true; 
			} else if(nextDel) {
				ptr->decLink();
				delete ptr->getNode(ch);
				ptr->putNode(ch, nullptr);
				nextDel = ptr->emptyLink() && !ptr->getEnd();
				if(ptr == rootNode) return true;
			}
		}
		return false;
	}
	
	/** Returns no of words contain the prefix  */
	int countWords(string const& prefix) { /// O(prefix), space(O(prefix))
		ptr = searchPrefix(prefix);
		return ptr ? ptr->getWordCount() : 0;
	}
    
    ~Trie() {
		ptr = rootNode;
		delete ptr;
		rootNode = ptr = nullptr;
	}
};

/**
 * You may assume that all inputs are consist of lowercase letters a-z.
 * All inputs are guaranteed to be non-empty strings.
 * 
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */



int main(int argc, char** argv) {
    fast_io
    
    
	Trie trie;

	trie.insert("abc");
	trie.insert("abde");
	trie.insert("word");
	trie.insert("xyz");
	trie.insert("xyzb");
	cout << trie.search("xy") << endl; // false
	cout << trie.search("worb") << endl; // false
	
	cout << trie.search("abc") << endl; // true
	cout << trie.search("abde") << endl; // true
	cout << trie.search("word") << endl; // true
	cout << trie.search("xyz") << endl; // true
	cout << trie.search("xyzb") << endl; // true
	cout << endl << endl;
	trie.remove("xyzb");
	trie.remove("word");
	trie.remove("xyz");
	cout << trie.search("abc") << endl; // true
	cout << trie.search("abde") << endl; // true
	cout << trie.search("word") << endl; // false
	cout << trie.search("xyz") << endl; // false
	cout << trie.search("xyzb") << endl; // false
	
	cout << trie.countWords("a") << endl; // 2


	
    return 0;
}













