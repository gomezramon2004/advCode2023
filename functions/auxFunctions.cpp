#include "functions.hpp"
#include "auxFunctions.hpp"

// ADV 1 - LAST PART

// Emplace content inside of the hashtable. Create a pointer array of words, then iterate the list.
void emplaceMap(std::map<std::string, int>& hashTable, int& counter) {
    std::string* arr = new std::string[9] {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (auto i = arr; i < arr + 9; ++i) {
        counter++;
        hashTable.emplace(*i, counter);
    }

    delete[] arr;
    counter = 0;
}

// Iterate the keys and check if it correspond to the blankline
void checkKey(std::map<std::string, int>& hashTable, std::string& result, bool& valFound, std::string& blankline) {
    for (auto const& [key, val] : hashTable) {
        if (blankline.find(key) != std::string::npos) {
            result += std::to_string(val);
            valFound = true;
            blankline = "";
            break;
        }
    }
}

// Check if the consequent positions are numbers (recursive).
void checkNums(std::vector<std::vector<char>>& matrix, std::vector<int>& it, size_t& i, size_t& j, std::string& number) {
    j++;                                            // Next position.
    if (isdigit(matrix[i][j])) {                    // If the next position is a digit, then add it to the container. Progresses recursively.
        number += matrix[i][j];
        checkNums(matrix, it, i, j, number);
    } else {                                        // If not, then Position "j-1" is the last index.
        it[1] = j-1;
    }
}

// Check the borders of the number, find if are any symbol across the border.
void checkBorders(std::vector<std::vector<char>>& matrix, std::vector<int>& it, size_t& i, std::string& number, int LINE_COUNT, int SIZE_LINE) {
    bool left = false, right = false;

    if (it[0] - 1 >= 0) {                                                   // Check left of the number.
        left = true;
        if (matrix[i][it[0]-1] != '.') return;
    } 
    if (it[1] + 1 < SIZE_LINE) {                                            // Check right of the number.
        right = true;
        if (matrix[i][it[1]+1] != '.') return;
    }

    if (!left) {                                                            // Check if the number is in the top-left, bottom-left and left-side of the matrix.
        if (i == 0) {
            for (size_t k = it[0]; k <= it[1] + 1; k++) {
                if (matrix[i+1][k] != '.') return;
            }
        } else if (i == LINE_COUNT) {
            for (size_t k = it[0]; k <= it[1] + 1; k++) {
                if (matrix[i-1][k] != '.') return;
            }
        } else {
            for (size_t k = it[0]; k <= it[1] + 1; k++) {
                if (matrix[i-1][k] != '.' || matrix[i+1][k] != '.') return;
            }
        }
    } else if (!right) {                                                    // Check if the number is in the top-right, bottom-right and right-side of the matrix.
        if (i == 0) {
            for (size_t k = it[0] - 1; k <= it[1]; k++) {
                if (matrix[i+1][k] != '.') return;
            }
        } else if (i == LINE_COUNT) {
            for (size_t k = it[0] - 1; k <= it[1]; k++) {
                if (matrix[i-1][k] != '.') return;
            }
        } else {
            for (size_t k = it[0] - 1; k <= it[1]; k++) {
                if (matrix[i-1][k] != '.' || matrix[i+1][k] != '.') return;
            }
        }
    } else {
        if (i == 0) {                                                           // Check top-side of the matrix.
            for (size_t k = it[0] - 1; k <= it[1] + 1; k++) {
                if (matrix[i+1][k] != '.') return;
            }
        } else if (i == LINE_COUNT) {
            for (size_t k = it[0] - 1; k <= it[1] + 1; k++) {                   // Check bottom-side of the matrix.
                if (matrix[i-1][k] != '.') return;
            }
        } else {                                                                // Check the other cases
            for (size_t k = it[0] - 1; k <= it[1] + 1; k++) {
                if (matrix[i-1][k] != '.' || matrix[i+1][k] != '.') return;
            }
        }
    }

    number = "0";
}