#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <vector>
#include <functional>
#include <string>
#include <fstream>

struct Result {
    int n;
    double avg_time;
};

class data_generator {
private:
    std::vector<int> data;
    std::vector<Result> results; 
    std::vector<double> exec_times;
    int size;
    
    std::vector<int> input_sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 
                                   11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 20000};
    int repetitions = 10;

public:
    data_generator(int n);
    
    std::vector<std::vector<int>> partition_vector(const std::vector<int>& original, size_t partition_size);
    
    void run_data_generator(std::function<void(std::vector<int>&)> algorithm);
    
    void export_to_csv(const std::string& filename) const;
    
    void set_input_sizes(const std::vector<int>& sizes) {
        input_sizes = sizes;
    }

    void set_repetitions(int reps) {
        if (reps > 0) repetitions = reps;
    }
};

#endif