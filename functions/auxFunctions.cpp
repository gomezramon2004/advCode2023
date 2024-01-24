#include "functions.hpp"
#include "auxFunctions.hpp"
#include <iostream>
#include <fstream>

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
    
    rangeSeeds.swap(mergedRangeSeeds);
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

// ADV 6 - Last Part

// Calculate the add and distance values concatenating the numbers
void anotherAddTimeAndDistance(std::ifstream& input, std::istringstream& stream, std::string& line, std::string& numString, std::string& totalNum, long long& total) {
    std::getline(input, line);
    stream.str (line.substr(line.find(":") + 1));

    while (stream >> numString) totalNum += numString ;

    total = stoll(totalNum);
    totalNum = "";
    stream.clear();
}

// ADV 7 - Classes (Created by me instead of using a library to practice memory handling)


// Class ----- Card -----

// Card - Clear
void Card::Clear() {
    this->next = nullptr;
    this->prev = nullptr;
}

// Card - Constructor
Card::Card() : hand(""), bid(0), type(NULLDATA), next(nullptr), prev(nullptr) {}

// Card - Constructor with parameters
Card::Card(const std::string& hand, const int& bid) : hand(hand), bid(bid), next(nullptr), prev(nullptr) {}

// Card - Copy Constructor
Card::Card(const Card& other) : hand(other.hand), bid(other.bid), type(other.type), next(other.next), prev(other.prev) {}

// Card - Copy Assignment Operator
Card& Card::operator=(const Card& other) {
    if (this != &other) {
        this->hand = other.hand;
        this->bid = other.bid;
        this->type = other.type;
        this->next = other.next;
        this->prev = other.prev;
    }
    return *this;
}

// Card - Move Constructor
Card::Card(Card&& other) noexcept : hand(std::move(other.hand)), bid(std::move(other.bid)), type(std::move(other.type)), next(other.next), prev(other.prev) {
    other.next = other.prev = nullptr;
}

// Card - Move Assignment Operator
Card& Card::operator=(Card&& other) noexcept {
    if (this != &other) {
        this->hand = std::move(other.hand);
        this->bid = std::move(other.bid);
        this->type = std::move(other.type);
        this->next = other.next;
        this->prev = other.prev;
        other.Clear();
    }
    return *this;
}

// Card - Destructor
Card::~Card() { this->Clear(); }


// Class ----- DoubleLinkedList -----

// DoubleLinkedList - Clear 
void DoubleLinkedList::Clear() {
    Card* currentTail = this->tail;

    while (currentTail) {
        Card* priorCard = currentTail->prev;
        delete currentTail;
        currentTail = priorCard;
    }

    this->head = this->tail = nullptr;
}

// DoubleLinkedlist - Put the Card Before
void DoubleLinkedList::putBefore(Card* newCard, Card* currCard) {
    newCard->prev = currCard->prev;
    currCard->prev = newCard;
    newCard->next = currCard;
    !newCard->prev ? this->head = newCard : newCard->prev->next = newCard;
}

// DoubleLinkedlist - Put the Card After
void DoubleLinkedList::putAfter(Card* newCard, Card* currCard) {
    newCard->next = currCard->next;
    currCard->next = newCard;
    newCard->prev = currCard;
    if (newCard->next) newCard->next->prev = newCard;
}


// DoubleLinkedList - Add Type of Card
void DoubleLinkedList::addType(const std::unordered_map<char, int>& content, Card& currCard) {
    switch (content.size()) {
        case 5: currCard.type = HIGH_CARD; return;
        case 4: currCard.type = ONE_PAIR; return; 
        case 3: {
            for (const auto& pair : content) {
                if (pair.second == 3) {
                    currCard.type = THREE_OF_A_KIND; return;
                }
            }
            currCard.type = TWO_PAIR; return;
        }
        case 2: {
            for (const auto& pair : content) {
                if (pair.second == 4) {
                    currCard.type = FOUR_OF_A_KIND; return;
                }
            }
            currCard.type = FULL_HOUSE; return;
        }
        case 1: currCard.type = FIVE_OF_A_KIND; return;
    }
}

// DoubleLinkedlist - Auxiliar Recursive Method
void DoubleLinkedList::recursiveHand(const Card* newCard, Card*& currCard, const int& i, const int& newIndex, int& currIndex, const Card* last) {
    if (!currCard->next || currCard->next->type != newCard->type || currCard == last) return;               // Constraints.
    currCard = currCard->next;                                                                              // Next Card.
    currIndex = std::distance(strArr.begin(), std::find(strArr.begin(), strArr.end(), currCard->hand[i]));  // Calculate the new current index.
    if (newIndex < currIndex) recursiveHand(newCard, currCard, i, newIndex, currIndex, last);               // If new index is still stronger, then recurse again.
    else if (newIndex > currIndex) currCard = currCard->prev;                                               // If not, then return to the prior card.
}

// DoubleLinkedlist - Another Auxiliar Recursive Method
void DoubleLinkedList::recursiveType(const Card* newCard, Card*& currCard, const int& i, const int& newIndex, int& currIndex, Card*& last) {
    if (!currCard->next || currCard->next->type != newCard->type || currCard == last) {                         // Constraints.
        last = currCard;
    } else {
        currCard = currCard->next;                                                                                  // Next Card.
        currIndex = std::distance(strArr.begin(), std::find(strArr.begin(), strArr.end(), currCard->hand[i]));      // Calculate the new current index.
        if (newIndex == currIndex) recursiveType(newCard, currCard, i, newIndex, currIndex, last);                  // If new index is still equal, then recurse again.
        else {                                                                                                      // If not, then return to the prior card.
            currCard = currCard->prev;
            last = currCard;
        }
    }
}

// DoubleLinkedList - Constructor
DoubleLinkedList::DoubleLinkedList() : head(nullptr), tail(nullptr) {}

// DoubleLinkedList - Copy Constructor
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& other) : head(nullptr), tail(nullptr) {
    Card* currCard = other.head;

    while (currCard) {
        Card* newCard = new Card(*currCard);
        if (!this->head) {
            this->head = this->tail = newCard;
        } else {
            this->tail->next = newCard;
            newCard->prev = tail;
            this->tail = newCard;
        }
        currCard = currCard->next;
    }
}

// DoubleLinkedList - Copy Assignment Operator
DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& other) {
    if (this != &other) {
        this->Clear();
        Card* currCard= other.head;

        while (currCard) {
            Card* newCard = new Card(*currCard);
            if (!this->head) {
                this->head = this->tail = newCard;
            } else {
                this->tail->next = newCard;
                newCard->prev = tail;
                this->tail = newCard;
            }
            currCard = currCard->next;
        }
    }
    return *this;
}

// DoubleLinkedList - Move Constructor
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& other) noexcept : head(std::move(other.head)), tail(std::move(other.tail)) {
    other.head = other.tail = nullptr;
}

// DoubleLinkedList - Move Assignment Operator
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& other) noexcept {
    if (this != &other) {
        this->Clear();
        this->head = std::move(other.head);
        this->tail = std::move(other.tail);
        other.head = other.tail = nullptr;
    }
    return *this;
}

// DoubleLinkedList - Destructor
DoubleLinkedList::~DoubleLinkedList() { this->Clear(); }

// DoubleLinkedList - Set Strength Array
void DoubleLinkedList::setStr(const std::array<char, 13>&& arr) {
    for (int i = 0; i < strArr.size(); i++){
        strArr[i] = arr[i];
    } 
}

// DoubleLinkedList - Insert Card
void DoubleLinkedList::insertCard(const std::string& hand, const int& bid, const bool&& wildcard) {
    std::unordered_map<char, int> content;                  // Unordered map that holds a certain character and how many times is it repeated.
    char maxLetter;                                         // Most repetitive letter on a card.
    int currIndex{}, newIndex{}, jCounter{}, maxAmount{};   // Current, New Index, J-Counter, Most repetitive letter on a card.
    Card* newCard = new Card(hand, bid);                    // New Card
    Card* currCard = this->head;                            // Current Card.
    Card* firstOfKind = nullptr;                            // Pointer to the first card that shares something from the new card.
    Card* lastOfKind = nullptr;                             // Pointer to the first card that shares something from the new card.

    if (wildcard && hand != "JJJJJ") {                      // Fill the unordered map using the hand from the new card.
        for (const auto& letter : hand) {
            letter != 'J' ? ++content[letter] : ++jCounter;
        }
        if (jCounter) {
            for (const auto [letter, amount] : content) {
                if (amount > maxAmount) {
                    maxAmount = amount;
                    maxLetter = letter;
                }
            }
            content.at(maxLetter) += jCounter;
        }
    } else for (const auto& letter : hand) ++content[letter];

    this->addType(content, *newCard);                       // Add the type from the new card in base of the unordered map.

    if (!this->head) {                                      // If there's a empty list.
        this->head = newCard;
    } else {
        while (currCard->type < newCard->type && currCard->next) currCard = currCard->next;
        if (currCard->type > newCard->type) {
            putBefore(newCard, currCard);                                                       // It means that the new card has a better type than the current.
        } else if (currCard->type == newCard->type) {
            firstOfKind = currCard;

            for (int i = 0; i < newCard->hand.length(); i++) {                                  // Check the characters of the hand, and compare it to another cards
                currCard = firstOfKind;
                currIndex = std::distance(strArr.begin(), std::find(strArr.begin(), strArr.end(), currCard->hand[i]));
                newIndex = std::distance(strArr.begin(), std::find(strArr.begin(), strArr.end(), newCard->hand[i]));
                if (newIndex < currIndex) { 
                    recursiveHand(newCard, currCard, i, newIndex, currIndex, lastOfKind);
                    if (newIndex == currIndex) {
                        firstOfKind = currCard;
                        recursiveType(newCard, currCard, i, newIndex, currIndex, lastOfKind);
                        continue;
                    }
                    putAfter(newCard, currCard);                                                // It means that the new card is stronger, so needs to be after.
                    return;
                } else if (newIndex > currIndex) {
                    putBefore(newCard, currCard);                                               // It means that the current card is stronger, so needs to be before.
                    return;
                } else {
                    firstOfKind = currCard;
                    recursiveType(newCard, currCard, i, newIndex, currIndex, lastOfKind);       // It means that both are equally stronger, so needs to recurse cards.
                }   
            }

            putBefore(newCard, currCard);                                                       // It means that new and current cards have the same hands and type.
        } else {
            putAfter(newCard, currCard);                                                        // It means that the new card has a worse type than the current.
        }
    }
}

// DoubleLinkedList - Display
void DoubleLinkedList::displayCards() {
    Card* currCard = this->head;

    while (currCard) {
        std::cout << currCard->hand << " " << currCard->bid << " " << currCard->type << "\n";
        currCard = currCard->next;
    }
}