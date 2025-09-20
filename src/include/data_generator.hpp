#ifndef DATA_GENERATOR_HPP
#define DATA_GENERATOR_HPP

#include <fstream>
#include <functional>
#include <string>
#include <vector>

struct Result {
  int n;
  double avg_time;
};

class DataGenerator {
private:
  int m_num_samples;
  int m_min_size;
  int m_max_size;
  std::vector<double> input_sizes;
  std::vector<int> data;
  std::vector<Result> results;

  int repetitions = 20;

public:
  DataGenerator(int smp, int min, int max);

  void run(std::function<void(std::vector<int>&)> algorithm);
  void export_to_csv(const std::string& filename) const;
  double calculate_time(std::vector<int> copy, std::function<void(std::vector<int>&)> algorithm);
};

#endif