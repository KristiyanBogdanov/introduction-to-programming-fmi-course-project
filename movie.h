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

const size_t MAX_TEXT_LENGTH = 100;
const double DEFAULT_RATING = 5.0;

struct Movie {
    char title[MAX_TEXT_LENGTH];
    size_t year;
    char genre[MAX_TEXT_LENGTH];
    char director[MAX_TEXT_LENGTH];
    size_t actorsCount;
    char (*actors)[MAX_TEXT_LENGTH];
    double rating;
};

bool isPositive(const int number);
size_t readPositiveNumber(const char* message);
void readString(char* buffer, const char* message);
Movie askForMovieDetails();
void freeMovie(Movie& movie);

#endif