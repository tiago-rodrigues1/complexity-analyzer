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

  while (std::getline(iss >> std::ws, token, delimiter)) {
    tokens.emplace_back(token);
  }

  return tokens;
}

bool is_valid_file(const std::string& path) {
  return std::filesystem::exists(path) and std::filesystem::is_regular_file(path);
}

void read_csv(const std::string& path, std::vector<long long>& X, std::vector<double>& Y, Metadata& meta) {
  std::ifstream data_file{ path };

  if (!is_valid_file(path) or !data_file.is_open()) {
    std::cout << ">>> Error: Não foi possível ler " << path << '\n';
    exit(EXIT_FAILURE);
  }

  std::string line;

  while (std::getline(data_file, line)) {
    if (line.size() == 0) {
      continue;
    }

    auto input = split(line, ',');

    if (input.size() < 2) {
      std::cout << ">>> Warn: Linha inválida será ignorada:\n" << "> " << line << '\n';
      continue;
    }

    try {
      int entry_size = std::stoll(input[0]);
      double time = std::stod(input[1]);

      if (X.size() == 0) {
        meta.min_entry = entry_size;
        meta.min_time = time;
      }

      if (entry_size < meta.min_entry) {
        meta.min_entry = entry_size;
      }

      if (time < meta.min_time) {
        meta.min_time = time;
      }

      if (entry_size > meta.max_entry) {
        meta.max_entry = entry_size;
      }

      if (time > meta.max_time) {
        meta.max_time = time;
      }

      X.push_back(entry_size);
      Y.push_back(time);
    } catch (const std::exception& e) {
      std::cout << ">>> Warn: Linha inválida será ignorada:\n" << "> " << line << '\n';
    }
  }

  data_file.close();
}

std::vector<double> linspace(int start, int end, int num_points) {
  std::vector<double> result(num_points);
  int step = (end - start) / (num_points - 1);
  for (int i = 0; i < num_points; ++i) {
    result[i] = start + step * i;
  }
  return result;
}
