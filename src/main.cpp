#include "data_generator.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"


int main(int argc, char* argv[]) {
  const std::string file_path = "resultados.csv";

  data_generator dg(20000);
  dg.run_data_generator([](std::vector<int>& v) {
    std::sort(v.begin(), v.end());
  });
  dg.export_to_csv(file_path); 

  std::vector<long long> X;
  std::vector<double> Y;
  read_csv(file_path, X, Y); 

  std::cout << "\n--- Lendo dados do CSV ---\n";
  for (size_t i = 0; i < X.size(); ++i) {
    std::cout << "X: " << X[i] << " | Y: " << Y[i] << '\n';
  }

  return 0;
}