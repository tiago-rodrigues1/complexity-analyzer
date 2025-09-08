#include "utils.hpp"

std::string ltrim(const std::string& s, const char* t) {
  std::string clone{ s };
  clone.erase(0, clone.find_first_not_of(t));
  return clone;
}

std::string rtrim(const std::string& s, const char* t) {
  std::string clone{ s };
  clone.erase(clone.find_last_not_of(t) + 1);
  return clone;
}

std::string trim(const std::string& s, const char* t) {
  std::string clone{ s };
  clone = ltrim(clone, t);
  clone = rtrim(clone, t);

  return clone;
}

std::vector<std::string> split(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;

  std::istringstream iss;
  iss.str(str);

  std::string token;

  while(std::getline(iss >> std::ws, token, delimiter)) {
    tokens.emplace_back(token);
  }

  return tokens;
}

bool is_valid_file(const std::string& path) {
  return std::filesystem::exists(path) and std::filesystem::is_regular_file(path);
}

void read_csv(const std::string& path, std::vector<long long>& X, std::vector<double>& Y) {
  std::ifstream data_file{ path };

  if (!is_valid_file(path) or !data_file.is_open()) {
    std::cout << ">>> Error: Não foi possível ler " << path << '\n';
    exit(EXIT_FAILURE);
  }

  std::string line;

  while(std::getline(data_file, line)) {
    if (line.size() == 0) {
      continue;
    }

    auto input = split(line, ',');

    if (input.size() < 2) {
      std::cout << "Warn: Linha inválida será ignorada:\n" << line << '\n';
      continue;
    }

    long long entry_size = std::stoll(input[0]);
    double time = std::stod(input[1]);

    if (entry_size == 0 or time == 0) {
      std::cout << "Warn: Linha inválida será ignorada:\n" << line << '\n';
    }

    X.push_back(entry_size);
    Y.push_back(time);
  }

  data_file.close();
}
