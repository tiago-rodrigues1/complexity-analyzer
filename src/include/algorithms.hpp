#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>

int sequential_search(const std::vector<int>& arr, int target);
int binary_search(const std::vector<int>& arr, int target);
void bubble_sort(std::vector<int>& arr);
void merge_sort(std::vector<int>& arr);

#endif
