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
 


        
class Solution {
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
		void putNode(const char& ch, TrieNode* node = new TrieNode()) {
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
	
	void add(const string& word) {
		ptr = rootNode;
		for(const auto& ch: word) {
			if(!ptr->containsKey(ch)) ptr->putNode(ch, new TrieNode());
			ptr = ptr->getNode(ch);
		}
		ptr->setEnd();
	}
	
	string replace(const string& str) {
		string res;
		ptr = rootNode;
		bool flow = true;
		for(const auto& ch : str) {
			res.push_back(ch);
			if(flow && ptr->containsKey(ch)) {
				ptr = ptr->getNode(ch);
				if(ptr->isEnd()) return res;
			} else flow = false;
		} 
		return res;
	}

public:

	Solution() { rootNode = new TrieNode(); }

    string replaceWords(const vector<string>& dict, string sentence) {
        for(const auto& item: dict) this->add(item);
        string res = "", w = "";
        for(const auto& ch: sentence) {
			if(ch == ' ') {
				w = this->replace(w);
				w.push_back(ch);
				res += w;
				w.clear();
			} else {
				w.push_back(ch);
			}
		}
		w = this->replace(w);
		res += w;
		return res;
    }
    
    ~Solution() { 
		delete rootNode; 
		rootNode = ptr = nullptr;
	 }

};





int main(int argc, char** argv) {
    fast_io
    
    
	Solution sol;
	cout << sol.replaceWords({"a", "aa", "aaa", "aaaa"} , 
	"a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa") << endl;
	
	
	
    return 0;
}





















