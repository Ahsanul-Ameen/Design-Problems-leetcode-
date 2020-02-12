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
		int linkCnt;
		bool end;
	public:
		TrieNode() : linkCnt(0), end(false) {
			links = new TrieNode*[26];
			for(int i = 0; i < 26; ++i) *(links + i) = nullptr;
		} 
		bool containsKey(const char& ch) const { return links[ch - 'a'] != nullptr; }
		TrieNode* getNode(const char& ch) const { return links[ch - 'a']; }
		void putNode(const char& ch, TrieNode* node) { links[ch - 'a'] = node; }
		void inc() { ++linkCnt; }
		void dec() { --linkCnt; }
		bool empty() const { return !linkCnt; }
		void setEnd() { end = true; }
		void unsetEnd() { end = false; }
		bool isEnd() const { return end; }
		
		~TrieNode() {
			for(int i = 0; i < 26; ++i) {
				if(links[i]) {
					delete links[i];
					links[i] = nullptr;
				}
			}
			delete []links;
			links = nullptr, end = false;
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
    void insert(string word) { /// O(word.length()), space O(w.len)
        ptr = rootNode;
        for(const auto& ch : word) {
			if(!ptr->containsKey(ch)) {
				ptr->putNode(ch, new TrieNode());
				ptr->inc();
			}
			ptr = ptr->getNode(ch);
		}
		ptr->setEnd();
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {	/// O(word), space = O(1)
        ptr = searchPrefix(word);
		return ptr != nullptr && ptr->isEnd();
    }
    
    /** removes a word from the trie if exists */
    /**
     * Explanation:
     * https://leetcode.com/problems/implement-trie-prefix-tree/discuss/156159/Java-solution-with-delete()-method 
    */
    void remove(string word) {	/// O(word.length()), space O(w.len), little bit slower
		if(!search(word)) return;
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
				if(ptr->empty()) nextDel = true; 
				ptr->unsetEnd();
			} else if(nextDel) {
				ptr->dec();
				delete ptr->getNode(ch);
				ptr->putNode(ch, nullptr);
				nextDel = ptr->empty() && !ptr->isEnd();
			}
		}
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

	for(const auto& str: {"abc", "abde", "worb", "xyz", "xyzb"}) trie.insert(str);
	
	trie.remove("xyzb");
	
	for(const auto& str: {"abc", "abde", "worb", "xyz", "xyzb"}) {
		cout << trie.search(str) << endl;
	}
	
	
	
	
    return 0;
}

