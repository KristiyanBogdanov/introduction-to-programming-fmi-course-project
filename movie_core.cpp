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
 * <file with the implementation of the core functions related to the Movie and MovieStorage structures>
 * 
*/

#include "movie.h"
#include "utils.h"
#include <iostream>

using namespace std;

Movie askForMovieDetails() {
    Movie movie;

    readString(movie.title, MAX_TEXT_LENGTH, "Enter movie title: ");

    movie.year = readPositiveNumber("Enter movie year: ");

    readString(movie.genre, MAX_TEXT_LENGTH, "Enter movie genre: ");
    readString(movie.director, MAX_TEXT_LENGTH, "Enter movie director: ");

    movie.actorsCount = readPositiveNumber("Enter number of actors: ");
    movie.actors = new char[movie.actorsCount][MAX_TEXT_LENGTH];

    for (size_t i = 0; i < movie.actorsCount; ++i) {
        readString(movie.actors[i], MAX_TEXT_LENGTH, "Enter actor name: ");
    }

    movie.rating = DEFAULT_RATING;

    return movie;
}

MovieStorage searchByGenre(const MovieStorage& array, const char* genre) {
    MovieStorage result = createMovieStorage();

    for (size_t i = 0; i < array.size; ++i) {
        if (areStringsEqual(array.data[i].genre, genre)) {
            addMovie(result, array.data[i]);
        }
    }

    return result;
}

void printMovies(const MovieStorage& array) {
    cout << "Title" << COL_SEPARATOR 
         << "Year" << COL_SEPARATOR 
         << "Genre" << COL_SEPARATOR 
         << "Director" << COL_SEPARATOR 
         << "Rating" << COL_SEPARATOR 
         << "Actors" << endl;

    for (size_t i = 0; i < array.size; ++i) {
        cout << array.data[i].title << COL_SEPARATOR 
             << array.data[i].year << COL_SEPARATOR 
             << array.data[i].genre << COL_SEPARATOR 
             << array.data[i].director << COL_SEPARATOR 
             << array.data[i].rating << COL_SEPARATOR;

        for (size_t j = 0; j < array.data[i].actorsCount; ++j) {
            cout << array.data[i].actors[j];

            if (j < array.data[i].actorsCount - 1) {
                cout << SUB_SEPARATOR;
            }
        }

        cout << endl;
    }
}

void freeMovie(Movie& movie) {
    delete[] movie.actors;
}