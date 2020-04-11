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
 
 


//  Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
  
  
  ~ListNode() {
	if(next) {
	    delete next;
	    next = nullptr;
	}
   }
};


 
class Solution {
 public:   
    void printList(ListNode* head) {
	ListNode* cur = head;
	while(cur) {
	    cout << cur->val << " ";
	    cur = cur->next;
	}
	cout << endl;
    }
    
    ListNode* addNode(ListNode* head, const int& val) {
	if(head == nullptr) {
	    head = new ListNode(val);
	    return head;
	}
	ListNode* cur = head;
	while(cur->next) {
	    cur = cur->next;
	}
	cur->next = new ListNode(val);
	return head;
    }
    
    ListNode* createList(const vector<int> v) {
	ListNode* head = nullptr;
	for(const int& item : v) head = addNode(head, item);
	return head;
    }
    
//public:
    inline ListNode* reverseList(ListNode* head) {
        
	ListNode* rev_head = nullptr;
	ListNode* cur = head;
	ListNode* temp = nullptr;
	
	while(cur) {
	    temp = cur->next;			// ph-> cur -> tmp  1 2 3 
	    cur->next = rev_head;				        //^			
	    rev_head = cur;
	    cur = temp;
	}
	
	return rev_head;
    }
    
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        ListNode* temp = nullptr;
        
        n -= m - 1;
        while(--m){
            temp = cur->next;
            prev = cur;
            cur = temp;
        }
        
        ListNode* part_1_end = prev;
        ListNode* part_2_start = cur;
        prev = nullptr;
        
        //cout << part_1_end->val << endl;    // 1
        //cout << part_2_start->val << endl;  // 2
        
        
        while(n--) {
            temp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = temp;
        }
        
        ListNode* part_3_start = cur; 
        
	//cout << part_3_start->val << endl; // 5
	//cout << prev->val << endl;         // 4
        

        if(part_1_end) {    // for 1 upto something range handle
            part_1_end->next = prev;
        } else {
            head = prev;
        }
        part_2_start->next = part_3_start;

        
        return head;
        
    }
    
    //can't be tail node
    void deleteNode(ListNode* node) {
        ListNode* next_node = node->next;
        node->val = next_node->val;
        node->next = next_node->next;
        next_node->next = nullptr;
	delete next_node;
	next_node = nullptr;
    }
    
    // sorted list keep one
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* cur = head;
        while(cur) {
            if(prev && cur->val == prev->val) {
                prev->next = cur->next;
                cur->next = nullptr;
                
                delete cur;
                cur = nullptr;
                
                cur = prev->next;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
        return head;
    }
    
    //sorted list don't keep one
    ListNode* deleteDuplicatesAll(ListNode* head) {
        ListNode* cur = head, *prev = nullptr;
        int before_me = INT_MIN;
        
        while(cur) {
            if((cur->next && cur->next->val == cur->val) || cur->val == before_me) {
                before_me = cur->val;
                if(cur == head) {
                    head = cur->next;
                    
                    cur->next = nullptr;
                    delete cur;
                    
                    cur = head;
                    prev = nullptr;
                } else{
                    prev->next = cur->next;
                    
                    cur->next = nullptr;
                    delete cur;
                    
                    cur = prev->next;
                }
            } else {
                prev = cur;
                before_me = cur->val;
                cur = cur->next;
            }
        }
        
        return head;
    }
    
    // Delete Middle Node
    ListNode* deleteMiddle(ListNode* head) {
	if(!head) return head;
	else if(!head->next) {
	    delete head;
	    return head = nullptr;
	}
	
	ListNode* hear = head, *tortoise = head;
	ListNode* prev = nullptr;
	
	while(tortoise && tortoise->next) {
	    prev = hear;
	    hear = hear->next;
	    tortoise = tortoise->next->next;
	}
	
	prev->next = hear->next;
	hear->next = nullptr;
	delete hear;
	
	return head;
    }
    
    
    //Maintain two pointers and update one with a delay of n steps.
    ListNode* removeValidNthFromEnd(ListNode* head, int n) {
        pair<ListNode*, ListNode*> pointer(head, head);
        
        while(n--) pointer.first = pointer.first->next;
        
        ListNode* prev = nullptr;
        
        while(pointer.first) {
            prev= pointer.second;
            pointer = {pointer.first->next, pointer.second->next};
        }
        
        if(pointer.second == head) head = head->next;
        else prev->next = pointer.second->next;
        
        pointer.second->next = nullptr;
        delete pointer.second;
        pointer.second = nullptr;
        
        return head;
    }
    
    // in O(1) extra space by removing tye functions
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        
        ListNode* slow = head;
        ListNode* fast = head;
        
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        if(fast) slow = slow->next;
        
        ListNode* temp1 = reverseList(slow);
        slow = temp1;
        fast = head;
        
        bool flag = true;
        while(slow) {
            if(slow->val != fast->val) {
                flag = false;
                break;
            }
            slow = slow->next, fast = fast->next;
        }
        
        slow = reverseList(temp1);
        
        return flag;
    }
    
/* palindrome checking
1 -> 2 -> 4 -> 4 -> 2 -> 1 -> null    # fast is null, even nodes, reverse from slow to end
               ^               |    

1 -> 2 -> 4 -> 5 -> 4 -> 2 -> 1 -> null  # fast is not null, odd nodes, reverse from slow->next to end
               ^              |
*/
	

	    
    struct Node {
	int val;
	Node* next;
	Node* random;
	Node(int v) {
	    next = random = nullptr;
	    val = v;
	}
    };
    
    // 3 pass algorithm with O(n) time and O(1) extra space
    Node* copyRandomList(Node* head) {
        
        Node* cur = head, *clone, *clone_head;
        while(cur) {
            clone = new Node(cur->val); // make deep copy
            clone->next = cur->next;    // clone next = current next
            cur->next = clone;          // current next = its clone
            cur = clone->next;          // forward current 
        }
        
        cur = head; 
        while(cur) {
            clone = cur->next;                  // find clone of cur
            clone->random = cur->random ? cur->random->next : nullptr; // update clones random
            cur = clone->next;                  // forward current
        }
        
        cur = head, clone_head = head ? head->next : nullptr;
        while(cur) {
            clone = cur->next;              // find clone
            cur->next = clone->next;        // retrive currents next
            clone->next = clone->next ? clone->next->next : nullptr;    // set clone next if found
            cur = cur->next;            // forward current
        }
                 
        return clone_head;
    }
    
    bool hasCycle(ListNode *head) {
        /**
        unordered_set<ListNode*> seen;
        while(head) {
            if(!seen.count(head)) {
                seen.insert(head);
                head = head->next;
            } else {
                return true;
            }
        }
        return false;
        */
        
        ListNode* fast = head;
        ListNode* slow = head;
        
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) return true; // this is checked after at least some move
        }
        
        return false;
    }

     ListNode *detectCycle(ListNode *head) {
        /**
        unordered_set<ListNode*> seen;
        while(head) {
            if(!seen.count(head)) {
                seen.insert(head);
                head = head->next;
            } else {
                return head;
            }
        }
        return nullptr;
        **/
        
        //http://en.shafaetsplanet.com/floyds-cycle-finding-algorithm/
        
        if(!head) return head;
        
        ListNode* h = head;
        ListNode* t = head;
        
        bool met = false;
        while(h && h->next) {
            t = t->next;
            h = h->next->next;
            if(h == t) {
                met = true;
                break;
            }
        }
        
        if(met) {
            h = head;
            while(h != t) h = h->next, t = t->next;
            return h;
        }
        
        return nullptr; 
    }
    
    // Function to remove duplicates from the linked list
    // root: root of the linked list
    ListNode * removeDuplicates( ListNode *head) {
	// your code goes here
	unordered_map<int, pair<int, bool>> cnt;
	ListNode* cur = head;
	while(cur) {
	    ++cnt[cur->val].first;
	    cnt[cur->val].second = false;
	    cur = cur->next;
	}
	
	ListNode* prev = nullptr;
	cur = head;
	ListNode* temp = nullptr;
	
	while(cur) {
	    if(cnt[cur->val].first > 1) {
		if(!cnt[cur->val].second) { // keep the first element 
		    cnt[cur->val].second = true;
		    prev = cur;
		    cur = cur->next;
		    continue;
		}
		--cnt[cur->val].first;
		temp = cur->next;
		
		if(cur == head) head = temp;
		else prev->next = temp;
		
		cur->next = nullptr;
		delete cur;
		cur = temp;
	    } else {
		prev = cur;
		cur = cur->next;
	    }
	}
     
	return head;
    }
    
    
}; 
 


int main(int argc, char** argv) {
    fast_io
   
    Solution s;
    ListNode* head = s.createList({1,2,3,5,4});
    s.printList(head);
    head = s.reverseList(head);
    s.deleteNode(head);
    s.printList(head);
	

    delete head;
    head = nullptr;

    return 0;
}





