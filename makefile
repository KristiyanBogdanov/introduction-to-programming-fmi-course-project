# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = CourseProject

# Source files
SRCS = main.cpp user.cpp movie_core.cpp movie_array.cpp movie_file.cpp utils.cpp

# Default rule: build the executable
all: $(TARGET)

# Build the executable from source files
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Clean up build artifacts
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run