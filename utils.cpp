/**
 * Solution to course project # 6
 * Introduction to rpogramming course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2023/2024
 * 
 * @author Kristiyan Bogdanov
 * @idnumber 4MI0600438
 * @compiler GCC
 * 
 * <file with the implementation of the utility functions>
 * 
*/

#include "utils.h"
#include <iostream>

using namespace std;

bool isPositive(const int number) {
    return number > 0;
}

size_t readPositiveNumber(const char* message) {
    int number;
    
    while (true) {
        cout << message;
        cin >> number;
        cin.ignore(); // Clear the newline left in the buffer

        if (isPositive(number)) {
            return number;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

void readString(char* buffer, const size_t maxLength, const char* message) {
    cout << message;
    cin.getline(buffer, maxLength);
}

char toLowerCase(const char c) {
    return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

bool areCharsEqualIgnoreCase(const char first, const char second) {
    return toLowerCase(first) == toLowerCase(second);
}

bool areStringsEqualIgnoreCase(const char* first, const char* second) {
    while (*first && *second) {
        if (!areCharsEqualIgnoreCase(*first, *second)) {
            return false;
        }

        ++first;
        ++second;
    }

    return *first == *second;
}

bool doesStringContainIgnoreCase(const char* string, const char* substring) {
    while (*string) {
        const char* stringStart = string;
        const char* substringStart = substring;

        while (*string && *substring && areCharsEqualIgnoreCase(*string, *substring)) {
            ++string;
            ++substring;
        }

        if (!*substring) {
            return true;
        }

        string = stringStart + 1;
        substring = substringStart;
    }

    return false;
}

bool doesFileExist(const char* filename) {
    ifstream file(filename);
    return file.good();
}