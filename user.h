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
 * <file with the declaration of the User-related enums and functions>
 * 
*/

#ifndef USER_H
#define USER_H

#include <cstddef> // Required for size_t

enum UserType {
    ADMIN,
    USER,
};

enum Action {
    ADD_MOVIE,
    SEARCH_BY_GENRE,
    SEARCH_BY_TITLE,
    PRINT_ALL,
    EDIT_MOVIE_INFO,
    DELETE_MOVIE,
    SORT_MOVIES,
    ADD_REVIEW,
    FILTER_BY_RATING,
    EXIT_PROGRAM,
};

extern const char* ACTION_DESCRIPTIONS[];
extern const Action ADMIN_ACTIONS[];
extern const Action USER_ACTIONS[];

// Function declarations
UserType chooseUserType();
const Action* getActions(const UserType userType);
size_t getActionsCount(const UserType userType);
Action selectAction(const UserType userType);

#endif