#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

// A node of a singly linked list: holds data and a link to the next node.
struct SNode {
    int data;
    SNode* next;

    explicit SNode(int value) : data(value), next(nullptr) {}
};

// Singly linked list with the full set of required operations.
// Positions are 1-based. Search/Find functions return 0 or false when nothing matches.
class SinglyLinkedList {
private:
    SNode* head;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    // Copying is disabled so that two lists never share (and double-free) nodes.
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    bool isEmpty() const;
    void clear();

    // Insertion
    void insertAtBeginning(int value);                 // O(1)
    void insertAtEnd(int value);                       // O(n)
    bool insertAtPosition(int pos, int value);         // O(n)
    bool insertAfter(int target, int value);           // O(n)
    bool insertBefore(int target, int value);          // O(n)

    // Deletion (removed value is returned through the reference parameter)
    bool deleteFromBeginning(int& removed);            // O(1)
    bool deleteFromEnd(int& removed);                  // O(n)
    bool deleteFromPosition(int pos, int& removed);    // O(n)
    bool deleteByValue(int value);                     // O(n)

    // Query and modification
    int search(int value) const;                       // returns 1-based position or 0
    bool update(int oldValue, int newValue);           // O(n)
    void display() const;                              // O(n)
    int count() const;                                 // O(n)
    bool findMaximum(int& result) const;               // O(n)
    bool findMinimum(int& result) const;               // O(n)
    bool findMiddle(int& result) const;                // O(n)

    // Advanced operations
    void reverse();                                    // O(n) time, O(1) extra space
    void sort();                                       // Bubble sort, O(n^2)
    void removeDuplicates();                           // O(n^2)

    // Interactive menu for this list
    void runMenu();
};

#endif
