#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <sstream>      // std::istringstream
#include <filesystem>
#include <iostream>
#include <fstream>

struct Metadata {
  long max_entry = 0;
  double max_time = 0.0;
  long min_entry = 0;
  double min_time = 0.0;
};

std::string trim(const std::string& s, const char* t = " \t\n\r\f\v");
std::vector<std::string> split(const std::string& str, char delimiter);
void read_csv(const std::string& path, std::vector<long long>& X, std::vector<double>& Y, Metadata& meta);
std::vector<double> linspace(double start, double end, int num_points);
#endif