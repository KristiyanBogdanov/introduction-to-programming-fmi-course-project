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
 * <file with the declaration of the dynamic array structure and related functions>
 * 
*/

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "movie.h"
#include <cstddef> // Required for size_t

const size_t INITIAL_CAPACITY = 10;
const size_t RESIZE_BUFFER = 2;

struct DynamicArray {
    Movie* data;
    size_t size;
    size_t capacity;
};

DynamicArray createDynamicArray();
void resizeDynamicArray(DynamicArray& array);
void addElement(DynamicArray& array, const Movie& element);
void freeDynamicArray(DynamicArray& array);

#endif