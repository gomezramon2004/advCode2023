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