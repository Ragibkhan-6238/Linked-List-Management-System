#include "DoublyLinkedList.h"
#include "Utils.h"

#include <iostream>
#include <utility>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

bool DoublyLinkedList::isEmpty() const {
    return head == nullptr;
}

void DoublyLinkedList::clear() {
    while (head != nullptr) {
        DNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------

DNode* DoublyLinkedList::nodeAt(int pos) const {
    if (pos < 1) {
        return nullptr;
    }
    DNode* cur = head;
    int index = 1;
    while (cur != nullptr && index < pos) {
        cur = cur->next;
        ++index;
    }
    return cur;
}

DNode* DoublyLinkedList::findNode(int value) const {
    for (DNode* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == value) {
            return cur;
        }
    }
    return nullptr;
}

// Before: ... <-> cur->prev <-> cur <-> ...
// After:  ... <-> cur->prev <-> node <-> cur <-> ...
void DoublyLinkedList::linkBefore(DNode* cur, DNode* node) {
    node->next = cur;
    node->prev = cur->prev;
    if (cur->prev != nullptr) {
        cur->prev->next = node;
    } else {
        head = node;  // cur was the head
    }
    cur->prev = node;
}

// Before: ... <-> cur <-> cur->next <-> ...
// After:  ... <-> cur <-> node <-> cur->next <-> ...
void DoublyLinkedList::linkAfter(DNode* cur, DNode* node) {
    node->prev = cur;
    node->next = cur->next;
    if (cur->next != nullptr) {
        cur->next->prev = node;
    } else {
        tail = node;  // cur was the tail
    }
    cur->next = node;
}

// Detaches node from both directions, updates head/tail, and frees it.
void DoublyLinkedList::unlink(DNode* node, int& removed) {
    removed = node->data;
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        head = node->next;  // node was the head
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;  // node was the tail
    }
    delete node;
}

// ---------------------------------------------------------------------------
// Insertion
// ---------------------------------------------------------------------------

void DoublyLinkedList::insertAtBeginning(int value) {
    DNode* node = new DNode(value);
    if (head == nullptr) {
        head = tail = node;
    } else {
        linkBefore(head, node);
    }
}

void DoublyLinkedList::insertAtEnd(int value) {
    DNode* node = new DNode(value);
    if (tail == nullptr) {
        head = tail = node;
    } else {
        linkAfter(tail, node);
    }
}

// Valid positions are 1 .. count+1 (count+1 appends at the end).
bool DoublyLinkedList::insertAtPosition(int pos, int value) {
    if (pos < 1) {
        return false;
    }
    if (pos == 1) {
        insertAtBeginning(value);
        return true;
    }
    DNode* before = nodeAt(pos - 1);  // node that will precede the new node
    if (before == nullptr) {
        return false;
    }
    linkAfter(before, new DNode(value));
    return true;
}

bool DoublyLinkedList::insertAfter(int target, int value) {
    DNode* cur = findNode(target);
    if (cur == nullptr) {
        return false;
    }
    linkAfter(cur, new DNode(value));
    return true;
}

bool DoublyLinkedList::insertBefore(int target, int value) {
    DNode* cur = findNode(target);
    if (cur == nullptr) {
        return false;
    }
    linkBefore(cur, new DNode(value));
    return true;
}

// ---------------------------------------------------------------------------
// Deletion
// ---------------------------------------------------------------------------

bool DoublyLinkedList::deleteFromBeginning(int& removed) {
    if (head == nullptr) {
        return false;
    }
    unlink(head, removed);
    return true;
}

bool DoublyLinkedList::deleteFromEnd(int& removed) {
    if (tail == nullptr) {
        return false;
    }
    unlink(tail, removed);
    return true;
}

bool DoublyLinkedList::deleteFromPosition(int pos, int& removed) {
    DNode* node = nodeAt(pos);
    if (node == nullptr) {
        return false;
    }
    unlink(node, removed);
    return true;
}

bool DoublyLinkedList::deleteByValue(int value) {
    DNode* node = findNode(value);
    if (node == nullptr) {
        return false;
    }
    int ignored;
    unlink(node, ignored);
    return true;
}

// ---------------------------------------------------------------------------
// Query and modification
// ---------------------------------------------------------------------------

int DoublyLinkedList::search(int value) const {
    int index = 1;
    for (DNode* cur = head; cur != nullptr; cur = cur->next, ++index) {
        if (cur->data == value) {
            return index;
        }
    }
    return 0;
}

bool DoublyLinkedList::update(int oldValue, int newValue) {
    DNode* node = findNode(oldValue);
    if (node == nullptr) {
        return false;
    }
    node->data = newValue;
    return true;
}

// Output format: NULL <- 10 <-> 20 <-> 30 -> NULL
void DoublyLinkedList::displayForward() const {
    if (head == nullptr) {
        std::cout << "List is empty.\n";
        return;
    }
    std::cout << "NULL <- ";
    for (DNode* cur = head; cur != nullptr; cur = cur->next) {
        std::cout << cur->data;
        if (cur->next != nullptr) {
            std::cout << " <-> ";
        }
    }
    std::cout << " -> NULL\n";
}

// Starts at tail and follows prev links. Output: NULL <- 30 <-> 20 <-> 10 -> NULL
void DoublyLinkedList::displayBackward() const {
    if (tail == nullptr) {
        std::cout << "List is empty.\n";
        return;
    }
    std::cout << "NULL <- ";
    for (DNode* cur = tail; cur != nullptr; cur = cur->prev) {
        std::cout << cur->data;
        if (cur->prev != nullptr) {
            std::cout << " <-> ";
        }
    }
    std::cout << " -> NULL\n";
}

int DoublyLinkedList::count() const {
    int total = 0;
    for (DNode* cur = head; cur != nullptr; cur = cur->next) {
        ++total;
    }
    return total;
}

bool DoublyLinkedList::findMaximum(int& result) const {
    if (head == nullptr) {
        return false;
    }
    result = head->data;
    for (DNode* cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->data > result) {
            result = cur->data;
        }
    }
    return true;
}

bool DoublyLinkedList::findMinimum(int& result) const {
    if (head == nullptr) {
        return false;
    }
    result = head->data;
    for (DNode* cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->data < result) {
            result = cur->data;
        }
    }
    return true;
}

// Slow/fast reference method. For even-length lists this returns the FIRST
// of the two middle nodes (e.g. 10 <-> 20 <-> 30 <-> 40 gives 20).
bool DoublyLinkedList::findMiddle(int& result) const {
    if (head == nullptr) {
        return false;
    }
    DNode* slow = head;
    DNode* fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    result = slow->data;
    return true;
}

// ---------------------------------------------------------------------------
// Advanced operations
// ---------------------------------------------------------------------------

void DoublyLinkedList::reverse() {
    DNode* cur = head;
    while (cur != nullptr) {
        DNode* next = cur->next;  // remember the original next
        std::swap(cur->prev, cur->next);  // swap both links on this node
        cur = next;               // original next is now reached via prev
    }
    std::swap(head, tail);
}

// Beginner bubble sort: swap data values (node links stay untouched).
void DoublyLinkedList::sort() {
    for (DNode* i = head; i != nullptr; i = i->next) {
        for (DNode* j = head; j->next != nullptr; j = j->next) {
            if (j->data > j->next->data) {
                std::swap(j->data, j->next->data);
            }
        }
    }
}

void DoublyLinkedList::removeDuplicates() {
    for (DNode* outer = head; outer != nullptr; outer = outer->next) {
        DNode* cur = outer->next;
        while (cur != nullptr) {
            DNode* following = cur->next;  // save before unlink frees cur
            if (cur->data == outer->data) {
                int ignored;
                unlink(cur, ignored);
            }
            cur = following;
        }
    }
}

// ---------------------------------------------------------------------------
// Menu
// ---------------------------------------------------------------------------

void DoublyLinkedList::runMenu() {
    int choice;
    do {
        std::cout << "\n********** Operation on Doubly Linked List **********\n"
                  << "1. Insert at Beginning\n"
                  << "2. Insert at End\n"
                  << "3. Insert at Position\n"
                  << "4. Insert After a Node\n"
                  << "5. Insert Before a Node\n"
                  << "6. Delete from Beginning\n"
                  << "7. Delete from End\n"
                  << "8. Delete from Position\n"
                  << "9. Delete by Value\n"
                  << "10. Search\n"
                  << "11. Update\n"
                  << "12. Display Forward\n"
                  << "13. Display Backward\n"
                  << "14. Count Nodes\n"
                  << "15. Find Maximum\n"
                  << "16. Find Minimum\n"
                  << "17. Find Middle Element\n"
                  << "18. Reverse\n"
                  << "19. Sort\n"
                  << "20. Remove Duplicates\n"
                  << "21. Exit\n";
        choice = readInt("Enter the choice: ");

        int value, pos, target, removed, result;
        switch (choice) {
            case 1:
                value = readInt("Enter value: ");
                insertAtBeginning(value);
                std::cout << "Inserted " << value << " at beginning.\n";
                break;
            case 2:
                value = readInt("Enter value: ");
                insertAtEnd(value);
                std::cout << "Inserted " << value << " at end.\n";
                break;
            case 3:
                pos = readInt("Enter position (1-based): ");
                value = readInt("Enter value: ");
                if (insertAtPosition(pos, value)) {
                    std::cout << "Inserted " << value << " at position " << pos << ".\n";
                } else {
                    std::cout << "Invalid position. Valid range: 1 to " << count() + 1 << ".\n";
                }
                break;
            case 4:
                target = readInt("Insert after which value? ");
                value = readInt("Enter new value: ");
                if (insertAfter(target, value)) {
                    std::cout << "Inserted " << value << " after " << target << ".\n";
                } else {
                    std::cout << "Value " << target << " not found.\n";
                }
                break;
            case 5:
                target = readInt("Insert before which value? ");
                value = readInt("Enter new value: ");
                if (insertBefore(target, value)) {
                    std::cout << "Inserted " << value << " before " << target << ".\n";
                } else {
                    std::cout << "Value " << target << " not found.\n";
                }
                break;
            case 6:
                if (deleteFromBeginning(removed)) {
                    std::cout << "Deleted " << removed << " from beginning.\n";
                } else {
                    std::cout << "List is empty. Nothing to delete.\n";
                }
                break;
            case 7:
                if (deleteFromEnd(removed)) {
                    std::cout << "Deleted " << removed << " from end.\n";
                } else {
                    std::cout << "List is empty. Nothing to delete.\n";
                }
                break;
            case 8:
                pos = readInt("Enter position (1-based): ");
                if (deleteFromPosition(pos, removed)) {
                    std::cout << "Deleted " << removed << " from position " << pos << ".\n";
                } else {
                    std::cout << "Invalid position.\n";
                }
                break;
            case 9:
                value = readInt("Enter value to delete: ");
                if (deleteByValue(value)) {
                    std::cout << "Deleted first occurrence of " << value << ".\n";
                } else {
                    std::cout << "Value " << value << " not found.\n";
                }
                break;
            case 10:
                value = readInt("Enter value to search: ");
                pos = search(value);
                if (pos > 0) {
                    std::cout << "Value " << value << " found at position " << pos << ".\n";
                } else {
                    std::cout << "Value " << value << " not found.\n";
                }
                break;
            case 11:
                target = readInt("Enter value to update: ");
                value = readInt("Enter new value: ");
                if (update(target, value)) {
                    std::cout << "Updated " << target << " to " << value << ".\n";
                } else {
                    std::cout << "Value " << target << " not found.\n";
                }
                break;
            case 12:
                displayForward();
                break;
            case 13:
                displayBackward();
                break;
            case 14:
                std::cout << "Number of nodes: " << count() << "\n";
                break;
            case 15:
                if (findMaximum(result)) {
                    std::cout << "Maximum: " << result << "\n";
                } else {
                    std::cout << "List is empty.\n";
                }
                break;
            case 16:
                if (findMinimum(result)) {
                    std::cout << "Minimum: " << result << "\n";
                } else {
                    std::cout << "List is empty.\n";
                }
                break;
            case 17:
                if (findMiddle(result)) {
                    std::cout << "Middle element: " << result
                              << " (for even length, the first of the two middle nodes)\n";
                } else {
                    std::cout << "List is empty.\n";
                }
                break;
            case 18:
                reverse();
                std::cout << "List reversed.\n";
                break;
            case 19:
                sort();
                std::cout << "List sorted in ascending order.\n";
                break;
            case 20:
                removeDuplicates();
                std::cout << "Duplicates removed.\n";
                break;
            case 21:
                std::cout << "Returning to main menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1 to 21.\n";
        }
    } while (choice != 21);
}
