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

size_t readPositiveNumber(const char* message, const size_t max) {
    int number;
    
    while (true) {
        cout << message;
        cin >> number;
        cin.ignore(); // Clear the newline left in the buffer

        if (isPositive(number) && number <= max) { // TODO: fix the warning
            return number;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

size_t myStrlen(const char* str) {
    size_t length = 0;

    while (str[length]) {
        ++length;
    }

    return length;
}

void readString(char* buffer, const size_t maxLength, const char* message) {
    cout << message;
    cin.getline(buffer, maxLength - 1);

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
    }
}

char toLowerCase(const char c) {
    return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

bool areCharsEqualIgnoreCase(const char first, const char second) {
    return toLowerCase(first) == toLowerCase(second);
}

int strcmpIgnoreCase(const char* first, const char* second) {
    while (*first && *second) {
        if (!areCharsEqualIgnoreCase(*first, *second)) {
            return toLowerCase(*first) - toLowerCase(*second);
        }

        ++first;
        ++second;
    }

    return toLowerCase(*first) - toLowerCase(*second);
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

bool askYesNo(const char* question) {
    char choice;

    cout << question << " (y/n): ";
    cin >> choice;
    cin.ignore(); // Clear the newline left in the buffer
    
    return areCharsEqualIgnoreCase(choice, 'y');
}

bool doesFileExist(const char* filename) {
    ifstream file(filename);
    return file.good();
}

void clearConsole() {
    #ifdef _WIN32
        system("cls"); // Clear console for Windows
    #elif __linux__ || __APPLE__
        system("clear"); // Clear console for Linux and macOS
    #endif
}