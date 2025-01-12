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
 * <file with the main function>
 * 
*/

#include "user.h"
#include "movie.h"
#include "utils.h"
#include <iostream>

using namespace std;

const char* MOVIES_FILENAME = "movies.txt";
const char* REVIEWS_FILENAME = "reviews.txt";

void printProgramHeader();
void addMovie(MovieStorage& movies);
void searchByGenre(const MovieStorage& movies);
MovieStorage searchByTitle_h(const MovieStorage& movies);
void searchByTitle(const MovieStorage& movies);
void printAll(const MovieStorage& movies);
void editMovieInfo(MovieStorage& movies);
void deleteMovie(MovieStorage& movies);
void sortMovies(MovieStorage& movies);
void addReview(MovieStorage& movies);

int main() {
    printProgramHeader();

    MovieStorage movies = createMovieStorage();
    int result = loadMoviesFromTextFile(movies, MOVIES_FILENAME);

    if (-1 == result) {
        cout << "Error loading movies from file." << endl;
        freeAll(movies);
        return -1;
    }

    UserType userType = chooseUserType();
    Action action = selectAction(userType);

    switch (action) {
        case ADD_MOVIE: {
            addMovie(movies);
            break;
        }
        case SEARCH_BY_GENRE: {
            searchByGenre(movies);
            break;
        }
        case SEARCH_BY_TITLE: {
            searchByTitle(movies);
            break;
        }
        case PRINT_ALL: {
            printAll(movies);
            break;
        }
        case EDIT_MOVIE_INFO: {
            editMovieInfo(movies);
            break;
        }
        case DELETE_MOVIE: {
            deleteMovie(movies);
            break;
        }
        case SORT_MOVIES: {
            sortMovies(movies);
            break;
        }
        case ADD_REVIEW: {
            addReview(movies);
            break;
        }
        default:
            break;
    }

    result = saveMoviesToTextFile(movies, MOVIES_FILENAME);

    if (-1 == result) {
        cout << "Error saving movies to file." << endl;
        freeAll(movies);
        return -1;
    }

    freeAll(movies);

    return 0;
}

void printProgramHeader() {
    cout << "Welcome to the program!" << endl;
    cout << "-----------------------" << endl;
}

void addMovie(MovieStorage& movies) {
    Movie* newMovie = askForMovieDetails();
    addMovieToStorage(movies, newMovie);
}

void searchByGenre(const MovieStorage& movies) {
    char genre[MAX_TEXT_LENGTH];
    readString(genre, MAX_TEXT_LENGTH, "Enter genre: ");

    MovieStorage result = findMoviesByGenre(movies, genre);
    printMovies(result);

    freeMovieStorage(result);
}

MovieStorage searchByTitle_h(const MovieStorage& movies) {
    char title[MAX_TEXT_LENGTH];
    readString(title, MAX_TEXT_LENGTH, "Enter title: ");

    MovieStorage result = findMoviesByTitle(movies, title);
    printMovies(result);

    return result;
}

void searchByTitle(const MovieStorage& movies) {
    MovieStorage result = searchByTitle_h(movies);
    freeMovieStorage(result);
}

void printAll(const MovieStorage& movies) {
    printMovies(movies);
}

void editMovieInfo(MovieStorage& movies) {
    MovieStorage result = searchByTitle_h(movies);

    if (result.size > 0) {
        size_t id = readPositiveNumber("Enter the id of the movie you want to edit: ", result.size);
        askForNewMovieDetails(result.data[id - 1]);
    }

    freeMovieStorage(result);
}

void deleteMovie(MovieStorage& movies) {
    MovieStorage result = searchByTitle_h(movies);

    if (result.size > 0) {
        size_t id = readPositiveNumber("Enter the id of the movie you want to delete: ", result.size);
        removeMovieFromStorage(movies, result.data[id - 1]);
    }

    freeMovieStorage(result);
}

void sortMovies(MovieStorage& movies) {
    cout << "Please choose the sorting criteria:" << endl;
    cout << "[1] By rating (descending)" << endl;
    cout << "[2] By title (ascending)" << endl;

    int choice = readPositiveNumber("Enter your choice: ", 2);
    MovieStorage result;

    switch (choice) {
        case 1:
            result = sortMovies(movies, compareByRatingDesc);
            break;
        case 2:
            result = sortMovies(movies, compareByTitleAsc);
            break;
        default:
            break;
    }

    printMovies(result);
    freeMovieStorage(result);
}

void addReview(MovieStorage& movies) {
    MovieStorage result = searchByTitle_h(movies);

    if (result.size > 0) {
        size_t index = readPositiveNumber("Enter the id of the movie you want to review: ", result.size);
        size_t rating = readPositiveNumber("Enter the rating: ", MAX_RATING);

        Review newReview;
        newReview.movieId = result.data[index - 1]->id;
        newReview.rating = rating;

        addReviewToMovie(result.data[index - 1], newReview);
        addReviewToTextFile(newReview, REVIEWS_FILENAME);
    }

    freeMovieStorage(result);
}