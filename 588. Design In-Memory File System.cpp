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
 


//Approach #1 Using separate Directory and File List

class FileSystem {
	struct Dir {
		unordered_map<string, Dir*> dirs;
		unordered_map<string, string> files;
		~Dir() {
			for(auto& item: dirs) delete item.second, item.second = nullptr;
			dirs.clear(), files.clear();
		}
	} *root;
	
	Dir* get(const vector<string>& paths) {
		Dir* temp = root;
		for(const string& step: paths) {
			if(step == paths.back()) continue;
			if(!temp->dirs.count(step)) {
				temp->dirs[step] = new Dir();
			}
			temp = temp->dirs[step];
		}
		return temp;
	}
	
	vector<string> split(const string& path, const char& delim) {
		vector<string> tokens;
		stringstream ss(path); 
		string token;
		while(getline(ss, token, delim)) {
			if(!token.empty()) tokens.emplace_back(token);
		}
		return tokens;
	}
public:
	FileSystem() : root(new Dir()) {}
	
    vector<string> ls(string path) {
		Dir* temp = root;
		if(path != "/") {
			vector<string> paths = split(path, '/');
			temp = get(paths); 
			if(temp->files.count(paths.back())) { 
				return {paths.back()};
			}
			temp = temp->dirs[paths.back()];
		} 
		vector<string> content;
		for(const auto& item : temp->dirs) content.emplace_back(item.first);
		for(const auto& item : temp->files) content.emplace_back(item.first);
		sort(content.begin(), content.end());
		return content;
    }
    
    void mkdir(string path) {
        vector<string> paths = split(path, '/');
        Dir* prevLast = get(paths);
        if(!prevLast->dirs.count(paths.back())) {
			prevLast->dirs[paths.back()] = new Dir();
		}
    }
    
    void rmdir(string path) {
		vector<string> paths = split(path, '/');
        Dir* prevLast = get(paths);
        delete prevLast->dirs[paths.back()];
        prevLast->dirs[paths.back()] = nullptr;
        prevLast->dirs.erase(paths.back());
	}
    
    void addContentToFile(string filePath, string content) {
        vector<string> paths = split(filePath, '/');
        Dir* prevLast = get(paths);
        if(!prevLast->files.count(paths.back())) {
			prevLast->files[paths.back()] = content;
		} else prevLast->files[paths.back()] += content;
    }
    
    string readContentFromFile(string filePath) {
        vector<string> paths = split(filePath, '/');
        Dir* prevLast = get(paths);      
        return prevLast->files[paths.back()];  
    }
    
    ~FileSystem() {
		delete root;
		root = nullptr;
	}
};



/**
*	Input:
*		["FileSystem","ls","mkdir","addContentToFile","ls","readContentFromFile"]
* 		[[],["/"],["/a/b/c"],["/a/b/c/d","hello"],["/"],["/a/b/c/d"]]
* 	Output:
* 		[null,[],null,null,["a"],"hello"]
* 
*	Time:	ls: O(l + klogk), l is the path length, k is the number of entries in the last level directory
*        	mkdir: O(l)
*         	addContentToFile: O(l + c), c is the content size	
*   		readContentFromFile: O(l + c)
*	Space: O(n + s), n is the number of dir/file nodes, s is the total content size.
* 
*	IDEA adapted from the article: https://leetcode.com/articles/design-in-memory-file-system/
* 	Extra sample code: https://paste.ubuntu.com/p/Vrmn2X3TSW/
* 
* */



int main(int argc, char** argv) {
    fast_io
    
    
	FileSystem fs; // the constructor returns nothing
	//fs.mkdir("/aa");
	//cout << fs.ls("/") << endl;
	//fs.rmdir("/aa");
	cout << fs.ls("/") << endl; //initially directory is empty. So returns empty list
	//fs.mkdir("/a/b/c"); // create a->root, b->a, c->b
	//fs.mkdir("a/b/cc");
	fs.addContentToFile("/a/b/c/d", "hello"); //create file d with content "hello" in directory /a/b/c
	//fs.rmdir("/a/b/cc");
	//cout << fs.ls("/a/b") << endl;
	cout << fs.ls("/") << endl; // Only directory a in root /
	cout << fs.readContentFromFile("/a/b/c/d") << endl; // Output the file content
    
	
	
    return 0;
}





















