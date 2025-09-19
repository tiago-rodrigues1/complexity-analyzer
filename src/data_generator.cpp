#include "data_generator.hpp"
#include "utils.hpp"

#include <numeric>
#include <iterator>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <fstream>

DataGenerator::DataGenerator(int smp, int min, int max) : m_num_samples(smp), m_min_size(min), m_max_size(max) {
    for (int i = m_max_size; i > 0; --i) {
        data.push_back(i);
    }

    input_sizes = linspace(m_min_size, m_max_size, m_num_samples);
}

void DataGenerator::run(std::function<void(std::vector<int>&)> algorithm) {
    for (int n : input_sizes) {
        double time_sum = 0;
        std::vector<int> base_data(data.begin(), data.begin() + n);

        for (int i = 0; i < repetitions; ++i) {
            double duration_ms = calculate_time(base_data, algorithm);
            time_sum += duration_ms;
        }

        double avg_time = time_sum / repetitions;

        results.push_back({n, avg_time});
    }
}

double DataGenerator::calculate_time(std::vector<int> copy, std::function<void(std::vector<int>&)> algorithm) {
    std::this_thread::sleep_for(std::chrono::microseconds(100));

    auto start = std::chrono::high_resolution_clock::now();
    algorithm(copy);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration_ms = end - start;

    return duration_ms.count();
}

void DataGenerator::export_to_csv(const std::string& filename) const {
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
