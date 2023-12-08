#include "functions.hpp"
#include "auxFunctions.hpp"

// ADV 1 - FIRST PART

int adv1First(std::string textFile) {
    std::ifstream inputFile(textFile);                      // Input stream from the textfile.
    int totalResult = 0;                                    // Total result.
    std::string line, lineResult;                           // n-Line from the textfile.  Result from each line.
 
    while (std::getline(inputFile, line)) {                 // For each line in the textfile.
        lineResult = "";
        for (size_t i = 0; i < line.length(); i++) {            // Iterate all of the chars from one line, break if it found a digit.
            if (isdigit(line[i])) {
                lineResult += line[i];  
                break;
            }
        }

        for (int i = line.length() - 1; i >= 0; i--) {          // Iterate all of the chars from one line in reverse, break if it found a digit.
            if (isdigit(line[i])) {
                lineResult += line[i];
                break;
            }
        }
        
        totalResult += stoi(lineResult);                        // Convert the line result in integer, then add it to the total result.
    }

    return totalResult;
}

// ADV 1 - LAST PART

int adv1Last(std::string textFile) {
    std::ifstream inputFile(textFile);                              // Input stream from the textfile.
    int totalResult = 0;                                            // Total result.
    std::string line, lineResult, blankline;                        // n-Line from the textfile.  Result from each line. Blankline to fill up a number word.
    std::map<std::string, int> nums;                                // Hashtable: [Keys: Number Word / Values: Its Numberized Value].
    emplaceMap(nums, totalResult);                                  // Emplace content inside of the hashtable. Create a pointer array of words, then iterate the list.
    bool valFound;                                                  // Boolean value for if the program found a number word.
 
    while (std::getline(inputFile, line)) {                         // For each line in the textfile.
        lineResult= "";
        
        for (size_t i = 0; i < line.length(); i++) {                    // Iterate all of the chars from one line, break if it found a digit or a number word.
            if (valFound) {
                valFound = false;
                break;
            }
            else if (isdigit(line[i])) {
                lineResult += line[i];
                break;
            } else {
                blankline.insert(blankline.end(), line[i]);                     
                checkKey(nums, lineResult, valFound, blankline);                // Iterate the keys and check if it correspond to the blankline.
            }
        }

        for (int i = line.length() - 1; i >= 0; i--) {                  // Iterate all of the chars from one line in reverse, break if it found a digit or a number word.
            if (valFound) {
                valFound = false;
                break;
            }
            else if (isdigit(line[i])) {
                lineResult += line[i];
                break;
            } else {
                blankline.insert(blankline.begin(), line[i]);
                checkKey(nums, lineResult, valFound, blankline);                // Iterate the keys and check if it correspond to the blankline.
            } 
        }
        
        totalResult += stoi(lineResult);                                // Convert the line result in integer, then add it to the total result.
    }

    return totalResult;
}

// ADV 2 - FIRST PART

int adv2First(std::string textFile) {
    std::ifstream inputFile(textFile);
    int result = 0, redCubes = 12, greenCubes = 13, blueCubes = 14, index = 1;
    std::string line, subsets, subset;
    bool isFull;
 
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line.substr(line.find(":") + 1));

        while (std::getline(iss, subsets, ';')) {
            std::istringstream iss(subsets);
            
            while (std::getline(iss, subset, ',')) {
                if (isdigit(subset[2])) {
                    if (subset[4] == 'r') {
                        if (stoi(subset.substr(1,2)) > redCubes) isFull = true;
                    } else if (subset[4] == 'g') {
                        if (stoi(subset.substr(1,2)) > greenCubes) isFull = true;
                    } else {
                        if (stoi(subset.substr(1,2)) > blueCubes) isFull = true;
                    }
               }
            }

        }

        if (!isFull) result += index;
        isFull = false;
        ++index;
    }

    return result;
}

// ADV 2 - LAST PART

int adv2Last(std::string textFile) {
    std::ifstream inputFile(textFile);
    int result = 0, fewerRed = 0, fewerGreen = 0, fewerBlue = 0;
    std::string line, subsets, subset;
 
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line.substr(line.find(":") + 1));

        while (std::getline(iss, subsets, ';')) {
            std::istringstream iss(subsets);

            while (std::getline(iss, subset, ',')) {
                if (subset.find("red") != std::string::npos) {
                    if (stoi(subset.substr(1,2)) > fewerRed) fewerRed = stoi(subset.substr(1,2));
                } else if (subset.find("green") != std::string::npos) {
                    if (stoi(subset.substr(1,2)) > fewerGreen) fewerGreen = stoi(subset.substr(1,2));
                } else {
                    if (stoi(subset.substr(1,2)) > fewerBlue) fewerBlue = stoi(subset.substr(1,2));
                }
            }

        }

        result += (fewerRed * fewerGreen * fewerBlue);
        fewerRed = fewerGreen = fewerBlue = 0;
    }

    return result;
}

// ADV 3 - FIRST PART

int adv3First(std::string textFile) {
    std::ifstream inputFile(textFile);              // Input Stream from the textfile
    std::string line;
    std::getline(inputFile, line);                  // Get the first line and check its size
    const size_t SIZE_LINE = line.size();
    const size_t LINE_COUNT = std::count_if(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), [](char c) { return c == '\n'; }) + 1; // Count all of the lines from the textfile
    inputFile.seekg(0);                             // Reset file pointer to the beginning
    
}