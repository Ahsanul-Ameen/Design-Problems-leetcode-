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
	int key, val, cnt;
	Node* prev, *next;
	Node(int k, int v) {
		key = k, val = v, cnt = 0;
		prev = next = nullptr;
	}
	Node(Node* node) {
		this->key = node->key, val = node->val, cnt = node->cnt;
		prev = next = nullptr;
	}
	~Node() {key = val = cnt = 0; prev = next = nullptr;}
};

struct DLList {
	Node *head, *tail;
	int len;
	DLList() {
		head = new Node(-1, -1);
		tail = new Node(-1, -1);
		head->next = tail, tail->prev = head;
		len = 0;
	}
	
	void addFirst(Node* node) { 
		++len;
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}
	
	void remove(Node* node) {
		Node *p = node->prev, *n = node->next;
		p->next = n, node->prev = nullptr;
		n->prev = p, node->next = nullptr;
		--len;
	}
	
	void removeTail() {
		Node* node = tail->prev;
		remove(node);
		delete node;
		node = nullptr;
	}
	
	void printList() {
		cout << "List Size: " << len << endl;
		for(Node* n = head->next; n != tail; n = n->next) {
			cout << "(" << n->key << ", " << n->val << ") ";
		}
		cout << endl;
	}
	
	~DLList() {
		Node* c = head, *cc = nullptr;
		while(c) {
			cc = c->next;
			delete c;
			c = cc;
		}
		c = cc = head = tail = nullptr;
		len = 0;	
	}
};


class LFUCache {
	unordered_map<int, Node*> nodeMap;
	unordered_map<int, DLList*> freqMap;
	unordered_map<int, unordered_map<int, Node*>> freqNodeMap;
	size_t size; 
	int maxFreq, cap;
public:
    LFUCache(int capacity) {
        cap = capacity;
        size = 0, maxFreq = 0;
    }
    
    int get(int key) {
		//not found
        if(nodeMap.find(key) == nodeMap.end()) return -1;

        Node* node = nodeMap[key];
        int prevfreq = node->cnt, nextfreq = node->cnt+1;
        if(freqMap.find(prevfreq) == freqMap.end()) freqMap[prevfreq] = new DLList();
        if(freqMap.find(nextfreq) == freqMap.end()) freqMap[nextfreq] = new DLList();
        DLList *prevList = freqMap[prevfreq], *nextList = freqMap[nextfreq];
		//remove copy of node from prev freq
		int v = node->val;
        Node* freqNode = freqNodeMap[prevfreq][key];
        freqNodeMap[prevfreq][key] = nullptr;
        freqNodeMap[prevfreq].erase(key);
        prevList->remove(freqNode); delete freqNode; freqNode = nullptr;
        //adjust and add node copy in next freq
        maxFreq = max(maxFreq, nextfreq);
        freqNode = new Node(key, v); freqNode->cnt = nextfreq;
        nextList->addFirst(freqNode);
        freqNodeMap[nextfreq][key] = freqNode;
        nodeMap[key] = freqNode;
        return freqNode->val;
    }
    
    void put(int key, int value) {
		if(cap) {
			//already has the key/value pair
			if(nodeMap.find(key) != nodeMap.end()) {
				nodeMap[key]->val = value;
				this->get(key);
				return;
			} else {
				Node* node = new Node(key, value);
				if(freqMap.find(1) == freqMap.end()) 
					freqMap[1] = new DLList();
				DLList* dlist = freqMap[1];
				dlist->addFirst(node), ++size;
				node->cnt = 1;
				freqNodeMap[1][key] = node;
				
				if(size > (size_t)cap) {
					Node* dnode;
					if(dlist->len > 1) { 
						dnode = dlist->tail->prev;
						freqNodeMap[1].erase(dnode->key);
						nodeMap.erase(dnode->key);
						dlist->removeTail();
						dnode = nullptr; 
					}
					else {
						for(int f = 2; f <= maxFreq; ++f) {
							if(freqMap.find(f) != freqMap.end() && freqMap[f]->len > 0) {
								dnode = freqMap[f]->tail->prev;
								freqNodeMap[f].erase(dnode->key);
								nodeMap.erase(dnode->key);
								freqMap[f]->removeTail();
								dnode = nullptr;
								break;
							}
						}
					}
					--size;
				}
				nodeMap[key] = node;
				
			}
		}
    }
	
	~LFUCache() {
		for(int f = 1; f <= maxFreq; ++f) {
			freqNodeMap[f].clear();
			delete freqMap[f];
			freqMap[f] = nullptr;
		}
		freqMap.clear();
		nodeMap.clear();
	}
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */



int main(int argc, char** argv) {
    fast_io
    
    
	LFUCache* cache = new LFUCache( 2 /* capacity */ );

	cache->put(1, 1);
	cache->put(2, 2);
	cout << cache->get(1) << endl;       // returns 1
	cache->put(3, 3);   				 // evicts key 2
	cout << cache->get(2) << endl;       // returns -1 (not found)
	cache->put(4, 4);   				 // evicts key 1
	cout << cache->get(1) << endl;       // returns -1 (not found)
	cout << cache->get(3) << endl;       // returns 3
	cout << cache->get(4) << endl;       // returns 4
		
	delete cache;
	cache = nullptr;
	
	
    return 0;
}





















