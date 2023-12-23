#pragma once

void emplaceMap(std::map<std::string, int>& hashTable, int& counter);
void checkKey(std::map<std::string, int>& hashTable, std::string& result, bool& valFound, std::string& blankline);

void insertMatrix(std::vector<std::vector<char>>& matrix, std::ifstream& inputFile, std::string& line, int LINE_COUNT, int SIZE_LINE);
void checkNextDigits(std::vector<std::vector<char>>& matrix, size_t& i, size_t& j, std::string& number, int* end = nullptr);
void checkBorders(std::vector<std::vector<char>>& matrix, std::vector<int>& iterator, size_t& i, std::string& number, int LINE_COUNT, int SIZE_LINE);

void checkGears(std::vector<std::vector<char>>& matrix, std::vector<int>& iterator, size_t& i, std::string& number, std::string& adjNumber, int LINE_COUNT, int SIZE_LINE);
void checkAdjNum(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber, int LINE_COUNT, int SIZE_LINE, bool topright = false, bool bottomleft = false);
void checkLeft(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber);

void mergeSort(std::vector<int>& vec, int left, int right);
void merge(std::vector<int>& vec, int left, int mid, int right);
bool binarySearch(const std::vector<int>& arr, int target);

void recursiveScratch(int& total, std::vector<std::vector<int>>& winVec, std::vector<std::vector<int>>& numVec, const int oldIt, const int oldPoints);

struct rangeNum { 
    long long firstNum, lastNum; 

    bool operator<(const rangeNum& other) const {
        return this->firstNum < other.firstNum || (!(other.firstNum < this->firstNum) && this->lastNum < other.lastNum);
    }

    bool operator==(const rangeNum& other) const {
        return this->firstNum == other.firstNum && this->lastNum == other.lastNum;
    }
};

void skipLines(std::istream& stream, int numLinesToSkip);

void recursiveMerge(const std::vector<std::pair<rangeNum, bool>>& seeds, const rangeNum& currentSeed, rangeNum& nextSeed, size_t& i);

void mergeSeeds(std::vector<std::pair<rangeNum, bool>>& rangeSeeds, std::vector<std::pair<rangeNum, bool>>& mergedRangeSeeds, rangeNum& currentSeed, rangeNum& nextSeed);