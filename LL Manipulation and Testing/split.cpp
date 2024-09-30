/*
A recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. 
*/

#include "split.h"

void helper(Node*& in, Node*& oddsHead, Node*& oddsTail, Node*& evensHead, Node*& evensTail) {
    // if the pointer to the first node is pointing to null, we just return
    if(in == nullptr){
        return;
    }

    // we create a pointer for the current node and set it to in->next
    Node* current = in;
    in = in->next;
    current->next = nullptr;  // Separate the current node from the original list

    // Case 1: current value we are checking is even
    if(current->value % 2 == 0){
        // if there are no evens yet, we make current the head and tail
        if(evensHead == nullptr){
            evensHead = evensTail = current;
        } else { // otherwise, we add it to the back of the list
            evensTail->next = current;
            evensTail = evensTail->next;
        }
    } else { // Case 2: current value we are checking is odd
        // if there are no odds yet, we make the current the head and tail
        if(oddsHead == nullptr){
            oddsHead = oddsTail = current;
        } else { // otherwise, we add it to the back of the list
            oddsTail->next = current;
            oddsTail = oddsTail->next;
        }
    }

    // Recursive call for the next node
    helper(in, oddsHead, oddsTail, evensHead, evensTail);
}

void split(Node*& in, Node*& odds, Node*& evens) {
    // Pointers for the head and tail of the two lists, to be used in helper function
    Node* oddsHead = nullptr;
    Node* oddsTail = nullptr;
    Node* evensHead = nullptr;
    Node* evensTail = nullptr;

    helper(in, oddsHead, oddsTail, evensHead, evensTail);

    // we set the odd and even pointers to the head pointers so that they correctly point to the lists
    odds = oddsHead;
    evens = evensHead;
}


