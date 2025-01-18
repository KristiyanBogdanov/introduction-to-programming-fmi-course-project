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
 * <file containing the source code of the program>
 * 
*/

// ==========
// Libraries:
// ==========

#include <iostream>
#include <fstream>
#include <cmath> // Include <cmath> library to use the log10() function.

// Include <iomanip> library to use the std::fixed and std::setprecision() functions.
// The std::fixed function is used to display the floating-point numbers in fixed-point notation.
// The std::setprecision() function is used to set the number of decimal places to display for the floating-point numbers.
// If I don't use them my custom padding functions (alternative to std::setw()) will not work perfectly.
#include <iomanip>

// Include the <limits> library to use the numeric_limits<streamsize>::max() constant.
// This constant is used to clear the buffer in the readString() function when the user enters string with more characters than the buffer can hold.
// If I don't clear the buffer, the program will enter an infinite loop because the cin.fail() condition will always be true.
#include <limits>

using namespace std;

// ==========
// Constants:
// ==========

// Movie structure constants
const size_t MAX_TEXT_LENGTH = 30;
const double DEFAULT_RATING = 5.0; // The used type is double because the field is used for storing the average rating of the movie
const size_t MAX_RATING = 10; // The used type is size_t because the rating system follows the logic of the real IMDb where the rating is between 1 and 10 (whole numbers)

// MovieStorage structure constants
const size_t INITIAL_CAPACITY = 10;
const size_t RESIZE_BUFFER = 2;

// File operations constants
const char COL_SEPARATOR = ';';
const char SUB_SEPARATOR = ',';

// File names
const char* MOVIES_FILENAME = "movies.txt";
const char* REVIEWS_FILENAME = "reviews.txt";

// =====================
// Structures and enums:
// =====================

enum UserType {
    ADMIN,
    USER,
};

enum Action {
    ADD_MOVIE,
    SEARCH_BY_GENRE,
    SEARCH_BY_TITLE,
    PRINT_ALL,
    EDIT_MOVIE_INFO,
    DELETE_MOVIE,
    SORT_MOVIES,
    ADD_REVIEW,
    FILTER_BY_RATING,
    EXIT_PROGRAM,
};

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

// Dynamic array of pointers to Movie structures.
struct MovieStorage {
    Movie** data;
    size_t size;
    size_t capacity;
};

// =============
// Role actions:
// =============

const char* ACTION_DESCRIPTIONS[] = {
    "Add a movie",
    "Search by genre",
    "Search by title",
    "Print all movies",
    "Edit movie info",
    "Delete a movie",
    "Sort movies",
    "Add a review",
    "Filter by rating",
    "Exit program",
};

const Action ADMIN_ACTIONS[] = {
    ADD_MOVIE,
    SEARCH_BY_GENRE,
    SEARCH_BY_TITLE,
    PRINT_ALL,
    EDIT_MOVIE_INFO,
    DELETE_MOVIE,
    SORT_MOVIES,
    FILTER_BY_RATING,
    EXIT_PROGRAM,
};

const Action USER_ACTIONS[] = {
    SEARCH_BY_GENRE,
    SEARCH_BY_TITLE,
    PRINT_ALL,
    SORT_MOVIES,
    ADD_REVIEW,
    FILTER_BY_RATING,
    EXIT_PROGRAM,
};

// =================
// Global variables:
// =================

// This counter is used to generate unique IDs for the movies. It is incremented each time a new movie is added.
// It follows the logic of the auto-incremented primary key in a database.
size_t MOVIES_ID_COUNTER = 0;

// ======================
// Function declarations:
// ======================

// Main functions:
int executeAction(const Action action, MovieStorage& movies);
void printProgramHeader();
int addMovie(MovieStorage& movies);
int searchByGenre(const MovieStorage& movies);
MovieStorage searchByTitle_h(const MovieStorage& movies);
int searchByTitle(const MovieStorage& movies);
int printAll(const MovieStorage& movies);
int editMovieInfo(MovieStorage& movies);
int deleteMovie(MovieStorage& movies);
int sortMovies(const MovieStorage& movies);
int addReview(MovieStorage& movies);
int filterByRating(const MovieStorage& movies);

// UserType related functions:
UserType chooseUserType();
const Action* getActions(const UserType userType);
size_t getActionsCount(const UserType userType);
Action selectAction(const UserType userType);

// Movie structure related functions:
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
MovieStorage filterMoviesByRating(const MovieStorage& array, const double rating);
void freeMovie(Movie* movie);

// MovieStorage structure related functions:
MovieStorage createMovieStorage(size_t initialCapacity = INITIAL_CAPACITY);
void resizeMovieStorage(MovieStorage& array);
void addMovieToStorage(MovieStorage& array, Movie* element);
void removeMovieFromStorage(MovieStorage& array, Movie* element);
MovieStorage copyMovieStorage(const MovieStorage& array);
void freeMovieStorage(MovieStorage& array);
void freeAll(MovieStorage& array);

// File operations related functions:
int saveMoviesToTextFile(const MovieStorage& array, const char* filename);
int loadMoviesFromTextFile(MovieStorage& array, const char* filename);
int addReviewToTextFile(const Review& review, const char* filename);

// Utility functions:
bool isPositive(const int number);
size_t readPositiveNumber(const char* message, const size_t max = SIZE_MAX); // SIZE_MAX is the maximum value of size_t
size_t myStrlen(const char* str);
bool doesStringContainsDelimiter(const char* string); // Checks if the string contains one of the delimiters defined in the constants section
void readString(char* buffer, const size_t maxLength, const char* message);
char toLowerCase(const char c);
bool areCharsEqualIgnoreCase(const char first, const char second);
int strcmpIgnoreCase(const char* first, const char* second);
bool doesStringContainIgnoreCase(const char* string, const char* substring);
bool askYesNo(const char* question);
size_t countDigits(size_t number);
void padText(const char* text, const size_t width);
void padPositiveInt(const int number, const size_t width);
void padDouble(const double number, const size_t width, const size_t precision);
void clearConsole();

// ==============
// Main function:
// ==============

int main() {
    printProgramHeader();

    MovieStorage movies = createMovieStorage();
    int result = loadMoviesFromTextFile(movies, MOVIES_FILENAME);

    if (-1 == result) {
        freeAll(movies);
        return -1;
    }

    UserType userType = chooseUserType();
    clearConsole();

    while (true) {
        Action action = selectAction(userType);

        if (EXIT_PROGRAM == action) {
            break;
        }

        clearConsole();
        
        if (-1 == executeAction(action, movies)) {
            break; // An error occurred
        }

        cout << endl;
        cout << "Press Enter to continue...";
        cin.get();
        clearConsole();
    }

    freeAll(movies);

    return 0;
}

// =====================
// Function definitions:
// =====================

// Main functions:

int executeAction(const Action action, MovieStorage& movies) {
    switch (action) {
        case ADD_MOVIE: {
            return addMovie(movies);
        }
        case SEARCH_BY_GENRE: {
            return searchByGenre(movies);
        }
        case SEARCH_BY_TITLE: {
            return searchByTitle(movies);
        }
        case PRINT_ALL: {
            return printAll(movies);
        }
        case EDIT_MOVIE_INFO: {
            return editMovieInfo(movies);
        }
        case DELETE_MOVIE: {
            return deleteMovie(movies);
        }
        case SORT_MOVIES: {
            return sortMovies(movies);
        }
        case ADD_REVIEW: {
            return addReview(movies);
        }
        case FILTER_BY_RATING: {
            return filterByRating(movies);
        }
        default:
            return 0;
    }
}

void printProgramHeader() {
    cout << "Welcome to the program!" << endl;
    cout << "-----------------------" << endl;
}

int addMovie(MovieStorage& movies) {
    Movie* newMovie = askForMovieDetails();
    addMovieToStorage(movies, newMovie);
    return saveMoviesToTextFile(movies, MOVIES_FILENAME);
}

int searchByGenre(const MovieStorage& movies) {
    char genre[MAX_TEXT_LENGTH];
    readString(genre, MAX_TEXT_LENGTH, "Enter genre: ");
    cout << endl;

    MovieStorage result = findMoviesByGenre(movies, genre);
    printMovies(result);

    freeMovieStorage(result);

    return 0;
}

MovieStorage searchByTitle_h(const MovieStorage& movies) {
    char title[MAX_TEXT_LENGTH];
    readString(title, MAX_TEXT_LENGTH, "Enter title: ");
    cout << endl;

    MovieStorage result = findMoviesByTitle(movies, title);
    printMovies(result);

    return result;
}

int searchByTitle(const MovieStorage& movies) {
    MovieStorage result = searchByTitle_h(movies);

    freeMovieStorage(result);
    
    return 0;
}

int printAll(const MovieStorage& movies) {
    printMovies(movies);

    return 0;
}

int editMovieInfo(MovieStorage& movies) {
    int success = 0;
    
    MovieStorage result = searchByTitle_h(movies);
    cout << endl;

    if (result.size > 0) {
        size_t idx = readPositiveNumber("Enter the No. of the movie you want to edit: ", result.size);
        askForNewMovieDetails(result.data[idx - 1]);
        success = saveMoviesToTextFile(movies, MOVIES_FILENAME);
    }

    freeMovieStorage(result);

    return success;
}

int deleteMovie(MovieStorage& movies) {
    int success = 0;
    
    MovieStorage result = searchByTitle_h(movies);
    cout << endl;

    if (result.size > 0) {
        size_t idx = readPositiveNumber("Enter the No. of the movie you want to delete: ", result.size);
        removeMovieFromStorage(movies, result.data[idx - 1]);
        success = saveMoviesToTextFile(movies, MOVIES_FILENAME);
    }

    freeMovieStorage(result);

    return success;
}

int sortMovies(const MovieStorage& movies) {
    const int sortByRatingValue = 1;
    const int sortByTitleValue = 2;

    cout << "Please choose the sorting criteria:" << endl;
    cout << "[" << sortByRatingValue << "] By rating (descending)" << endl;
    cout << "[" << sortByTitleValue << "] By title (ascending)" << endl;

    int choice = readPositiveNumber("Enter your choice: ", sortByTitleValue);
    cout << endl;

    MovieStorage result;

    switch (choice) {
        case sortByRatingValue:
            result = sortMovies(movies, compareByRatingDesc);
            break;
        case sortByTitleValue:
            result = sortMovies(movies, compareByTitleAsc);
            break;
        default:
            break;
    }

    printMovies(result);
    freeMovieStorage(result);

    return 0;
}

int addReview(MovieStorage& movies) {
    int addReviewSuccess = 0;
    int saveMoviesSuccess = 0;

    MovieStorage result = searchByTitle_h(movies);
    cout << endl;

    if (result.size > 0) {
        size_t idx = readPositiveNumber("Enter the No. of the movie you want to review: ", result.size);
        size_t rating = readPositiveNumber("Enter the rating: ", MAX_RATING);

        Review newReview;
        newReview.movieId = result.data[idx - 1]->id;
        newReview.rating = rating;

        addReviewToMovie(result.data[idx - 1], newReview);
        addReviewSuccess = addReviewToTextFile(newReview, REVIEWS_FILENAME);
        saveMoviesSuccess = saveMoviesToTextFile(movies, MOVIES_FILENAME);
    }

    freeMovieStorage(result);

    return (addReviewSuccess == 0 && saveMoviesSuccess == 0) ? 0 : -1;
}

int filterByRating(const MovieStorage& movies) {
    size_t rating = readPositiveNumber("Enter the rating: ", MAX_RATING);
    MovieStorage result = filterMoviesByRating(movies, rating);

    printMovies(result);
    freeMovieStorage(result);

    return 0;
}

// UserType related functions:

UserType chooseUserType() {
    const int adminValue = 1;
    const int userValue = 2;

    cout << "Please choose your user type:" << endl;
    cout << "[" << adminValue << "] Admin" << endl;
    cout << "[" << userValue << "] User" << endl;
    
    int choice;
    
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline left in the buffer

        switch (choice) {
            case adminValue:
                return ADMIN;
            case userValue:
                return USER;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}

const Action* getActions(const UserType userType) {
    return userType == ADMIN ? ADMIN_ACTIONS : USER_ACTIONS;
}

size_t getActionsCount(const UserType userType) {
    return userType == ADMIN ? sizeof(ADMIN_ACTIONS) / sizeof(Action) 
                             : sizeof(USER_ACTIONS) / sizeof(Action);
}

Action selectAction(const UserType userType) {
    const Action* actions = getActions(userType);
    const size_t actionsCount = getActionsCount(userType);

    cout << "Please select an action:" << endl;

    for (size_t i = 0; i < actionsCount; ++i) {
        cout << "[" << i + 1 << "] " << ACTION_DESCRIPTIONS[actions[i]] << endl;
    }

    size_t choice;

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline left in the buffer

        if (choice < 1 || choice > actionsCount) {
            cout << "Invalid choice. Please try again." << endl;
        } else {
            return actions[choice - 1];
        }
    }
}

// Movie structure related functions:

Movie* askForMovieDetails() {
    Movie* movie = new Movie;
    
    movie->id = ++MOVIES_ID_COUNTER;

    readString(movie->title, MAX_TEXT_LENGTH, "Enter movie title: ");

    movie->year = readPositiveNumber("Enter movie year: ");

    readString(movie->genre, MAX_TEXT_LENGTH, "Enter movie genre: ");
    readString(movie->director, MAX_TEXT_LENGTH, "Enter movie director: ");

    movie->actorsCount = readPositiveNumber("Enter number of actors: ");
    movie->actors = new char[movie->actorsCount][MAX_TEXT_LENGTH];

    for (size_t i = 0; i < movie->actorsCount; ++i) {
        readString(movie->actors[i], MAX_TEXT_LENGTH, "Enter actor name: ");
    }

    movie->reviewsCount = 0;
    movie->rating = DEFAULT_RATING;

    return movie;
}

MovieStorage findMoviesByGenre(const MovieStorage& array, const char* genre) {
    MovieStorage result = createMovieStorage();

    for (size_t i = 0; i < array.size; ++i) {
        if (0 == strcmpIgnoreCase(array.data[i]->genre, genre)) {
            addMovieToStorage(result, array.data[i]);
        }
    }

    return result;
}

MovieStorage findMoviesByTitle(const MovieStorage& array, const char* title) {
    MovieStorage result = createMovieStorage();

    for (size_t i = 0; i < array.size; ++i) {
        if (doesStringContainIgnoreCase(array.data[i]->title, title)) {
            addMovieToStorage(result, array.data[i]);
        }
    }

    return result;
}

void printMovies(const MovieStorage& array) {
    if (0 == array.size) {
        cout << "No movies found." << endl;
        return;
    }

    // Column widths
    const size_t SPACE_WIDTH = 2;
    const size_t NUM_PERCISION = 1;
    const size_t ROW_NUMBER_WIDTH = countDigits(array.size) + myStrlen("No.") + SPACE_WIDTH;
    const size_t ID_WIDTH = countDigits(MOVIES_ID_COUNTER) + myStrlen("UID") + SPACE_WIDTH;
    const size_t TITLE_WIDTH = MAX_TEXT_LENGTH + SPACE_WIDTH;
    const size_t YEAR_WIDTH = myStrlen("Year") + SPACE_WIDTH;
    const size_t GENRE_WIDTH = MAX_TEXT_LENGTH + SPACE_WIDTH;
    const size_t DIRECTOR_WIDTH = MAX_TEXT_LENGTH + SPACE_WIDTH;
    const size_t REVIEWS_WIDTH = myStrlen("Reviews") + SPACE_WIDTH;
    const size_t RATING_WIDTH = myStrlen("Rating") + SPACE_WIDTH;

    const size_t WIDTH_SUM = ROW_NUMBER_WIDTH + ID_WIDTH + TITLE_WIDTH + YEAR_WIDTH +
                         GENRE_WIDTH + DIRECTOR_WIDTH + REVIEWS_WIDTH + RATING_WIDTH +
                         myStrlen("Actors");

    // Print the header
    padText("No.", ROW_NUMBER_WIDTH);
    padText("UID", ID_WIDTH);
    padText("Title", TITLE_WIDTH);
    padText("Year", YEAR_WIDTH);
    padText("Genre", GENRE_WIDTH);
    padText("Director", DIRECTOR_WIDTH);
    padText("Reviews", REVIEWS_WIDTH);
    padText("Rating", RATING_WIDTH);
    cout << "Actors" << endl;

    // Print the separator
    for (size_t i = 0; i < WIDTH_SUM; ++i) {
        cout << '-';
    }

    cout << endl;

    // Print the movies
    for (size_t i = 0; i < array.size; ++i) {
        padPositiveInt(i + 1, ROW_NUMBER_WIDTH);
        padPositiveInt(array.data[i]->id, ID_WIDTH);
        padText(array.data[i]->title, TITLE_WIDTH);
        padPositiveInt(array.data[i]->year, YEAR_WIDTH);
        padText(array.data[i]->genre, GENRE_WIDTH);
        padText(array.data[i]->director, DIRECTOR_WIDTH);
        padPositiveInt(array.data[i]->reviewsCount, REVIEWS_WIDTH);
        padDouble(array.data[i]->rating, RATING_WIDTH, NUM_PERCISION);
        
        for (size_t j = 0; j < array.data[i]->actorsCount; ++j) {
            cout << array.data[i]->actors[j];

            if (j < array.data[i]->actorsCount - 1) {
                cout << SUB_SEPARATOR;
            }
        }

        cout << endl;
    }
}

void askForNewMovieDetails(Movie* movie) {
    if (nullptr == movie) {
        return;
    }

    if (askYesNo("Do you want to edit the movie title?")) {
        readString(movie->title, MAX_TEXT_LENGTH, "Enter new movie title: ");
    }

    if (askYesNo("Do you want to edit the movie year?")) {
        movie->year = readPositiveNumber("Enter new movie year: ");
    }

    if (askYesNo("Do you want to edit the movie genre?")) {
        readString(movie->genre, MAX_TEXT_LENGTH, "Enter new movie genre: ");
    }

    if (askYesNo("Do you want to edit the movie director?")) {
        readString(movie->director, MAX_TEXT_LENGTH, "Enter new movie director: ");
    }

    if (askYesNo("Do you want to edit the movie rating?")) {
        movie->rating = readPositiveNumber("Enter new movie rating: ");
    }

    if (askYesNo("Do you want to edit the movie actors?")) {
        movie->actorsCount = readPositiveNumber("Enter new number of actors: ");
        delete[] movie->actors;
        movie->actors = new char[movie->actorsCount][MAX_TEXT_LENGTH];

        for (size_t i = 0; i < movie->actorsCount; ++i) {
            readString(movie->actors[i], MAX_TEXT_LENGTH, "Enter actor name: ");
        }
    }
}

void swapMovies(Movie*& first, Movie*& second) {
    Movie* temp = first;
    first = second;
    second = temp;
}

bool compareByRatingDesc(const Movie* first, const Movie* second) {
    if (nullptr == first || nullptr == second) {
        return false;
    }

    return first->rating < second->rating;
}

bool compareByTitleAsc(const Movie* first, const Movie* second) {
    if (nullptr == first || nullptr == second) {
        return false;
    }

    return strcmpIgnoreCase(first->title, second->title) > 0;
}

MovieStorage sortMovies(const MovieStorage& array, bool (*compare)(const Movie*, const Movie*)) {
    MovieStorage result = copyMovieStorage(array);

    // Bubble sort algorithm
    for (size_t i = 0; i < result.size - 1; ++i) {
        for (size_t j = 0; j < result.size - i - 1; ++j) {
            if (compare(result.data[j], result.data[j + 1])) {
                swapMovies(result.data[j], result.data[j + 1]);
            }
        }
    }

    return result;
}

void addReviewToMovie(Movie* movie, const Review& review) {
    if (nullptr == movie) {
        return;
    }

    movie->rating = (movie->rating * movie->reviewsCount + review.rating) / (movie->reviewsCount + 1);
    ++movie->reviewsCount;
}

MovieStorage filterMoviesByRating(const MovieStorage& array, const double rating) {
    MovieStorage result = createMovieStorage();

    for (size_t i = 0; i < array.size; ++i) {
        if (array.data[i]->rating >= rating) {
            addMovieToStorage(result, array.data[i]);
        }
    }

    return result;
}

void freeMovie(Movie* movie) {
    if (nullptr == movie) {
        return;
    }

    delete[] movie->actors;
    delete movie;
}

// MovieStorage structure related functions:

MovieStorage createMovieStorage(size_t initialCapacity) {
    MovieStorage array;

    array.data = new Movie*[initialCapacity];
    array.size = 0;
    array.capacity = initialCapacity;

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
    if (nullptr == element) {
        return;
    }

    if (array.size == array.capacity) {
        resizeMovieStorage(array);
    }

    array.data[array.size++] = element;
}

void removeMovieFromStorage(MovieStorage& array, Movie* element) {
    if (nullptr == element) {
        return;
    }

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

MovieStorage copyMovieStorage(const MovieStorage& array) {
    MovieStorage result = createMovieStorage(array.capacity);

    for (size_t i = 0; i < array.size; ++i) {
        addMovieToStorage(result, array.data[i]);
    }

    return result;
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

// File operations related functions:

int saveMoviesToTextFile(const MovieStorage& array, const char* filename) {
    ofstream file(filename, ios::out);

    if (!file.is_open()) {
        cout << "Error saving movies to file." << endl;
        return -1;
    }

    file << array.size << endl;
    file << MOVIES_ID_COUNTER << endl;

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
    if (!ifstream(filename)) { // Check if the file exists
        return 0;
    }

    ifstream file(filename, ios::in);

    if (!file.is_open()) { // Check if the file is opened successfully
        cout << "Error loading movies from file." << endl;
        return -1;
    }

    if (file.peek() == ifstream::traits_type::eof()) { // Check if the file is empty
        file.close();
        return 0;
    }

    size_t size;
    file >> size;
    file >> MOVIES_ID_COUNTER;
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

// Utility functions:

bool isPositive(const int number) {
    return number > 0;
}

size_t readPositiveNumber(const char* message, const size_t max) {
    int number;
    
    while (true) {
        cout << message;
        cin >> number;
        cin.ignore(); // Clear the newline left in the buffer

        if (isPositive(number) && (size_t) number <= max) {
            return number;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
}

size_t myStrlen(const char* str) {
    if (nullptr == str) {
        return 0;
    }

    size_t length = 0;

    while (str[length]) {
        ++length;
    }

    return length;
}

bool doesStringContainsDelimiter(const char* string) {
    if (nullptr == string) {
        return false;
    }

    while (*string) {
        if (*string == COL_SEPARATOR || *string == SUB_SEPARATOR) {
            return true;
        }

        ++string;
    }

    return false;
}

void readString(char* buffer, const size_t maxLength, const char* message) {
    while (true) {
        cout << message;
        cin.getline(buffer, maxLength);

        if (doesStringContainsDelimiter(buffer)) {
            cout << "Invalid input. Please try again." << endl;
        } else if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            cout << "Entered string was cut off to fit the buffer maximum length." << endl;
            break;
        } else {
            break;
        }
    }
}

char toLowerCase(const char c) {
    return c >= 'A' && c <= 'Z' ? c + ('a' - 'A') : c;
}

bool areCharsEqualIgnoreCase(const char first, const char second) {
    return toLowerCase(first) == toLowerCase(second);
}

int strcmpIgnoreCase(const char* first, const char* second) {
    if (nullptr == first && nullptr == second) {
        return 0; // Both strings are null, so they are considered equal
    }

    if (nullptr == first) {
        return -1; // Null is considered less than any non-null string
    }

    if (nullptr == second) {
        return 1; // Any non-null string is considered greater than null
    }
    
    while (*first && *second) {
        if (!areCharsEqualIgnoreCase(*first, *second)) {
            return toLowerCase(*first) - toLowerCase(*second);
        }

        ++first;
        ++second;
    }

    return toLowerCase(*first) - toLowerCase(*second);
}

bool doesStringContainIgnoreCase(const char* string, const char* substring) {
    if (nullptr == string || nullptr == substring) {
        return false;
    }

    while (*string) {
        const char* stringStart = string;
        const char* substringStart = substring;

        while (*string && *substring && areCharsEqualIgnoreCase(*string, *substring)) {
            ++string;
            ++substring;
        }

        if (!*substring) {
            return true;
        }

        string = stringStart + 1;
        substring = substringStart;
    }

    return false;
}

bool askYesNo(const char* question) {
    char choice;

    cout << question << " (y/n): ";
    cin >> choice;
    cin.ignore(); // Clear the newline left in the buffer
    
    return areCharsEqualIgnoreCase(choice, 'y');
}

size_t countDigits(size_t number) {
    return number == 0 ? 1 : (size_t) log10(number) + 1;
}

void padText(const char* text, const size_t width) {
    cout << text;

    size_t length = myStrlen(text);
    
    for (size_t i = length; i < width; ++i) {
        cout << ' ';
    }
}

void padPositiveInt(const int number, const size_t width) {
    cout << number;

    size_t digits = countDigits(number);

    for (size_t i = digits; i < width; ++i) {
        cout << ' ';
    }
}

void padDouble(const double number, const size_t width, const size_t precision) {
    cout << fixed << setprecision(precision) << number;

    size_t digits = countDigits((size_t) number);

    for (size_t i = digits + precision + 1; i < width; ++i) {
        cout << ' ';
    }
}

// Clear the console based on the operating system.
// _WIN32 is defined for Windows, __linux__ is defined for Linux, and __APPLE__ is defined for macOS.
// These are predefined macros that are used to determine the operating system.
// We need to determine the operating system in order to clear the console correctly. Because the console clearing commands are different for each operating system.
// The system() function is used to execute a command in the console.
void clearConsole() {
    #ifdef _WIN32
        system("cls"); // Clear console for Windows
    #elif __linux__ || __APPLE__
        system("clear"); // Clear console for Linux and macOS
    #endif
}