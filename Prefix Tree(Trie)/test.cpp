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
 

//	https://leetcode.com/problems/word-search-ii/
//	https://leetcode.com/problems/prefix-and-suffix-search/
//	https://leetcode.com/problems/unique-paths-iii/
//	https://leetcode.com/problems/unique-paths-ii/
//	https://leetcode.com/problems/unique-paths/
//	https://leetcode.com/problems/sudoku-solver/
//	https://github.com/Ahsanul-Ameen/Design_Problems_leetcode/tree/master/Prefix%20Tree(Trie)



class Solution {
	struct TrieNode {
	private:
		TrieNode **links;
		bool end;
		unsigned cnt;
	public:
		TrieNode() : end(false), cnt(0) {
			links = new TrieNode*[26];
			for(int i = 0; i < 26; ++i) links[i] = nullptr;
		}
		bool containsKey(const char& ch) const { return links[ch - 'a'] != nullptr; }
		TrieNode* getNode(const char& ch) const { return links[ch - 'a']; }
		void putNode(const char& ch, TrieNode* node = new TrieNode()) {
			links[ch - 'a'] = node;
		}
		void setEnd() { end = true; }
		bool isEnd() { return end; }
		void inc() { ++cnt; } 
		void dec() { assert(cnt > 0); --cnt; }
		~TrieNode() {
			for(int i = 0; i < 26; ++i) {
				if(links[i]) {
					delete links[i];
					links[i] = nullptr;
				}
			}
			delete []links;
			links = nullptr;
			end = false; //hahaVodox
		}
	} *root, *ptr;
	
	void insert(const string& word) {
		ptr = root;
		for(const auto& ch : word) {
			if(!ptr->containsKey(ch)) ptr->putNode(ch);
			ptr = ptr->getNode(ch);
		}
		ptr->setEnd();
	}
	
	/**
	bool search(const string& word) {
		ptr = root;
		for(const auto& ch : word) {
			if(ptr->containsKey(ch)) ptr = ptr->getNode(ch);
			else return false;
		}
		return ptr->isEnd();
	}
	*/
	vector< pair<int, int> > dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	
	bool isValid(const int& x, const int& y, const int& n, const int& m) const {
		return x >= 0 && x < n && y >= 0 && y < m;
	}
	
	void dfs(const auto& board, int x, int y, const int& n, const int& m, auto& vis, auto& res, string w = "") {
		if(!ptr->containsKey(board[x][y])) 
			return; // prunning, no need to move forward

		ptr = ptr->getNode(board[x][y]);
		TrieNode* state = ptr;
				
		vis[x][y] = true;
		w.push_back(board[x][y]);
		if(state->isEnd()) {
			res.emplace_back(w);
			//cout << endl << w << endl << endl;
		} 
		
		for(const auto &item : dirs) {
			int xx = x + item.first, yy = y + item.second;
			if(!isValid(xx, yy, n, m) || vis[xx][yy]) continue;
			dfs(board, xx, yy, n, m, vis, res, w);
			ptr = state;
		}
		w.pop_back();
		vis[x][y] = false;
		state = nullptr;
	}
public:
	Solution() : root(new TrieNode()), ptr(root) {}
	
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> res;
		int n = board.size(), m = board.back().size();
		vector<bool> sss(m, false);
		vector<vector<bool>> vis(n, sss);
		
		for(const auto & w : words) insert(w);
		
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				if(!vis[i][j]) {
					ptr = root;
					dfs(board, i, j, n, m, vis, res);
				}
			}
		}
		set<string> ser;
		for(auto& r : res) ser.insert(r);
		res.clear();
		for(auto& s : ser) res.emplace_back(s);
		return res;
    }
    
    ~Solution() {
		ptr = root;
		delete root;
		root = ptr = nullptr;
	}
};



int main(int argc, char** argv) {
    fast_io
    
    
    Solution s1;
    vector<vector<char>> board1 = {{'b','b','a','a','b','a'},
								   {'b','b','a','b','a','a'},
								   {'b','b','b','b','b','b'},
								   {'a','a','a','b','a','a'},
								   {'a','b','a','a','b','b'}};
    
	vector<string> words1 = {"abbbababaa"};
	
	cout << s1.findWords(board1, words1);
    
	Solution s;
	vector<vector<char>> board = {{'o', 'a', 'a', 'n'},
								  {'e', 't', 'a', 'e'},
								  {'i', 'h', 'k', 'r'}, 
								  {'i', 'f', 'l', 'v'}};
	vector<string> words({"oath", "pea", "eat", "rain", "rainman", "akrenaaoeiifht"});
	
	cout << s.findWords(board, words);
	
	
    return 0;
}





















