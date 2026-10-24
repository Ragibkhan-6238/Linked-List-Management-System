#include "SinglyLinkedList.h"
#include "Utils.h"

#include <iostream>
#include <utility>

SinglyLinkedList::SinglyLinkedList() : head(nullptr) {}

SinglyLinkedList::~SinglyLinkedList() {
    clear();
}

bool SinglyLinkedList::isEmpty() const {
    return head == nullptr;
}

void SinglyLinkedList::clear() {
    while (head != nullptr) {
        SNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// ---------------------------------------------------------------------------
// Insertion
// ---------------------------------------------------------------------------

void SinglyLinkedList::insertAtBeginning(int value) {
    SNode* node = new SNode(value);
    node->next = head;
    head = node;
}

void SinglyLinkedList::insertAtEnd(int value) {
    SNode* node = new SNode(value);
    if (head == nullptr) {
        head = node;
        return;
    }
    SNode* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = node;
}

// Valid positions are 1 .. count+1 (count+1 appends at the end).
bool SinglyLinkedList::insertAtPosition(int pos, int value) {
    if (pos < 1) {
        return false;
    }
    if (pos == 1) {
        insertAtBeginning(value);
        return true;
    }

    // Walk to the node just before the target position (pos - 1).
    SNode* prev = head;
    int index = 1;
    while (prev != nullptr && index < pos - 1) {
        prev = prev->next;
        ++index;
    }
    if (prev == nullptr) {
        return false;  // position is beyond count+1
    }

    SNode* node = new SNode(value);
    node->next = prev->next;
    prev->next = node;
    return true;
}

bool SinglyLinkedList::insertAfter(int target, int value) {
    for (SNode* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == target) {
            SNode* node = new SNode(value);
            node->next = cur->next;
            cur->next = node;
            return true;
        }
    }
    return false;
}

bool SinglyLinkedList::insertBefore(int target, int value) {
    if (head == nullptr) {
        return false;
    }
    if (head->data == target) {
        insertAtBeginning(value);
        return true;
    }

    SNode* prev = head;
    SNode* cur = head->next;
    while (cur != nullptr) {
        if (cur->data == target) {
            SNode* node = new SNode(value);
            node->next = cur;
            prev->next = node;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Deletion
// ---------------------------------------------------------------------------

bool SinglyLinkedList::deleteFromBeginning(int& removed) {
    if (head == nullptr) {
        return false;
    }
    SNode* temp = head;
    removed = temp->data;
    head = head->next;
    delete temp;
    return true;
}

bool SinglyLinkedList::deleteFromEnd(int& removed) {
    if (head == nullptr) {
        return false;
    }
    if (head->next == nullptr) {
        return deleteFromBeginning(removed);
    }

    SNode* prev = head;
    SNode* cur = head->next;
    while (cur->next != nullptr) {
        prev = cur;
        cur = cur->next;
    }
    removed = cur->data;
    prev->next = nullptr;
    delete cur;
    return true;
}

bool SinglyLinkedList::deleteFromPosition(int pos, int& removed) {
    if (pos < 1 || head == nullptr) {
        return false;
    }
    if (pos == 1) {
        return deleteFromBeginning(removed);
    }

    // prev becomes the node just before the target (pos - 1).
    SNode* prev = head;
    int index = 1;
    while (prev != nullptr && index < pos - 1) {
        prev = prev->next;
        ++index;
    }
    if (prev == nullptr || prev->next == nullptr) {
        return false;
    }

    SNode* target = prev->next;
    removed = target->data;
    prev->next = target->next;
    delete target;
    return true;
}

bool SinglyLinkedList::deleteByValue(int value) {
    if (head == nullptr) {
        return false;
    }
    if (head->data == value) {
        int ignored;
        return deleteFromBeginning(ignored);
    }

    SNode* prev = head;
    SNode* cur = head->next;
    while (cur != nullptr) {
        if (cur->data == value) {
            prev->next = cur->next;
            delete cur;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

// ---------------------------------------------------------------------------
// Query and modification
// ---------------------------------------------------------------------------

int SinglyLinkedList::search(int value) const {
    int index = 1;
    for (SNode* cur = head; cur != nullptr; cur = cur->next, ++index) {
        if (cur->data == value) {
            return index;
        }
    }
    return 0;
}

bool SinglyLinkedList::update(int oldValue, int newValue) {
    for (SNode* cur = head; cur != nullptr; cur = cur->next) {
        if (cur->data == oldValue) {
            cur->data = newValue;
            return true;
        }
    }
    return false;
}

void SinglyLinkedList::display() const {
    if (head == nullptr) {
        std::cout << "List is empty.\n";
        return;
    }
    for (SNode* cur = head; cur != nullptr; cur = cur->next) {
        std::cout << cur->data << " -> ";
    }
    std::cout << "NULL\n";
}

int SinglyLinkedList::count() const {
    int total = 0;
    for (SNode* cur = head; cur != nullptr; cur = cur->next) {
        ++total;
    }
    return total;
}

bool SinglyLinkedList::findMaximum(int& result) const {
    if (head == nullptr) {
        return false;
    }
    result = head->data;
    for (SNode* cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->data > result) {
            result = cur->data;
        }
    }
    return true;
}

bool SinglyLinkedList::findMinimum(int& result) const {
    if (head == nullptr) {
        return false;
    }
    result = head->data;
    for (SNode* cur = head->next; cur != nullptr; cur = cur->next) {
        if (cur->data < result) {
            result = cur->data;
        }
    }
    return true;
}

// Slow/fast pointer method. For even-length lists this returns the FIRST
// of the two middle nodes (e.g. 10 -> 20 -> 30 -> 40 gives 20).
bool SinglyLinkedList::findMiddle(int& result) const {
    if (head == nullptr) {
        return false;
    }
    SNode* slow = head;
    SNode* fast = head;
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

void SinglyLinkedList::reverse() {
    SNode* prev = nullptr;
    SNode* cur = head;
    while (cur != nullptr) {
        SNode* next = cur->next;  // save the rest of the list
        cur->next = prev;         // flip the link
        prev = cur;               // advance prev
        cur = next;               // advance cur
    }
    head = prev;
}

// Beginner bubble sort: swap data values (links stay untouched).
void SinglyLinkedList::sort() {
    for (SNode* i = head; i != nullptr; i = i->next) {
        for (SNode* j = head; j->next != nullptr; j = j->next) {
            if (j->data > j->next->data) {
                std::swap(j->data, j->next->data);
            }
        }
    }
}

void SinglyLinkedList::removeDuplicates() {
    for (SNode* outer = head; outer != nullptr; outer = outer->next) {
        SNode* prev = outer;
        SNode* cur = outer->next;
        while (cur != nullptr) {
            if (cur->data == outer->data) {
                prev->next = cur->next;  // unlink the duplicate
                delete cur;
                cur = prev->next;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Menu
// ---------------------------------------------------------------------------

void SinglyLinkedList::runMenu() {
    int choice;
    do {
        std::cout << "\n********** Operation on Singly Linked List **********\n"
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
                  << "12. Display\n"
                  << "13. Count Nodes\n"
                  << "14. Find Maximum\n"
                  << "15. Find Minimum\n"
                  << "16. Find Middle Element\n"
                  << "17. Reverse\n"
                  << "18. Sort\n"
                  << "19. Remove Duplicates\n"
                  << "20. Exit\n";
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
                display();
                break;
            case 13:
                std::cout << "Number of nodes: " << count() << "\n";
                break;
            case 14:
                if (findMaximum(result)) {
                    std::cout << "Maximum: " << result << "\n";
                } else {
                    std::cout << "List is empty.\n";
                }
                break;
            case 15:
                if (findMinimum(result)) {
                    std::cout << "Minimum: " << result << "\n";
                } else {
                    std::cout << "List is empty.\n";
                }
                break;
            case 16:
                if (findMiddle(result)) {
                    std::cout << "Middle element: " << result
                              << " (for even length, the first of the two middle nodes)\n";
                } else {
                    std::cout << "List is empty.\n";
                }
                break;
            case 17:
                reverse();
                std::cout << "List reversed.\n";
                break;
            case 18:
                sort();
                std::cout << "List sorted in ascending order.\n";
                break;
            case 19:
                removeDuplicates();
                std::cout << "Duplicates removed.\n";
                break;
            case 20:
                std::cout << "Returning to main menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1 to 20.\n";
        }
    } while (choice != 20);
}
