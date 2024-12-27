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
 * <file with the declaration of the Movie structure and related functions>
 * 
*/

#ifndef MOVIE_H
#define MOVIE_H

#include <cstddef> // Required for size_t

// Movie structure constants
const size_t MAX_TEXT_LENGTH = 100;
const double DEFAULT_RATING = 5.0;

// MovieStorage structure constants
const size_t INITIAL_CAPACITY = 10;
const size_t RESIZE_BUFFER = 2;

// File operations constants
const char COL_SEPARATOR = ';';
const char SUB_SEPARATOR = ',';

struct Movie {
    char title[MAX_TEXT_LENGTH];
    size_t year;
    char genre[MAX_TEXT_LENGTH];
    char director[MAX_TEXT_LENGTH];
    size_t actorsCount;
    char (*actors)[MAX_TEXT_LENGTH];
    double rating;
};

struct MovieStorage {
    Movie* data;
    size_t size;
    size_t capacity;
};

Movie askForMovieDetails();
MovieStorage searchByGenre(const MovieStorage& array, const char* genre);
MovieStorage searchByTitle(const MovieStorage& array, const char* title);
void printMovies(const MovieStorage& array);
void freeMovie(Movie& movie);

MovieStorage createMovieStorage();
void resizeMovieStorage(MovieStorage& array);
void addMovie(MovieStorage& array, const Movie& element);
void freeMovieStorage(MovieStorage& array);

int saveMoviesToTextFile(const MovieStorage& array, const char* filename);
int loadMoviesFromTextFile(MovieStorage& array, const char* filename);

#endif