#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>      // std::istringstream
#include <filesystem>
#include <iostream>
#include <fstream>

std::string trim(const std::string& s, const char* t = " \t\n\r\f\v");
std::vector<std::string> split(const std::string& str, char delimiter);
void read_csv(const std::string& path, std::vector<long long>& X, std::vector<double>& Y);
#endif