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
 


//https://leetcode.com/articles/desing-compressed-string-iterator/
//reverse code: https://leetcode.com/submissions/detail/299586058/

//assume valid input strings only, no just 0 as frequencies
//Approach #3 Demand-Computation
//Time: O(hasNext + next), O(validNext) <= O(n)
//space: O(s.size()) with no extra linear space
class StringIterator {
	string compressedString;
	unsigned ptr, num;
	char res;
public:
	explicit StringIterator(const string& str) : 
		compressedString(str), ptr(0), num(0) {}
	
	bool hasNext() {
		return ptr != compressedString.length() || num; 
	}
	char next() {
		if(!hasNext()) return ' ';
		if(!num) {
			res = compressedString[ptr++]; //character 
			while(ptr < compressedString.length() && isdigit(compressedString[ptr])) {
				num = num * 10 + (compressedString[ptr++] - '0'); //number
			}
		}
		--num; //use it
		return res;
	}
};






int main(int argc, char** argv) {
    fast_io
    
    	
	StringIterator iterator("g1e2k1s1f1o1r1g1e2k1s1w4a3d1e1x6y1w3L1e2t1C1o1d1e1");
	while(iterator.hasNext()) cout << iterator.next();
	cout << endl << '|' << iterator.next() << '|' << endl;
	
	
    return 0;
}





















