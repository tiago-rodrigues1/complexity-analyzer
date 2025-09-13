#include <iostream>
#include <vector>

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

  std::vector<long long> X;
  std::vector<double> Y;

  read_csv(file_path, X, Y);

  for (size_t i = 0; i < X.size(); ++i) {
    std::cout << "(" << X[i] << "; " << Y[i] << ")\n";
  }
}