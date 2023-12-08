#include "functions.hpp"
#include "auxFunctions.hpp"

// ADV 1 - FIRST PART

int adv1First(std::string textFile) {
    std::ifstream inputFile(textFile);
    int result = 0;
    std::string line, resultString;
 
    while (std::getline(inputFile, line)) {
        resultString = "";
        for (size_t i = 0; i < line.length(); i++) {
            if (isdigit(line[i])) {
                resultString += line[i];  
                break;
            }
        }

        for (int i = line.length() - 1; i >= 0; i--) {
            if (isdigit(line[i])) {
                resultString += line[i];
                break;
            }
        }
        
        result += stoi(resultString);
    }

    return result;
}

// ADV 1 - LAST PART

int adv1Last(std::string textFile) {
    std::ifstream inputFile(textFile);
    int result = 0;
    std::string line, resultString, blankline;
    std::map<std::string, int> nums;
    emplaceMap(nums, result);
    bool valFound;
 
    while (std::getline(inputFile, line)) {
        resultString = "";
        
        for (size_t i = 0; i < line.length(); i++) {
            if (valFound) {
                valFound = false;
                break;
            }
            else if (isdigit(line[i])) {
                resultString += line[i];
                break;
            } else {
                blankline.insert(blankline.end(), line[i]);
                checkKey(nums, resultString, valFound, blankline);
            }
        }

        for (int i = line.length() - 1; i >= 0; i--) {
            if (valFound) {
                valFound = false;
                break;
            }
            else if (isdigit(line[i])) {
                resultString += line[i];
                break;
            } else {
                blankline.insert(blankline.begin(), line[i]);
                checkKey(nums, resultString, valFound, blankline);
            } 
        }
        
        result += stoi(resultString);
    }

    return result;
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

        if (!isFull) {
            result += index;
            isFull = false;
        }
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
    std::ifstream inputFile(textFile);
    std::string line;
    const size_t LINE_COUNT = std::count_if(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), [](char c) { return c == '\n'; }); 
    std::cout << LINE_COUNT << "\n";

    while (std::getline(inputFile, line)) {

    }
}