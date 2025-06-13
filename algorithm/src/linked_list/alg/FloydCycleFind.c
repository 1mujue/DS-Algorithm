// this is a very classic algorithm to judge whether a linked list has a cycle
// or not. The algorithm is called Floyd's cycle-finding algorithm. 

// The idea is to use two pointers, one is slow and the other is fast. 
// The slow pointer moves ONE step each time and the fast pointer moves TWO steps each time. 
// If there is a cycle in the linked list, the two pointers will meet at some
// point. If there is no cycle, the fast pointer will reach the end of the list.

// The time complexity of this algorithm is O(n) and the space complexity is
// O(1).

struct ListNode{
    int val;
    struct ListNode* next;
};

int FloydCycleFind(struct ListNode* head){
    if(!head) return 0;
    // we use do-while loop to prevent breaking the while loop at the very beginning. 
    // (the break condition is slow == fast, if we use while(..) loop, the loop will
    // break immediately.)
    struct ListNode* slow = head, *fast = head;
    // ans = 1 means there is a cycle.
    int ans = 1;
    do{
        // fast has reached the end!!
        if(!fast || !fast->next) {
            ans = 0;
            break;
        }
        slow = slow->next;
        fast = fast->next->next;
    } while (slow != fast);
    // we may want to ask: if there is a cycle, then where is the entry of the cycle?
    // assuming the NON-CYCLE part's length is a. 
    // When slow and fast meet, slow havegone b ON THE CYCLE.
    // and the length of left part is c. 

    // Clearly, b + c is the length of cycle.
    // it is evident that, when fast and slow meet, 
    // fast have gone a + n * (b + c) + b,
    // slow have gone a + b.
    
    // since fast's speed is double as slow, we have:
    // a + (n + 1) * b + n * c = 2a + 2b,
    // a = (n - 1) * b + n * c = (n - 1) * (b + c) + c.
    
    // That means, a + b = n * (b + c) ! Now slow have gone b,
    // so if slow go a steps, it will be at the entry of the cycle!
    // Therefore, we just need to let struct ListNode* p = head,
    // if p and slow move a steps, they will meet at the entry of the cycle.
    struct ListNode* p = head;
    while(p != slow){
        p = p->next;
        slow = slow->next;
    }
    
    return ans;
}