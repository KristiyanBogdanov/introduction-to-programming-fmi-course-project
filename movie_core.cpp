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

Movie* askForMovieDetails() {
    Movie* movie = new Movie;

    readString(movie->title, MAX_TEXT_LENGTH, "Enter movie title: ");

    movie->year = readPositiveNumber("Enter movie year: ");

    readString(movie->genre, MAX_TEXT_LENGTH, "Enter movie genre: ");
    readString(movie->director, MAX_TEXT_LENGTH, "Enter movie director: ");

    movie->actorsCount = readPositiveNumber("Enter number of actors: ");
    movie->actors = new char[movie->actorsCount][MAX_TEXT_LENGTH];

    for (size_t i = 0; i < movie->actorsCount; ++i) {
        readString(movie->actors[i], MAX_TEXT_LENGTH, "Enter actor name: ");
    }

    movie->reviewsCount = 0;
    movie->rating = DEFAULT_RATING;

    return movie;
}

MovieStorage findMoviesByGenre(const MovieStorage& array, const char* genre) {
    MovieStorage result = createMovieStorage();

    for (size_t i = 0; i < array.size; ++i) {
        if (0 == strcmpIgnoreCase(array.data[i]->genre, genre)) {
            addMovieToStorage(result, array.data[i]);
        }
    }

    return result;
}

MovieStorage findMoviesByTitle(const MovieStorage& array, const char* title) {
    MovieStorage result = createMovieStorage();

    for (size_t i = 0; i < array.size; ++i) {
        if (doesStringContainIgnoreCase(array.data[i]->title, title)) {
            addMovieToStorage(result, array.data[i]);
        }
    }

    return result;
}

void printMovies(const MovieStorage& array) {
    if (0 == array.size) {
        cout << "No movies found." << endl;
        return;
    }

    cout << "Id" << COL_SEPARATOR
         << "Title" << COL_SEPARATOR 
         << "Year" << COL_SEPARATOR 
         << "Genre" << COL_SEPARATOR 
         << "Director" << COL_SEPARATOR 
         << "Number of reviews" << COL_SEPARATOR
         << "Rating" << COL_SEPARATOR 
         << "Actors" << endl;

    for (size_t i = 0; i < array.size; ++i) {
        cout << array.data[i]->id << COL_SEPARATOR
             << array.data[i]->title << COL_SEPARATOR 
             << array.data[i]->year << COL_SEPARATOR 
             << array.data[i]->genre << COL_SEPARATOR 
             << array.data[i]->director << COL_SEPARATOR
             << array.data[i]->reviewsCount << COL_SEPARATOR
             << array.data[i]->rating << COL_SEPARATOR;

        for (size_t j = 0; j < array.data[i]->actorsCount; ++j) {
            cout << array.data[i]->actors[j];

            if (j < array.data[i]->actorsCount - 1) {
                cout << SUB_SEPARATOR;
            }
        }

        cout << endl;
    }
}

void askForNewMovieDetails(Movie* movie) {
    if (askYesNo("Do you want to edit the movie title?")) {
        readString(movie->title, MAX_TEXT_LENGTH, "Enter new movie title: ");
    }

    if (askYesNo("Do you want to edit the movie year?")) {
        movie->year = readPositiveNumber("Enter new movie year: ");
    }

    if (askYesNo("Do you want to edit the movie genre?")) {
        readString(movie->genre, MAX_TEXT_LENGTH, "Enter new movie genre: ");
    }

    if (askYesNo("Do you want to edit the movie director?")) {
        readString(movie->director, MAX_TEXT_LENGTH, "Enter new movie director: ");
    }

    if (askYesNo("Do you want to edit the movie rating?")) {
        movie->rating = readPositiveNumber("Enter new movie rating: ");
    }

    if (askYesNo("Do you want to edit the movie actors?")) {
        movie->actorsCount = readPositiveNumber("Enter new number of actors: ");
        delete[] movie->actors;
        movie->actors = new char[movie->actorsCount][MAX_TEXT_LENGTH];

        for (size_t i = 0; i < movie->actorsCount; ++i) {
            readString(movie->actors[i], MAX_TEXT_LENGTH, "Enter actor name: ");
        }
    }
}

void swapMovies(Movie*& first, Movie*& second) {
    Movie* temp = first;
    first = second;
    second = temp;
}

bool compareByRatingDesc(const Movie* first, const Movie* second) {
    return first->rating < second->rating;
}

bool compareByTitleAsc(const Movie* first, const Movie* second) {
    return strcmpIgnoreCase(first->title, second->title) > 0;
}

MovieStorage sortMovies(const MovieStorage& array, bool (*compare)(const Movie*, const Movie*)) {
    MovieStorage result = copyMovieStorage(array);

    for (size_t i = 0; i < result.size - 1; ++i) {
        for (size_t j = 0; j < result.size - i - 1; ++j) {
            if (compare(result.data[j], result.data[j + 1])) {
                swapMovies(result.data[j], result.data[j + 1]);
            }
        }
    }

    return result;
}

void addReviewToMovie(Movie* movie, const Review& review) {
    movie->rating = (movie->rating * movie->reviewsCount + review.rating) / (movie->reviewsCount + 1);
    cout << "The new rating of the movie is: " << movie->rating << endl;
    ++movie->reviewsCount;
}

void freeMovie(Movie* movie) {
    delete[] movie->actors;
    delete movie;
}