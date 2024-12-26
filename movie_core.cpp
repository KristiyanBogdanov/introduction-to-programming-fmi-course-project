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

void freeMovie(Movie& movie) {
    delete[] movie.actors;
}