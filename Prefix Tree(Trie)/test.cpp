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
 




class WordDictionary {
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
	bool dfs(TrieNode* current, const string& word, int indx) {
		if((size_t)indx == word.size()) 
			return current->isEnd();
		else if(word[indx] != '.') 
			return current->containsKey(word[indx]) && dfs(current->getNode(word[indx]), word, indx+1);
		else {
			for(int i = 0; i < 26; ++i) {
				if(current->containsKey('a'+i)) {
					bool flag = dfs(current->getNode('a' + i), word, indx+1);
					if(flag) return true;
				}
			}
			return false;
		}
	}
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        rootNode = new TrieNode();
        ptr = rootNode;
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        ptr = rootNode;
        for(const char& ch: word) {
			if(!ptr->containsKey(ch)) {
				ptr->putNode(ch, new TrieNode());
			}
			ptr = ptr->getNode(ch);
		}
		ptr->setEnd();
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
		return dfs(rootNode, word, 0);
    }
    ~WordDictionary() {
		ptr = rootNode;
		delete ptr;
		ptr = rootNode = nullptr;
	}
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */





int main(int argc, char** argv) {
    fast_io
    
    
	WordDictionary dict;
	dict.addWord("bad");
	dict.addWord("dad");
	dict.addWord("mad");
	cout << dict.search("pad") << endl; // 0
	cout << dict.search("bad") << endl; // 1
	cout << dict.search(".ad") << endl; // 1
	cout << dict.search("b..") << endl; // 1
	
	
    return 0;
}





















