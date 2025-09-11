#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <chrono>

class data_generator {
private:
    struct Result {
        int n;
        double avg_time;
    };

    int size;
    std::vector<int> data;
    std::vector<int> input_sizes = {1000, 5000, 10000, 20000};
    int repetitions = 5;
    std::vector<double> exec_times;
    std::vector<Result> results;

    std::vector<std::vector<int>> partition_vector(const std::vector<int>& original, size_t partition_size);

public:
    data_generator(int n);
    void run_data_generator(std::function<void(std::vector<int>&)> algorithm);
    void export_to_csv(const std::string& filename) const;
};

#endif