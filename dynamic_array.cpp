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
 * <file with the implementation of the dynamic array structure and related functions>
 * 
*/

#include "dynamic_array.h"

DynamicArray createDynamicArray() {
    DynamicArray array;

    array.data = new Movie[INITIAL_CAPACITY];
    array.size = 0;
    array.capacity = INITIAL_CAPACITY;

    return array;
}

void resizeDynamicArray(DynamicArray& array) {
    Movie* newData = new Movie[array.capacity + RESIZE_BUFFER];

    for (size_t i = 0; i < array.size; ++i) {
        newData[i] = array.data[i];
    }

    delete[] array.data;
    array.data = newData;

    array.capacity += RESIZE_BUFFER;
}

void addElement(DynamicArray& array, const Movie& element) {
    if (array.size == array.capacity) {
        resizeDynamicArray(array);
    }

    array.data[array.size++] = element;
}

void freeDynamicArray(DynamicArray& array) {
    for (size_t i = 0; i < array.size; ++i) {
        freeMovie(array.data[i]);
    }

    delete[] array.data;
}