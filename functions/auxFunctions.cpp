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

// Check the borders of the asterik, find if are any number.
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


// Check the left side of the matrix until it can't search more.
void checkLeft(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber) {
    if (j != 0) {
        if (isdigit(matrix[i][j-1])) return checkLeft(matrix, i, j-1, adjNumber);
    }
    adjNumber += matrix[i][j];
    return checkNextDigits(matrix, i, j, adjNumber);
}

// ADV 4 - First Part

// Merge Sort - Recursive Part
void mergeSort(std::vector<int>& vec, int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// Merge Sort - Merge Part
void merge(std::vector<int>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid, i = 0, j = 0, k = left;
    std::vector<int> leftVec(vec.begin() + left, vec.begin() + left + n1);
    std::vector<int> rightVec(vec.begin() + mid + 1, vec.begin() + mid + 1 + n2);

    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}

// Binary Search
bool binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return true;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return false;
}

// ADV 4 - Last Part

// Recurse the cards to find the correct value.
void recursiveScratch(int& total, std::vector<std::vector<int>>& winVec, std::vector<std::vector<int>>& numVec, const int oldIt, const int oldPoints) {
    int points, limit = oldPoints + oldIt;
    if (oldPoints + oldIt > winVec.size()) limit = winVec.size();

    for (int i = oldIt; i < limit; i++) {
        points = 0;
        for (size_t j = 0; j < winVec[i].size(); j++) if (binarySearch(numVec[i], winVec[i][j])) points++;    // If Binary Search found the value, check by recursivity
        recursiveScratch(total, winVec, numVec, i+1, points);
        total++;
    }         
}

// ADV 5 - Last Part

// Skip the unnecessary lines
void skipLines(std::istream& stream, int numLinesToSkip) {
    for (int i = 0; i < numLinesToSkip; ++i) {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Recurse the ranges until it can't more. 
void recursiveMerge(const std::vector<std::pair<rangeNum, bool>>& seeds, const rangeNum& currentSeed, rangeNum& nextSeed, size_t& i) {
    ++i;
    if (i + 1 >= seeds.size()) return;
    if (seeds[i].first.lastNum >= seeds[i+1].first.firstNum || seeds[i-1].first.lastNum >= seeds[i+1].first.firstNum) {
        nextSeed = seeds[i+1].first;
        recursiveMerge(seeds, currentSeed, nextSeed, i);
    }
}

// Merge the range of seeds if they overlap
void mergeSeeds(std::vector<std::pair<rangeNum, bool>>& rangeSeeds, std::vector<std::pair<rangeNum, bool>>& mergedRangeSeeds, rangeNum& currentSeed, rangeNum& nextSeed) {
    std::sort(rangeSeeds.begin(), rangeSeeds.end());
    
    for (size_t i = 0; i < rangeSeeds.size(); ++i) {
        currentSeed = rangeSeeds[i].first;
        nextSeed = (i + 1 == rangeSeeds.size()) ? rangeSeeds[i].first : rangeSeeds[i + 1].first;

        if (currentSeed.lastNum >= nextSeed.firstNum && i + 1 != rangeSeeds.size()) {
            recursiveMerge(rangeSeeds, currentSeed, nextSeed, i);
            mergedRangeSeeds.emplace_back(rangeNum{ currentSeed.firstNum, std::max(nextSeed.lastNum, currentSeed.lastNum) }, false);
        } else {
            mergedRangeSeeds.emplace_back(currentSeed, false);
        }
    }

    rangeSeeds = std::move(mergedRangeSeeds);
    mergedRangeSeeds.clear();
}

// ADV 6 - First Part

// Add time and distance
void addTimeAndDistance(std::ifstream& input, std::istringstream& stream, std::string& line, int& num, std::vector<int>& vec) {
    std::getline(input, line);
    stream.str (line.substr(line.find(":") + 1));

    while (stream >> num) vec.emplace_back(num);

    stream.clear();
}

// Change the boundaries of the quadratic formula result.
template <typename T>
T fixBoundary(const T& time, const T& distance, T&& quadraticEq, const int&& edge) {
    auto boundary = [&](T t) { return t * (time - t) > distance; };
    while (!boundary(quadraticEq))
        quadraticEq -= edge;
    while (boundary(quadraticEq + edge))
        quadraticEq += edge;
    return quadraticEq;
}

template int fixBoundary<int>(const int& time, const int& distance, int&& quadraticEq, const int&& edge);
template long long fixBoundary<long long>(const long long& time, const long long& distance, long long&& quadraticEq, const int&& edge);

// Calculate the add and distance values concatenating the numbers
void anotherAddTimeAndDistance(std::ifstream& input, std::istringstream& stream, std::string& line, std::string& numString, std::string& totalNum, long long& total) {
    std::getline(input, line);
    stream.str (line.substr(line.find(":") + 1));

    while (stream >> numString) totalNum += numString ;

    total = stoll(totalNum);
    totalNum = "";
    stream.clear();
}