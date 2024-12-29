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
 * <file with the implementation of the functions in movie.h related to the dynamic array operations>
 * 
*/

#include "movie.h"

MovieStorage createMovieStorage() {
    MovieStorage array;

    array.data = new Movie*[INITIAL_CAPACITY];
    array.size = 0;
    array.capacity = INITIAL_CAPACITY;

    return array;
}

void resizeMovieStorage(MovieStorage& array) {
    Movie** newData = new Movie*[array.capacity + RESIZE_BUFFER];

    for (size_t i = 0; i < array.size; ++i) {
        newData[i] = array.data[i];
    }

    delete[] array.data;
    array.data = newData;

    array.capacity += RESIZE_BUFFER;
}

void addMovieToStorage(MovieStorage& array, Movie* element) {
    if (array.size == array.capacity) {
        resizeMovieStorage(array);
    }

    array.data[array.size++] = element;
}

void removeMovieFromStorage(MovieStorage& array, Movie* element) {
    size_t index = SIZE_MAX;

    for (size_t i = 0; i < array.size; ++i) {
        if (array.data[i] == element) {
            index = i;
            break;
        }
    }

    if (SIZE_MAX == index) {
        return;
    }

    for (size_t i = index; i < array.size - 1; ++i) {
        array.data[i] = array.data[i + 1];
    }

    --array.size;
    freeMovie(element);
}

void freeMovieStorage(MovieStorage& array) {
    delete[] array.data;
}

void freeAll(MovieStorage& array) {
    for (size_t i = 0; i < array.size; ++i) {
        freeMovie(array.data[i]);
    }

    freeMovieStorage(array);
}