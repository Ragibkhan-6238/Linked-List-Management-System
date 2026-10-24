#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

// Reads an integer from standard input.
// Re-prompts on invalid input and exits cleanly if input is closed (EOF).
inline int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        if (std::cin.eof()) {
            std::cout << "\nInput closed. Exiting.\n";
            std::exit(0);
        }
        std::cout << "Invalid input. Please enter an integer.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

#endif
