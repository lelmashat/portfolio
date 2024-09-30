/*
Create linked lists and split them with the split() function.
*/

#include "split.h"
#include <iostream>
using namespace std;

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->value << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Create a sample linked list
    Node node5(5, NULL);
    Node node4(4, &node5);
    Node node3(3, &node4);
    Node node2(2, &node3);
    Node node1(1, &node2);

    // Set head to point to the first node
    Node* head = &node1;

    // Initialize pointers for odds and evens lists
    Node *odds = nullptr;
    Node *evens = nullptr;

    // Call the split function
    split(head, odds, evens);

    // Print the original and separated lists
    cout << "Original List: ";
    printList(head);

    cout << "Odd Values: ";
    printList(odds);

    cout << "Even Values: ";
    printList(evens);

    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
    }

    // Free the memory for the odd values list
    

    delete head;

    return 0;

}

