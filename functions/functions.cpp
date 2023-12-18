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
    std::ifstream inputFile(textFile);                                                      // Input Stream from the textfile. 
    int totalResult = 0;                                                                    // Total result. 
    std::string line, number;                                                               // n-Line from the textfile. Number container.
    std::vector<int> it(2);                                                                 // Iterator of a number. Contains the beginning and end.

    std::getline(inputFile, line);                                                                                                  // Get the first line to check its size.
    const size_t SIZE_LINE = line.size();                                                                                           // Size line.
    const size_t LINE_COUNT = std::count(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), '\n') + 1;    // Total amount of lines in the textfile.
    inputFile.seekg(0);                                                                                                             // Reset file pointer to the beginning.
    std::vector<std::vector<char>> mtrx(SIZE_LINE, std::vector<char>(LINE_COUNT));                                                  // Initialize size of the vector.
    
    insertMatrix(mtrx, inputFile, line, LINE_COUNT, SIZE_LINE);

    for (size_t i = 0; i <= LINE_COUNT; i++) {                                              // Travel to the matrix.
        for (size_t j = 0; j < SIZE_LINE; j++) {
            if (isdigit(mtrx[i][j])) {                                                              // Check if certain position is a number.
                number += mtrx[i][j];
                it[0] = j;                                                                              // Position "j" is the beginning of the iterator.
                int* ptrToIt1 = &it[1];                                                                 // Pointer to the end of the iterator. C-Like way to pass as a reference a value.
                checkNextDigits(mtrx, i, j, number, ptrToIt1);                                          // Check if the consequent positions are numbers (recursive).
                checkBorders(mtrx, it, i, number, LINE_COUNT, SIZE_LINE);                               // Check the borders of the number, find if are any symbol across the border.
                totalResult += stoi(number);                                                            // Add the number to the total result.
                number = "";
            }
        }
    }

    return totalResult;
}

// ADV 3 - LAST PART

int adv3Last(std::string textFile) {
    std::ifstream inputFile(textFile);                                                      // Input Stream from the textfile. 
    int totalResult = 0;                                                                    // Total result. 
    std::string line, number, adjNumber;                                                    // n-Line from the textfile. Number and its adjacent.
    std::vector<int> it(2);                                                                 // Iterator of a number. Contains the beginning and end.
    int* ptrToIt1 = &it[1];                                                                 // Pointer to the end of the iterator. // C-Like way to pass as a reference a value. 

    std::getline(inputFile, line);                                                                                                  // Get the first line to check its size.
    const size_t SIZE_LINE = line.size();                                                                                           // Size line.
    const size_t LINE_COUNT = std::count(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), '\n') + 1;    // Total amount of lines in the textfile.
    inputFile.seekg(0);                                                                                                             // Reset file pointer to the beginning.
    std::vector<std::vector<char>> mtrx(SIZE_LINE, std::vector<char>(LINE_COUNT));                                                  // Initialize size of the vector.
    
    insertMatrix(mtrx, inputFile, line, LINE_COUNT, SIZE_LINE);

    for (size_t i = 0; i <= LINE_COUNT; i++) {                                              // Travel to the matrix.
        for (size_t j = 0; j < SIZE_LINE; j++) {
            if (isdigit(mtrx[i][j])) {                                                              // Check if certain position is a number and the position was checked previously.
                number += mtrx[i][j];
                it[0] = j;                                                                              // Position "j" is the beginning of the iterator.
                checkNextDigits(mtrx, i, j, number, ptrToIt1);                                          // Check if the consequent positions are numbers (recursive).
                checkGears(mtrx, it, i, number, adjNumber, LINE_COUNT, SIZE_LINE);                      // Check the borders of the number, find if are any symbol across the border.
                if (number == adjNumber) adjNumber = "0";
                totalResult += stoi(number) * stoi(adjNumber);                                          // Add the product to the total result.
                number = adjNumber = "";
            }
        }
    }

    return totalResult;
}

// ADV 4 - FIRST PART

int adv4First(std::string textFile) {
    std::ifstream inputFile(textFile);                                                                                  // Input stream from the textfile.
    std::string line, nums;                                                                                             // n-Line from the textfile. List of numbers.
    int totalResult = 0, num, points, it = 0;                                                                           // Total result. Each number. Points. Iterator.

    const size_t LINE_COUNT = std::count(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), '\n') + 1;    // Total amount of lines in the textfile.
    inputFile.seekg(0);                                                                                                             // Reset file pointer to the beginning.
    std::vector<std::vector<int>> winnerList(LINE_COUNT, std::vector<int>()), numList(LINE_COUNT, std::vector<int>());              // Winners and total numbers vectors.

    while (std::getline(inputFile, line)) {                                                                             // For each line in the textfile.
        std::istringstream iss(line.substr(line.find(":") + 1));                                                            // Substract the "Game #n: " part.
        std::getline(iss, nums, '|');                                                                                       // Substract the first part of the row; winner list.
        std::istringstream winnerStream(nums);
        while (winnerStream >> num) winnerList[it].push_back(num);
        std::getline(iss, nums);                                                                                            // Substract the last part of the row; number list.
        std::istringstream numStream(nums);
        while (numStream >> num) numList[it].push_back(num);
        
        mergeSort(numList[it], 0, numList[it].size() - 1);                                                                  // Mergesort

        for (size_t i = 0; i < winnerList[it].size(); i++) if (binarySearch(numList[it], winnerList[it][i])) points++;      // If Binary Search found the value, sum by one the points count.

        if (points == 1) totalResult += 1;
        else if (points > 1) totalResult += pow(2, points-1);
        points = 0;
        it++;
    }

    return totalResult;
}

// ADV 4 - LAST PART

int adv4Last(std::string textFile) {
    std::ifstream inputFile(textFile);                                                                              // Input stream from the textfile.
    std::string line, nums;                                                                                         // n-Line from the textfile. List of numbers.
    int totalResult = 0, num, points, it = 0;                                                                       // Total result. Each number. Points. Iterator.

    const size_t LINE_COUNT = std::count(std::istreambuf_iterator<char>(inputFile), std::istreambuf_iterator<char>(), '\n') + 1;    // Total amount of lines in the textfile.
    inputFile.seekg(0);                                                                                                             // Reset file pointer to the beginning.
    std::vector<std::vector<int>> winnerList(LINE_COUNT, std::vector<int>());                                                       // Winners numbers vector.
    std::vector<std::vector<int>> numList(LINE_COUNT, std::vector<int>());                                                          // Total numbers vector.

    while (std::getline(inputFile, line)) {                                                                         // For each line in the textfile.
        std::istringstream iss(line.substr(line.find(":") + 1));                                                        // Substract the "Game #n: " part.
        std::getline(iss, nums, '|');                                                                                   // Substract the first part of the row; winner list.
        std::istringstream winnerStream(nums);
        while (winnerStream >> num) winnerList[it].push_back(num);
        std::getline(iss, nums);                                                                                        // Substract the last part of the row; number list.
        std::istringstream numStream(nums);
        while (numStream >> num) numList[it].push_back(num);
        
        mergeSort(numList[it], 0, numList[it].size() - 1);                                                              // Mergesort.
        it++;
    }
        
    for (size_t i = 0; i < winnerList.size(); i++) {                                                                // For each series of winner numbers.
        points = 0;
        for (size_t j = 0; j < winnerList[i].size(); j++) if (binarySearch(numList[i], winnerList[i][j])) points++;     // If Binary Search found the value, sum by one the points count.
        recursiveScratch(totalResult, winnerList, numList, i+1, points);
        totalResult++;
    }

    return totalResult;
}

// ADV 5 - FIRST PART

int adv5First(std::string textFile) {
    std::ifstream inputFile(textFile);                                              // Input stream from the textfile.
    int allChecked{};                                                               // Number flag to check if all of the seeds are checked (and prevent to iterate each time).
    long long num{};                                                                // Number that holds an entity from the textfile;
    std::array<long long, 3> map;                                                   // Array of each mapping list [Destination, Length and Start]
    std::string line;                                                               // String that holds each line from the textfile.
    std::vector<std::pair<long long, bool>> seeds;                                  // Each seeds and if it was checked during an iteration.

    std::getline(inputFile, line);                                                  // First line corresponds to the total of seeds.
    std::istringstream seedStream(line.substr(line.find(":") + 1));                 // Substract the "seeds: " part.
    while (seedStream >> num) seeds.emplace_back(num, false);                       // While the line has at most one number, emplace back to the vector.
    
    while (std::getline(inputFile, line)) {                                         // For each line in the textfile.
        if (!isdigit(line[0])) {                                                        // TO FIX
            if (line[0] == '\n') continue;
            for (auto&& [seed, checked]: seeds) checked = false;
            continue;
        }
        if (allChecked == seeds.size()) continue;                                       // TO FIX
        std::istringstream mapStream(line);                                             // Input streamline for mapping line.
        for (size_t i = 0; i < map.size(); ++i) {                                       // For each line of mapping, extract a number and put in the indexed slot.
            mapStream >> num;
            map[i] = num;
        }
        for (auto&& [seed, checked]: seeds) {                                           // For each structured binding of the seed, use the logic of mapping to convert data.
            if (checked) {                                                                  // TO FIX
                allChecked++; 
                continue; 
            }
            if (map[1] <= seed && map[1] + map[2] - 1 >= seed && !checked) {
                seed = map[0] + (seed - map[1]);
                checked = true;
            }
        }
    }

    const auto smallestPair = [](const auto& a, const auto& b) { return a.first < b.first; };           // Check the smallest of the pair.
    const auto smallest = std::min_element(seeds.begin(), seeds.end(), &smallestPair)->first;           // Check the smalles value.
    return smallest;
}       

// ADV 5 - LAST PART
/*
int adv5Last(std::string textFile) {
    
}
*/