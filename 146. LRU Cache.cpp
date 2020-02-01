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
 


struct Node {
    int key, value;
    Node *prev, *next;
	
    Node(int k, int v) {
		key = k, value = v;
		prev = nullptr;
		next = nullptr;
	}
    ~Node() {
        prev = next = nullptr;
    }
};

struct Dlist {
    Node *head, *tail;
    
    //construct a linked list with dummy nodes(head, tail)
    Dlist() {
        head = new Node(INT_MIN, INT_MIN);
        tail = new Node(INT_MAX, INT_MAX);
        head->next = tail;
        tail->prev = head;
    }
    
    //remove that node from list
    void remove(Node * node) {
        Node * p = node->prev, * n = node->next;
        p->next = n, n->prev = p;
        node->prev = node->next = nullptr;
    }
    
    //add that node after head
    void addfirst(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    ~Dlist() {
		head = tail = nullptr;
    }
};

class LRUCache {
    int cap;
    int s;
    Dlist * dl;
    unordered_map<int, Node*> hashCheck;
    
public:
    LRUCache(int capacity) {
        s = 0;
        cap = capacity;
        dl = new Dlist();
    }
    
    int get(int key) {
        //if exists then remove and addfirst and return
        //else return -1
         if(hashCheck.find(key) != hashCheck.end()) {
            Node * node = hashCheck[key];
            dl->remove(node);
            dl->addfirst(node);
            hashCheck[key] = node;
            return node->value;
        } else {
            return -1;
        }
    }
    
    void put(int key, int value) {
        //if doesn't exist addfirst
        //else remove and addfirst
        if(hashCheck.find(key) == hashCheck.end()) {
            if(s == cap) {
                --s;
                //remove last node
                int k = dl->tail->prev->key;
                Node* node = dl->tail->prev;
                dl->remove(node);
                delete node;
                node = nullptr;
                hashCheck.erase(k);
            }
            dl->addfirst(new Node(key, value));
            hashCheck.insert({key, dl->head->next});
            ++s;
        } else if(hashCheck.find(key) != hashCheck.end()) {
            dl->remove(hashCheck[key]);
            hashCheck[key]->value = value;
            dl->addfirst(hashCheck[key]);
        }
    }
    
    ~LRUCache() {
		for(Node *cur = dl->head; cur != nullptr; ) {
			Node* n = cur->next;
			delete cur;
			cur = n;
		}
		
        delete dl;
        dl = nullptr;
        hashCheck.clear();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */



int main(int argc, char** argv) {
    fast_io
    
    
	LRUCache* cache = new LRUCache( 2 /* capacity */ );

	cache->put(1, 1);
	cache->put(2, 2);
	cout << cache->get(1) << endl;       // returns 1
	cache->put(3, 3);    // evicts key 2
	cout << cache->get(2) << endl;       // returns -1 (not found)
	cache->put(4, 4);    // evicts key 1
	cout << cache->get(1) << endl;       // returns -1 (not found)
	cout << cache->get(3) << endl;       // returns 3
	cout << cache->get(4) << endl;       // returns 4
		
	delete cache;
	cache = nullptr;
	
	
    return 0;
}





















