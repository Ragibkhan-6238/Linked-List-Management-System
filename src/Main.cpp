#include <iostream>

#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"
#include "Utils.h"

// Prints a side-by-side comparison of the two implementations.
static void printComparison() {
    std::cout << "\n========== Singly vs Doubly Linked List ==========\n"
              << "Node structure : Singly -> data, next\n"
              << "                 Doubly -> data, prev, next\n"
              << "Head pointer   : Both have head\n"
              << "Tail pointer   : Singly -> not kept (append is O(n))\n"
              << "                 Doubly -> kept (append is O(1))\n\n"
              << "Operation               Singly     Doubly\n"
              << "----------------------------------------\n"
              << "Insert at beginning     O(1)       O(1)\n"
              << "Insert at end           O(n)       O(1)\n"
              << "Delete from beginning   O(1)       O(1)\n"
              << "Delete from end         O(n)       O(1)\n"
              << "Delete a given node     O(n)       O(1) once node is known\n"
              << "Search / Display        O(n)       O(n)\n"
              << "Display backward        N/A        O(n)\n"
              << "Reverse                 O(n)       O(n) (swap prev/next)\n"
              << "Memory per node         Less       More (extra prev link)\n"
              << "Pointer management      Simpler    More links to keep correct\n"
              << "==================================================\n";
}

int main() {
    SinglyLinkedList singly;
    DoublyLinkedList doubly;

    std::cout << "\n==================================================\n"
              << " LINKED LIST MANAGEMENT SYSTEM\n"
              << "==================================================\n";

    int choice;
    do {
        std::cout << "\n1. Singly Linked List\n"
                  << "2. Doubly Linked List\n"
                  << "3. Compare Singly vs Doubly Linked List\n"
                  << "4. Exit\n";
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                singly.runMenu();
                break;
            case 2:
                doubly.runMenu();
                break;
            case 3:
                printComparison();
                break;
            case 4:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please select 1 to 4.\n";
        }
    } while (choice != 4);

    return 0;
}
