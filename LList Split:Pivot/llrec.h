#ifndef LLREC_H
#define LLREC_H
#ifndef NULL
#define NULL 0
#endif

/**
 * Node struct for both problems
 */
struct Node
{
    int val;
    Node *next;

    Node(int v, Node* n) : val(v), next(n) {}
};

/**
 * Given a linked list pointed to by head, creates two lists
 * where all values less than or equal to the pivot value are
 * placed in a linked list whose head will be pointed to by
 * smaller and all values greater than the pivot
 * value are placed in a linked list whose head will be pointed to
 * by larger.  
 */
void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot);

/**
 * Given a linked list pointed to by head, removes (filters out) nodes
 * whose value does not meet the criteria given by the predicate
 * function object
 */

template <typename Comp>
Node* llfilter(Node* head, Comp pred) {
    // Base case: If the current node is nullptr (end of the list), return nullptr
    if (head == nullptr) {
        return nullptr;
    }

    // Check if the current node's value does not satisfy the predicate
    if (!pred(head->val)) {
        // Disconnect the current node from the original list and makes updates to list accordingly
        Node* filteredHead = head;
        Node* filteredTail = head;
        head = head->next;
        filteredHead->next = nullptr;

        // Recursive call on the next node in the list, and update the filtered list
        Node* nextFiltered = llfilter(head, pred);
        if (nextFiltered != nullptr) {
            filteredTail->next = nextFiltered;
            filteredTail = nextFiltered;
        }

        return filteredHead;
    } else {
        // If the current node's value satisfies the predicate, delete the node and continue with the next node
        Node* temp = head;
        head = head->next;
        delete temp;

        // Recursive call on the next node in the list
        return llfilter(head, pred);
    }
}

#endif

