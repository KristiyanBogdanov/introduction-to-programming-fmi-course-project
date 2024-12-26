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
 * <file with the implementation of the functions related to the Movie structure>
 * 
*/

#include "movie.h"
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

void readString(char* buffer, const char* message) {
    cout << message;
    cin.getline(buffer, MAX_TEXT_LENGTH);
}

Movie askForMovieDetails() {
    Movie movie;

    readString(movie.title, "Enter movie title: ");

    movie.year = readPositiveNumber("Enter movie year: ");
    
    readString(movie.genre, "Enter movie genre: ");
    readString(movie.director, "Enter movie director: ");

    movie.actorsCount = readPositiveNumber("Enter number of actors: ");
    movie.actors = new char[movie.actorsCount][MAX_TEXT_LENGTH];

    for (size_t i = 0; i < movie.actorsCount; ++i) {
        readString(movie.actors[i], "Enter actor name: ");
    }

    movie.rating = DEFAULT_RATING;

    return movie;
}

void freeMovie(Movie& movie) {
    delete[] movie.actors;
}