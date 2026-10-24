#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

// A node of a doubly linked list: data plus links in both directions.
struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    explicit DNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Doubly linked list with the full set of required operations.
// Keeps both head and tail so that appending and backward display are O(1) to start.
// Positions are 1-based. Search/Find functions return 0 or false when nothing matches.
class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;

    // Helpers that keep prev/next links consistent in one place.
    DNode* nodeAt(int pos) const;                // 1-based; nullptr if out of range
    DNode* findNode(int value) const;            // first node with this value
    void linkBefore(DNode* cur, DNode* node);    // insert node immediately before cur
    void linkAfter(DNode* cur, DNode* node);     // insert node immediately after cur
    void unlink(DNode* node, int& removed);      // detach and free node

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    // Copying is disabled so that two lists never share (and double-free) nodes.
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    bool isEmpty() const;
    void clear();

    // Insertion
    void insertAtBeginning(int value);                 // O(1)
    void insertAtEnd(int value);                       // O(1) with tail
    bool insertAtPosition(int pos, int value);         // O(n)
    bool insertAfter(int target, int value);           // O(n)
    bool insertBefore(int target, int value);          // O(n)

    // Deletion (removed value is returned through the reference parameter)
    bool deleteFromBeginning(int& removed);            // O(1)
    bool deleteFromEnd(int& removed);                  // O(1) with tail
    bool deleteFromPosition(int pos, int& removed);    // O(n)
    bool deleteByValue(int value);                     // O(n)

    // Query and modification
    int search(int value) const;                       // returns 1-based position or 0
    bool update(int oldValue, int newValue);           // O(n)
    void displayForward() const;                       // O(n), follows next links
    void displayBackward() const;                      // O(n), starts at tail, follows prev links
    int count() const;                                 // O(n)
    bool findMaximum(int& result) const;               // O(n)
    bool findMinimum(int& result) const;               // O(n)
    bool findMiddle(int& result) const;                // O(n)

    // Advanced operations
    void reverse();                                    // O(n): swaps prev/next, then head/tail
    void sort();                                       // Bubble sort, O(n^2)
    void removeDuplicates();                           // O(n^2)

    // Interactive menu for this list
    void runMenu();
};

#endif
