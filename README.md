# Movie Management System

## Overview
This project is a simplified version of the Internet Movie Database (IMDb). It allows users to manage and explore a database of movies. Users are divided into two roles: **Admin** and **Regular User**. Each role provides a set of functionalities tailored to their needs.

### Key Features:
1. Add, edit, and delete movies (Admin only).
2. Search movies by title or genre.
3. Sort movies by title or rating.
4. View all movies and their details.
5. Add ratings to movies.
6. Filter movies by minimum rating.

## Roles and Functionalities

### Admin:
- **Add New Movie**: Add movie details.
- **Edit Movie Details**: Modify existing movie data.
- **Delete Movie**: Remove a movie from the database.
- **Sort Movies**: Sort movies by title (ascending) or rating (descending).
- **Search Movies**: Find movies by title or genre.
- **View All Movies**: List all movies with detailed information.
- **Filter Movies by Rating**: Filter movies above a specified rating threshold.

### Regular User:
- **Search Movies**: Search for movies by title or genre.
- **View All Movies**: Browse all movies.
- **Sort Movies**: Sort movies by title (ascending) or rating (descending).
- **Add Review**: Submit a rating (1-10) for a movie. The average rating is automatically recalculated.
- **Filter Movies by Rating**: Filter movies above a specified rating threshold.

## Technical Details
- **Language**: C++
- **Compiler**: GCC
- **Data Persistence**: Movie and review data are stored and retrieved from text files (`movies.txt` and `reviews.txt`).
- **Platform Compatibility**: The console clearing command adapts to Windows, Linux, and macOS systems.

## How to Run
1. Compile the program using GCC:
   ```bash
   g++ -o movie_manager main.cpp
   ```
2. Run the executable:
   ```bash
   ./movie_manager
   ```

## Author
- **Kristiyan Bogdanov**
- **ID**: 4MI0600438
- **Faculty**: Faculty of Mathematics and Informatics, Sofia University