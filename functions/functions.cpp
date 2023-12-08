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
    std::ifstream inputFile(textFile);                                                      // Input stream from the textfile.
    int totalResult = 0, redCubes = 12, greenCubes = 13, blueCubes = 14, index = 1;         // Total result. Maximum amount of red, green and blue cubes. Index.
    std::string line, subsets, subset;                                                      // n-Line from the textfile. Each group of subsets. Each subset.
    bool isImpossible;                                                                      // Boolean value for if a specific amount of cubes can't be possible to play a game.
 
    while (std::getline(inputFile, line)) {                                                 // For each line in the textfile.
        std::istringstream iss(line.substr(line.find(":") + 1));                                // Substract the "Game #n: " part.

        while (std::getline(iss, subsets, ';')) {                                               // For each group of subsets.
            std::istringstream iss(subsets);
            
            while (std::getline(iss, subset, ',')) {                                                // For each subset.
                if (isdigit(subset[2])) {                                                           // If the third char is a number. It means that it is a two-digit number.
                    if (subset[4] == 'r') {                                                             // If the five char is "r", i.e red, and its value is greater, then it's impossible.
                        if (stoi(subset.substr(1,2)) > redCubes) isImpossible = true;
                    } else if (subset[4] == 'g') {                                                      // If the five char is "g", i.e green, and its value is greater, then it's impossible.
                        if (stoi(subset.substr(1,2)) > greenCubes) isImpossible = true;
                    } else {                                                                            // If the five char is "b", i.e blue, and its value is greater, then it's impossible.
                        if (stoi(subset.substr(1,2)) > blueCubes) isImpossible = true;
                    }
               }
            }

        }

        if (!isImpossible) totalResult += index;                                                // Add the index to the total result if it found that a game is possible to play it.
        isImpossible = false;                                                                   // Reset the boolean value for each iteration.
        ++index;
    }

    return totalResult;
}

// ADV 2 - LAST PART

int adv2Last(std::string textFile) {
    std::ifstream inputFile(textFile);                                                      // Input stream from the textfile.
    int totalResult = 0, fewerRed = 0, fewerGreen = 0, fewerBlue = 0;                       // Total result. Maximum amount of red, green and blue cubes.
    std::string line, subsets, subset;                                                      // n-Line from the textfile. Each group of subsets. Each subset.
 
    while (std::getline(inputFile, line)) {                                                 // For each line in the textfile.
        std::istringstream iss(line.substr(line.find(":") + 1));                                // Substract the "Game #n: " part.

        while (std::getline(iss, subsets, ';')) {                                               // For each group of subsets.
            std::istringstream iss(subsets);

            while (std::getline(iss, subset, ',')) {                                                // For each subset.
                if (subset.find("red") != std::string::npos) {                                          // If the subset is red, and its value is greater, then replace the current value.
                    if (stoi(subset.substr(1,2)) > fewerRed) fewerRed = stoi(subset.substr(1,2));
                } else if (subset.find("green") != std::string::npos) {                                 // If the subset is green, and its value is greater, then replace the current value.
                    if (stoi(subset.substr(1,2)) > fewerGreen) fewerGreen = stoi(subset.substr(1,2));
                } else {                                                                                // If the subset is blue, and its value is greater, then replace the current value.
                    if (stoi(subset.substr(1,2)) > fewerBlue) fewerBlue = stoi(subset.substr(1,2));
                }
            }

        }

        totalResult += (fewerRed * fewerGreen * fewerBlue);                                  // Add the product of the three values to the total result.
        fewerRed = fewerGreen = fewerBlue = 0;
    }

    return totalResult;
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