#include "data_generator.hpp"

#include <numeric>
#include <iterator>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <fstream>

data_generator::data_generator(int n) : size(n) {
    for (int i = n; i > 0; --i) {
        data.push_back(i);
    }
}

void data_generator::run_data_generator(std::function<void(std::vector<int>&)> algorithm) {
    for (int n : input_sizes) {
        exec_times.clear();

        std::vector<int> base_data(data.begin(), data.begin() + n);

        for (int i = 0; i < repetitions + 5; ++i) {
            auto copy = base_data; 
            double duration_ms = calculate_time(copy, algorithm);
            exec_times.push_back(duration_ms);
        }

        std::sort(exec_times.begin(), exec_times.end());
        double avg_time = calculate_median(exec_times);

        results.push_back({n, avg_time});
    }
}

double data_generator::calculate_time(std::vector<int>& copy,
                                      std::function<void(std::vector<int>&)> algorithm) {
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    auto start = std::chrono::high_resolution_clock::now();

    algorithm(copy);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;

    return duration_ms.count();
}

double data_generator::calculate_median(std::vector<double> times) {
    if (times.empty()) return 0.0;

    double sum_times = std::accumulate(times.begin(), times.end(), 0.0);
    return sum_times / times.size();
}

void data_generator::export_to_csv(const std::string& filename) const {
    std::ofstream output_file(filename);

    if (!output_file.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo " << filename << std::endl;
        return;
    }

    output_file << "tamanho,tempo_ms\n";

    for (const auto& result : results) {
        output_file << result.n << "," << std::fixed << result.avg_time << "\n";
    }

    output_file.close();
    std::cout << "Resultados exportados com sucesso para " << filename << std::endl;
}
