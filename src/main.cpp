#include <iostream>
#include <math.h>
#include <memory>
#include <vector>

#include "function.hpp"
#include "utils.hpp"

void usage() {
  std::cout << "\nUsage: analyzer <csv_file>\n";
}

void setup(int argc, char* argv[], std::string& file_path) {
  if (argc <= 1) {
    std::cerr << ">>> Error: É necessário passar o caminho de um arquivo .csv\n";
    usage();

    exit(EXIT_FAILURE);
  }

  for (int i = 1; i < argc; ++i) {
    std::string current_arg{ argv[i] };

    if (current_arg == "-h" or current_arg == "--help") {
      usage();
      exit(EXIT_SUCCESS);
    } 
    
    file_path = current_arg;
    return;
  }
}

int main(int argc, char* argv[]) {
  std::string file_path;
  setup(argc, argv, file_path);

  std::vector<long> X;
  std::vector<double> Y;
  Metadata meta;
  
  read_csv(file_path, X, Y, meta);

  std::vector<double> x_cont = linspace(meta.min_entry, meta.max_entry, X.size());

  std::vector<std::unique_ptr<ComplexityFunction>> functions;
  functions.emplace_back(std::make_unique<Constant>());
  functions.emplace_back(std::make_unique<Linear>());
  functions.emplace_back(std::make_unique<Logarithmic>());
  functions.emplace_back(std::make_unique<NLogN>());
  functions.emplace_back(std::make_unique<Quadratic>());
  functions.emplace_back(std::make_unique<Cubic>());

  size_t best_guess_index = 0;
  
  for (size_t i = 0; i < functions.size(); ++i) {
    auto& func = functions[i];

    func->set_data(x_cont);
    func->set_mse(Y, meta.max_time);

    std::cout << "> " << func->get_name() << ": " << func->get_mse() << '\n';

    if (func->get_mse() < functions[best_guess_index]->get_mse()) {
      best_guess_index = i;
    }
  }

  std::cout << "\n>>> Best complexity: " << functions[best_guess_index]->get_name() << '\n';
}