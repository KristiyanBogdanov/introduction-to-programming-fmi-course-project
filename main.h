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
 * <file with the declaration of the functions used in main.cpp>
 * 
*/

#ifndef MAIN_H
#define MAIN_H

#include "movie.h"
#include "user.h"

const char* MOVIES_FILENAME = "movies.txt";
const char* REVIEWS_FILENAME = "reviews.txt";

void executeAction(const Action action, MovieStorage& movies);
void printProgramHeader();
void addMovie(MovieStorage& movies);
void searchByGenre(const MovieStorage& movies);
MovieStorage searchByTitle_h(const MovieStorage& movies);
void searchByTitle(const MovieStorage& movies);
void printAll(const MovieStorage& movies);
void editMovieInfo(MovieStorage& movies);
void deleteMovie(MovieStorage& movies);
void sortMovies(const MovieStorage& movies);
void addReview(MovieStorage& movies);
void filterByRating(const MovieStorage& movies);

#endif