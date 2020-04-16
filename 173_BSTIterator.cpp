#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define     endl               "\n"
#define     fast_io            ios::sync_with_stdio(false); cin.tie(0);
#define     all(x)             begin(x), end(x)
#define     debug(x)           cerr <<"Line "<< __LINE__ <<" : "<< #x " = "<< x <<endl;
 
template<typename T, typename TT>
ostream& operator<<(ostream &os, const pair<T, TT> &t) { return os<<"("<<t.first<<", "<<t.second<<")"; }
template<typename T>
ostream& operator<<(ostream& os, const vector<T> &t) { for(auto& i: t) os<<i<<" "; return os; }
 
 
/**
 * Definition for a binary tree node.
 **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
    ~TreeNode() {
	if(left) {
	    delete left;
	    left = nullptr;
	}
	if(right) {
	    delete right;
	    right = nullptr;
	}
    }
};
 
 
class BSTIterator {
    // stack helps us controlling recursion
    stack<TreeNode*> s;
    
    // push all nodes along left path withing its subtree
    void leftPush(TreeNode* root) {
        while(root) {
            s.push(root);
            root = root->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        // initialize with root ans its left....s
        leftPush(root);
    }
    
    /** @return the next smallest number */
    int next() {
        // validity check only 
        assert(!s.empty());
        
        //this node is surely desired next smallest node
        TreeNode* smallest = s.top();
        s.pop();
        // only pushes if it has a right subtree
        leftPush(smallest->right);
       
        return smallest->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        // if stack contains at least one node then we'll be able to process it
        return !s.empty();    
    }
    
    ~BSTIterator() {
	while(hasNext()) s.pop();
    }
};

/**
 * Problem : https://leetcode.com/problems/binary-search-tree-iterator/
 * Solution : https://leetcode.com/articles/binary-search-tree-iterator/
 *  
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */


void testIterator(BSTIterator* bst_iterator) {
    // provides sorted sequence
    while(bst_iterator->hasNext()) {
	cout << bst_iterator->next() << endl;
    }
}


int main(int argc, char** argv) {
    fast_io
    
    // generate a tree like structure
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);
    
    
    // Construct an iterator object
    BSTIterator* bst_iterator = new BSTIterator(root);
    
    // Code Testing
    testIterator(bst_iterator);
    
    // free up memory
    delete bst_iterator;
    bst_iterator = nullptr;

    delete root;
    root = nullptr;
    

    return 0;
}





