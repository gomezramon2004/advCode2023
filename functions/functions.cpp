#include "functions.hpp"
#include "auxFunctions.hpp"
#include <iostream>
#include <fstream>

// ADV 1 - FIRST PART

int adv1First(const std::string& textFile) {
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

int adv1Last(const std::string& textFile) {
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

int adv2First(const std::string& textFile) {
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

int adv2Last(const std::string& textFile) {
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

int adv3First(const std::string& textFile) {
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

int adv3Last(const std::string& textFile) {
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

int adv4First(const std::string& textFile) {
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

int adv4Last(const std::string& textFile) {
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

int adv5First(const std::string& textFile) {
    std::ifstream inputFile(textFile);                                              // Input stream from the textfile.
    int allChecked{};                                                               // Number flag to check if all of the seeds are checked (and prevent to iterate each time).
    long long num{};                                                                // Number that holds an entity from the textfile.
    std::array<long long, 3> map;                                                   // Array of each mapping list [Destination, Length and Start].
    std::string line;                                                               // String that holds each line from the textfile.
    std::vector<std::pair<long long, bool>> seeds;                                  // Each seeds and if it was checked during an iteration.

    std::getline(inputFile, line);                                                  // First line corresponds to the total of seeds.
    std::istringstream seedStream(line.substr(line.find(":") + 1));                 // Substract the "seeds: " part.
    while (seedStream >> num) seeds.emplace_back(num, false);                       // While the line has at most one number, emplace back to the vector.
    
    while (std::getline(inputFile, line)) {                                         // For each line in the textfile.
        if (!isdigit(line[0])) {                                                        // Check if the line is empty or is a string to skip the iteration.
            if (line.empty()) continue;
            for (auto&& [seed, checked]: seeds) checked = false;
            allChecked = 0;
            continue;
        }
        if (allChecked == seeds.size()) continue;                                       // If all of the seeds are checked, then skip the iteration.
        std::istringstream mapStream(line);                                             // Input streamline for mapping line.

        for (size_t i = 0; i < map.size(); ++i) {                                       // For each line of mapping, extract a number and put in the indexed slot.
            mapStream >> num;
            map[i] = num;
        }

        for (auto&& [seed, checked]: seeds) {                                           // For each structured binding of the seed, use the logic of mapping to convert data.
            if (checked) continue;                                                          // If checked, skip the iteration.
            if (map[1] <= seed && map[1] + map[2] > seed && !checked) {
                seed = map[0] + (seed - map[1]);
                checked = true;
                allChecked++;
            }
        }
        
    }

    const auto smallestPair = [](const auto& a, const auto& b) { return a.first < b.first; };           // Check the smallest of the pair.
    const auto smallest = std::min_element(seeds.begin(), seeds.end(), smallestPair)->first;           // Check the smallest value.
    return smallest;
}       

// ADV 5 - LAST PART

long long adv5Last(const std::string& textFile) {
    std::ifstream inputFile(textFile);                                                      // Input stream from the textfile.
    long long startNum{}, endNum{}, offsetStart, offsetEnd;                                 // Start and end of the seed range. Also the values of its offset range.
    std::array<long long, 3> map;                                                           // Array of each mapping list [Destination, Length and Start]
    std::string line;                                                                       // String that holds each line from the textfile.
    std::vector<std::pair<rangeNum, bool>> rangeSeeds, newRangeSeeds, mergedRangeSeeds;     // Each range of seeds, a temporal range and a merged range seeds.
    rangeNum currentSeed, nextSeed;                                                         // Current and next Seed in a range of seeds

    std::getline(inputFile, line);                                                          // First line corresponds to the total of seeds.
    std::istringstream seedStream(line.substr(line.find(":") + 1));                         // Substract the "seeds: " part.

    while (seedStream >> startNum) {                                                        // While the line has a range of numbers, emplace back to the vector.
        seedStream >> endNum;
        rangeSeeds.emplace_back(rangeNum{startNum, startNum + endNum}, false);  
    }     

    skipLines(inputFile, 2);                                                                // Skip the first two lines (unnecesary).

    while (std::getline(inputFile, line)) {                                                 // For each line in the textfile.
        if (line.empty()) {                                                                     // Check if the line is empty to merge ranges and skip the void lines.
            mergeSeeds(rangeSeeds, mergedRangeSeeds, currentSeed, nextSeed);
            skipLines(inputFile, 1);
            continue;
        }
        std::istringstream mapStream(line);                                                     // Input streamline for mapping line.

        for (auto& value : map) {                                                               // For each line of mapping, extract a number and put in the indexed slot.
            mapStream >> value;
        }

        while (!rangeSeeds.empty()) {                                                           // Unpacked the pairs, and calculate the offsets. If they coincide, calculate the new value.
            const auto& [currentSeed, currentChecked] = rangeSeeds.back();              
            const auto& [firstSeed, lastSeed] = currentSeed;
            const auto& [destination, start, end] = map;
            rangeSeeds.pop_back();
            offsetStart = std::max(firstSeed, start);
            offsetEnd = std::min(lastSeed, start + end);
            if (offsetStart < offsetEnd && !currentChecked) {                                       
                newRangeSeeds.emplace_back(rangeNum{offsetStart - start + destination, offsetEnd - start + destination}, true);
                if (offsetStart > firstSeed) rangeSeeds.emplace_back(rangeNum{firstSeed, offsetStart}, false);
                if (lastSeed > offsetEnd) rangeSeeds.emplace_back(rangeNum{offsetEnd, lastSeed}, false);
            } else newRangeSeeds.emplace_back(rangeNum{firstSeed, lastSeed}, currentChecked);    
        }
        
        rangeSeeds.swap(newRangeSeeds);
        newRangeSeeds.clear();
    }

    mergeSeeds(rangeSeeds, mergedRangeSeeds, currentSeed, nextSeed);                            // Lastly, merge the range seeds to reduce the comparisons.
    auto minElement = *std::min_element(rangeSeeds.begin(), rangeSeeds.end(), [](const auto& a, const auto& b) {
        return a.first.firstNum < b.first.firstNum;
    });
    return minElement.first.firstNum;
}

// ADV 6 - FIRST PART

int adv6First(const std::string& textFile) {
    std::ifstream inputFile(textFile);                                                  // Input stream from the textfile.
    std::string line;                                                                   // String that holds each line from the textfile.
    int num{}, firstWin{}, lastWin{}, total{1};                                         // Number that holds an entity from the textfile, the first and last way to win, and the total.
    std::vector<int> timeVec, distanceVec;                                              // Vector of each time and distance value from the textfile.
    std::istringstream lineStream;                                                      // Input stream that substract the content from the textfile.

    addTimeAndDistance(inputFile, lineStream, line, num, timeVec);                      // Add the content of the time vector.
    addTimeAndDistance(inputFile, lineStream, line, num, distanceVec);                  // Add the content of the distance vector.

    /*
    for (int i = 0; i < timeVec.size(); ++i) {                                          // Prior wat to solve the problem, by iterating the range of time until it found a way to win.
        for (int j = 0; j <= timeVec[i] / 2; ++j) {                                     
            if (((timeVec[i] - j) * j) > distanceVec[i]) {                                       // If it found a way to win, then add the substraction to the total.
                total *= (timeVec[i] + 1) - (j+j);
                break;
                fixBoundary(timeVec[i], distanceVec[i], (timeVec[i] - num) / 2, -1);
                fixBoundary(timeVec[i], distanceVec[i], (timeVec[i] + num) / 2, +1);
            }
        }
    }

    return total;
    */

    for (int i = 0; i < timeVec.size(); ++i) {                                           // Alternative way to solve the problem, using quadratic formula.
        num = std::sqrt(timeVec[i] * timeVec[i] - 4 * distanceVec[i]);
        firstWin = fixBoundary(timeVec[i], distanceVec[i], (timeVec[i] - num) / 2, -1);
        lastWin = fixBoundary(timeVec[i], distanceVec[i], (timeVec[i] + num) / 2, +1);
        total *= lastWin - firstWin + 1;
    }

    return total;
}

// ADV 6 - LAST PART

long long adv6Last(const std::string& textFile) {
    std::ifstream inputFile(textFile);                                                      // Input stream from the textfile.
    std::string line, numString, totalNum;                                                  // String that holds each line from the textfile, the number casted as string, and the total.
    long long time{}, distance{}, num{}, firstWin{}, lastWin{};                             // Time, and distance values. Also, the first and last way to win, and an arbitrary number.
    std::istringstream lineStream;                                                          // Input stream that substract the content from the textfile.

    anotherAddTimeAndDistance(inputFile, lineStream, line, numString, totalNum, time);      // Add the content of the time vector.
    anotherAddTimeAndDistance(inputFile, lineStream, line, numString, totalNum, distance);  // Add the content of the distance vector.

    /*
    for (int j = 0; j <= time / 2; ++j) {                                                   // Prior wat to solve the problem, by iterating the range of time until it found a way to win.
        if (((time - j) * j) > distance) {                                                      // If it found a way to win, then add the substraction to the total.
            total = (time + 1) - (j+j);
            break;
        }
    }

    return total;
    */

    num = std::sqrt(time * time - 4 * distance);                                            // Alternative way to solve the problem, using quadratic formula.
    firstWin = fixBoundary(time, distance, (time - num) / 2, -1);
    lastWin = fixBoundary(time, distance, (time + num) / 2, +1);
    return lastWin - firstWin + 1;
}    

// ADV 7 - FIRST PART

int adv7First(const std::string& textFile) {
    std::ifstream inputFile(textFile);
    std::string line, hand;
    int bid{}, counter{}, total{};
    std::istringstream lineStream;
    DoubleLinkedList list;
   
    while (std::getline(inputFile, line)) {
        lineStream.str (line);
        lineStream >> hand >> bid;
        list.insertCard(hand, bid);
        lineStream.clear();
    }

    Card* currCard = list.head;

    while (currCard) {
        ++counter;
        total += currCard->bid * counter;
        currCard = currCard->next;
    }

    return total;
}