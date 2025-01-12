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
#include <cstdint> // Required for SIZE_MAX

// Movie structure constants
const size_t MAX_TEXT_LENGTH = 100;
const double DEFAULT_RATING = 5.0;
const size_t MAX_RATING = 10;

// MovieStorage structure constants
const size_t INITIAL_CAPACITY = 10;
const size_t RESIZE_BUFFER = 2;

// File operations constants
const char COL_SEPARATOR = ';';
const char SUB_SEPARATOR = ',';

struct Movie {
    size_t id;
    char title[MAX_TEXT_LENGTH];
    size_t year;
    char genre[MAX_TEXT_LENGTH];
    char director[MAX_TEXT_LENGTH];
    size_t actorsCount;
    char (*actors)[MAX_TEXT_LENGTH];
    size_t reviewsCount;
    double rating;
};

struct Review {
    size_t movieId;
    double rating;
};

struct MovieStorage {
    Movie** data;
    size_t size;
    size_t capacity;
};

Movie* askForMovieDetails();
MovieStorage findMoviesByGenre(const MovieStorage& array, const char* genre);
MovieStorage findMoviesByTitle(const MovieStorage& array, const char* title);
void printMovies(const MovieStorage& array);
void askForNewMovieDetails(Movie* movie);
void swapMovies(Movie*& first, Movie*& second);
bool compareByRatingDesc(const Movie* first, const Movie* second);
bool compareByTitleAsc(const Movie* first, const Movie* second);
MovieStorage sortMovies(const MovieStorage& array, bool (*compare)(const Movie*, const Movie*));
void addReviewToMovie(Movie* movie, const Review& review);
void freeMovie(Movie* movie);

MovieStorage createMovieStorage(size_t initialCapacity = INITIAL_CAPACITY);
void resizeMovieStorage(MovieStorage& array);
void addMovieToStorage(MovieStorage& array, Movie* element);
void removeMovieFromStorage(MovieStorage& array, Movie* element);
MovieStorage copyMovieStorage(const MovieStorage& array);
void freeMovieStorage(MovieStorage& array);
void freeAll(MovieStorage& array);

int saveMoviesToTextFile(const MovieStorage& array, const char* filename);
int loadMoviesFromTextFile(MovieStorage& array, const char* filename);
int addReviewToTextFile(const Review& review, const char* filename);

#endif