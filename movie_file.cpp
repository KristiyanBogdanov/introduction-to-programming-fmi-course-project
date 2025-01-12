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
 * <file with the implementation of the functions in movie.h related to the file operations>
 * 
*/

#include "movie.h"
#include "utils.h"
#include <fstream>
#include <iostream>

using namespace std;

int saveMoviesToTextFile(const MovieStorage& array, const char* filename) {
    ofstream file(filename, ios::out);

    if (!file.is_open()) {
        return -1;
    }

    file << array.size << endl;

    for (size_t i = 0; i < array.size; ++i) {
        file << array.data[i]->id << COL_SEPARATOR
             << array.data[i]->title << COL_SEPARATOR
             << array.data[i]->year << COL_SEPARATOR
             << array.data[i]->genre << COL_SEPARATOR
             << array.data[i]->director << COL_SEPARATOR
             << array.data[i]->reviewsCount << COL_SEPARATOR
             << array.data[i]->rating << COL_SEPARATOR
             << array.data[i]->actorsCount << COL_SEPARATOR;

        for (size_t j = 0; j < array.data[i]->actorsCount; ++j) {
            file << array.data[i]->actors[j] << SUB_SEPARATOR;
        }

        file << endl;
    }

    file.close();

    return 0;
}

int loadMoviesFromTextFile(MovieStorage& array, const char* filename) {
    ifstream file(filename, ios::in);

    if (!doesFileExist(filename)) {
        return 0;
    }

    if (file.peek() == ifstream::traits_type::eof()) {
        file.close();
        return 0;
    }

    if (!file.is_open()) {
        return -1;
    }

    size_t size;
    file >> size;
    file.ignore(); // Clear the newline left in the buffer

    for (size_t i = 0; i < size; ++i) {
        Movie* movie = new Movie;

        file >> movie->id;
        file.ignore(); // Clear the newline left in the buffer

        file.getline(movie->title, MAX_TEXT_LENGTH, COL_SEPARATOR);
        file >> movie->year;
        file.ignore(); // Clear the newline left in the buffer

        file.getline(movie->genre, MAX_TEXT_LENGTH, COL_SEPARATOR);
        file.getline(movie->director, MAX_TEXT_LENGTH, COL_SEPARATOR);

        file >> movie->reviewsCount;
        file.ignore(); // Clear the newline left in the buffer
        file >> movie->rating;
        file.ignore(); // Clear the newline left in the buffer

        file >> movie->actorsCount;
        file.ignore(); // Clear the newline left in the buffer

        movie->actors = new char[movie->actorsCount][MAX_TEXT_LENGTH];

        for (size_t j = 0; j < movie->actorsCount; ++j) {
            file.getline(movie->actors[j], MAX_TEXT_LENGTH, SUB_SEPARATOR);
        }

        addMovieToStorage(array, movie);

        file.ignore();
    }

    file.close();

    return 0;
}

int addReviewToTextFile(const Review& review, const char* filename) {
    ofstream file(filename, ios::app);

    if (!file.is_open()) {
        return -1;
    }

    file << review.movieId << COL_SEPARATOR << review.rating << endl;

    file.close();

    return 0;
}