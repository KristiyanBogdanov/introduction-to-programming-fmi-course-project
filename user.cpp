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
 * <file with the implementation of the user-related functions>
 * 
*/

#include "user.h"
#include <iostream>

using namespace std;

const char* ACTION_DESCRIPTIONS[] = {
    "Add a movie",
    "Search by genre",
    "Search by title",
    "Print all movies",
    "Exit program",
};

const Action ADMIN_ACTIONS[] = {
    ADD_MOVIE,
    SEARCH_BY_GENRE,
    SEARCH_BY_TITLE,
    PRINT_ALL,
    EXIT_PROGRAM,
};

const Action USER_ACTIONS[] = {
    SEARCH_BY_GENRE,
    SEARCH_BY_TITLE,
    PRINT_ALL,
    EXIT_PROGRAM,
};

UserType chooseUserType() {
    const int adminValue = 1;
    const int userValue = 2;

    cout << "Please choose your user type:" << endl;
    cout << "[" << adminValue << "] Admin" << endl;
    cout << "[" << userValue << "] User" << endl;
    
    int choice;
    
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline left in the buffer

        switch (choice) {
            case adminValue:
                return ADMIN;
            case userValue:
                return USER;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

const Action* getActions(const UserType userType) {
    return userType == ADMIN ? ADMIN_ACTIONS : USER_ACTIONS;
}

size_t getActionsCount(const UserType userType) {
    return userType == ADMIN ? sizeof(ADMIN_ACTIONS) / sizeof(Action) 
                             : sizeof(USER_ACTIONS) / sizeof(Action);
}

Action selectAction(const UserType userType) {
    const Action* actions = getActions(userType);
    const size_t actionsCount = getActionsCount(userType);

    cout << "Please select an action:" << endl;

    for (size_t i = 0; i < actionsCount; ++i) {
        cout << "[" << i + 1 << "] " << ACTION_DESCRIPTIONS[actions[i]] << endl;
    }

    size_t choice;

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline left in the buffer

        if (choice < 1 || choice > actionsCount) {
            cout << "Invalid choice. Please try again." << endl;
        } else {
            return actions[choice - 1];
        }
    }
}