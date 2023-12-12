#pragma once

void emplaceMap(std::map<std::string, int>& hashTable, int& counter);
void checkKey(std::map<std::string, int>& hashTable, std::string& result, bool& valFound, std::string& blankline);

void insertMatrix(std::vector<std::vector<char>>& matrix, std::ifstream& inputFile, std::string& line, int LINE_COUNT, int SIZE_LINE);
void checkNextDigits(std::vector<std::vector<char>>& matrix, size_t& i, size_t& j, std::string& number, int* end = nullptr);
void checkBorders(std::vector<std::vector<char>>& matrix, std::vector<int>& iterator, size_t& i, std::string& number, int LINE_COUNT, int SIZE_LINE);

void checkGears(std::vector<std::vector<char>>& matrix, std::vector<int>& iterator, size_t& i, std::string& number, std::string& adjNumber, int LINE_COUNT, int SIZE_LINE);
void checkAdjNum(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber, int LINE_COUNT, int SIZE_LINE, bool topright = false, bool bottomleft = false);
void checkLeft(std::vector<std::vector<char>>& matrix, size_t i, size_t j, std::string& adjNumber);