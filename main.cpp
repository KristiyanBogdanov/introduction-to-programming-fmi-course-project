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
 * <file with the main function>
 * 
*/

#include "user.h"
#include "movie.h"
#include "dynamic_array.h"
#include <iostream>

using namespace std;

void printProgramHeader();

int main() {
    DynamicArray movies = createDynamicArray();

    printProgramHeader();

    UserType userType = chooseUserType();
    Action action = selectAction(userType);

    switch (action) {
        case ADD_MOVIE: {
            Movie newMovie = askForMovieDetails();
            addElement(movies, newMovie);
            break;
        }
        default:
            return 0;
    }

    freeDynamicArray(movies);

    return 0;
}

void printProgramHeader() {
    cout << "Welcome to the program!" << endl;
    cout << "-----------------------" << endl;
}