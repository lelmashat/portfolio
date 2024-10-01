#include "llrec.h"

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
    // Base case: If the current node is nullptr (end of the list), set both 'smaller' and 'larger' to nullptr and return
    if (head == nullptr) {
        smaller = nullptr;
        larger = nullptr;
        return;
    }

    // Check if the value of the current node is less than or equal to the pivot
    if (head->val <= pivot) {
        // recursively call llpivot on next node, and change variables as needed
        llpivot(head->next, smaller, larger, pivot);
        head->next = smaller;
        smaller = head;
    } else {
        //recursively call llpivot on the next node and change variables as needed 
        llpivot(head->next, smaller, larger, pivot);
        head->next = larger;
        larger = head;
    }
    // Set the 'head' pointer to nullptr to detach it from the original list
    head = nullptr;
}




