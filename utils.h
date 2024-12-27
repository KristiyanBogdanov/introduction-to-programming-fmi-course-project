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
 * <file with the declaration of the utility functions>
 * 
*/

#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <cstddef> // Required for size_t

bool isPositive(const int number);
size_t readPositiveNumber(const char* message);
void readString(char* buffer, const size_t maxLength, const char* message);
char toLowerCase(const char c);
bool areCharsEqualIgnoreCase(const char first, const char second);
bool areStringsEqualIgnoreCase(const char* first, const char* second);
bool doesStringContainIgnoreCase(const char* string, const char* substring);

bool doesFileExist(const char* filename);

#endif