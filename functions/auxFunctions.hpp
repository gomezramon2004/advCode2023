#pragma once

void emplaceMap(std::map<std::string, int>& hashTable, int& counter);
void checkKey(std::map<std::string, int>& hashTable, std::string& result, bool& valFound, std::string& blankline);
void checkNums(std::vector<std::vector<char>>& matrix, std::vector<int>& it, size_t& i, size_t& j, std::string& number);
void checkBorders(std::vector<std::vector<char>>& matrix, std::vector<int>& it, size_t& i, std::string& number, int LINE_COUNT, int SIZE_LINE);