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

// ADV 3 - First Part

// Insert content inside of the matrix.
void insertMatrix(std::vector<std::vector<char>>& matrix, std::ifstream& inputFile, std::string& line, int LINE_COUNT, int SIZE_LINE) {
    for (size_t i = 0; i <= LINE_COUNT; i++) {
        std::getline(inputFile, line);         
        for (size_t j = 0; j < SIZE_LINE; j++) {
            matrix[i][j] = line[j];
        }
    }
}

// Check if the consequent positions are numbers (recursive).
void checkNextDigits(std::vector<std::vector<char>>& matrix, size_t& i, size_t& j, std::string& number, int* end) {
    j++;
    if (isdigit(matrix[i][j])) {
        number += matrix[i][j];
        checkNextDigits(matrix, i, j, number, end);
    }  else if (end) {
        *end = j - 1;
    }
}

// Check the borders of the number, find if are any symbol across the border.
void checkBorders(std::vector<std::vector<char>>& matrix, std::vector<int>& iterator, size_t& i, std::string& number, int LINE_COUNT, int SIZE_LINE) {
    bool left = false, right = false, top = false, bottom = false;

    if (iterator[0] != 0) {                                                         // Check left of the number.
        left = true;
        if (matrix[i][iterator[0]-1] != '.') return;
    } 
    if (iterator[1] + 1 < SIZE_LINE) {                                                  // Check right of the number.
        right = true;
        if (matrix[i][iterator[1]+1] != '.') return;
    }

    if (i != 0 && i != LINE_COUNT) {                                                    // Check top and bottom of the number. It is the average case, of only O(n).
        top = bottom = true;
        for (size_t k = iterator[0]; k <= iterator[1]; k++) {
            if (matrix[i-1][k] != '.' || matrix[i+1][k] != '.') return;
        }
    } else {
        if (i != 0) {                                                                   // Check top of the number.
            top = true;
            for (size_t k = iterator[0]; k <= iterator[1]; k++) {
                if (matrix[i-1][k] != '.') return;
            }
        }
        if (i != LINE_COUNT) {                                                          // Check bottom of the number.
            bottom = true;
            for (size_t k = iterator[0]; k <= iterator[1]; k++) {
                if (matrix[i+1][k] != '.') return;
            }
        }
    }
    
    if (left && top) if (matrix[i-1][iterator[0]-1] != '.') return;                     // Check top-left corner.
    if (left && bottom) if (matrix[i+1][iterator[0]-1] != '.') return;                  // Check bottom-left corner.
    if (right && top) if (matrix[i-1][iterator[1]+1] != '.') return;                    // Check top-right corner.
    if (right && bottom) if (matrix[i+1][iterator[1]+1] != '.') return;                 // Check bottom-right corner.
    number = "0";                                                                       // Number is not adjacent to any symbol.
}

// ADV 3 - Last Part

// Check the borders of the number, find if are any asterik across the border.
void checkGears(std::vector<std::vector<char>>& matrix, std::vector<int>& iterator, size_t& i, std::string& number, std::string& adjNumber, int LINE_COUNT, int SIZE_LINE) {
    bool left = false, right = false, top = false, bottom = false;

    if (iterator[0] != 0) left = true;                                                   // Check left of the number.
    if (iterator[1] + 1 < SIZE_LINE) {                                                   // Check right of the number.
        right = true;
        if (matrix[i][iterator[1]+1] == '*') return checkAdjNum(matrix, i, iterator[1]+1, adjNumber, LINE_COUNT, SIZE_LINE);

    }
    if (i != 0) top = true;                                                             // Check top of the number.
    if (i != LINE_COUNT) {                                                              // Check bottom of the number.
        bottom = true;
        for (size_t k = iterator[0]; k <= iterator[1]; k++) {
            if (matrix[i+1][k] == '*') return checkAdjNum(matrix, i+1, k, adjNumber, LINE_COUNT, SIZE_LINE);
        }
    }
    
    if (left && bottom) if (matrix[i+1][iterator[0]-1] == '*') return checkAdjNum(matrix, i+1, iterator[0]-1, adjNumber, LINE_COUNT, SIZE_LINE, false, true);
    if (right && bottom) if (matrix[i+1][iterator[1]+1] == '*') return checkAdjNum(matrix, i+1, iterator[1]+1, adjNumber, LINE_COUNT, SIZE_LINE);
    if (right && top) if (matrix[i-1][iterator[1]+1] == '*') return checkAdjNum(matrix, i-1, iterator[1]+1, adjNumber, LINE_COUNT, SIZE_LINE, true, false);

    number = adjNumber = "0";
}

void checkAdjNum(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber, int LINE_COUNT, int SIZE_LINE, bool topright, bool bottomleft) {
    bool left = false, right = false, top = false, bottom = false;

    if (j != 0) left = true;                                           // Check left
    if (j != SIZE_LINE) {                                              // Check right
        right = true;
        if (isdigit(matrix[i][j+1])) return checkLeft(matrix, i, j+1, adjNumber);
    }
    if (i != 0) top = true;                                             // Check top
    if (i != LINE_COUNT) {                                              // Check bottom
        bottom = true;
        if (isdigit(matrix[i+1][j])) return checkLeft(matrix, i+1, j, adjNumber);
    }
    
    if ((left && bottom) && !topright) if (isdigit(matrix[i+1][j-1])) return checkLeft(matrix, i+1, j-1, adjNumber);
    if (right && bottom) if (isdigit(matrix[i+1][j+1])) return checkLeft(matrix, i+1, j+1, adjNumber);
    if ((right && top)  && !topright && !bottomleft) if (isdigit(matrix[i-1][j+1])) return checkLeft(matrix, i-1, j+1, adjNumber);

    adjNumber = "0";
}

void checkLeft(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber) {
    if (j != 0) {
        if (isdigit(matrix[i][j-1])) return checkLeft(matrix, i, j-1, adjNumber);
    }
    adjNumber += matrix[i][j];
    return checkNextDigits(matrix, i, j, adjNumber);
}