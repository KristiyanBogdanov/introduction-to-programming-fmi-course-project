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
#include <iostream>

using namespace std;

const char* DB_FILENAME = "movies.txt";

void printProgramHeader();

int main() {
    printProgramHeader();

    MovieStorage movies = createMovieStorage();
    int result = loadMoviesFromTextFile(movies, DB_FILENAME);

    if (-1 == result) {
        cout << "Error loading movies from file." << endl;
        freeMovieStorage(movies);
        return -1;
    }

    UserType userType = chooseUserType();
    Action action = selectAction(userType);

    switch (action) {
        case ADD_MOVIE: {
            Movie newMovie = askForMovieDetails();
            addMovie(movies, newMovie);
            break;
        }
        default:
            return 0;
    }

    result = saveMoviesToTextFile(movies, DB_FILENAME);

    if (-1 == result) {
        cout << "Error saving movies to file." << endl;
        freeMovieStorage(movies);
        return -1;
    }

    freeMovieStorage(movies);

    return 0;
}

void printProgramHeader() {
    cout << "Welcome to the program!" << endl;
    cout << "-----------------------" << endl;
}