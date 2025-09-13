#include "data_generator.hpp"
#include <numeric>
#include <iterator> 
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

data_generator::data_generator(int n) : size(n) {
    for(int i = n; i > 0; --i) {
        data.push_back(i);
    }
}

std::vector<std::vector<int>> data_generator::partition_vector(const std::vector<int>& original, size_t partition_size){
    std::vector<std::vector<int>> result;

    if (partition_size == 0) return result;

    auto it = original.cbegin();
    const auto end = original.cend();

    while (it != end) {
        auto end_partition = static_cast<size_t>(std::distance(it, end)) < partition_size
                                 ? end
                                 : std::next(it, partition_size);

        result.emplace_back(it, end_partition);
        it = end_partition;
    }

    return result;
}

void data_generator::run_data_generator(std::function<void(std::vector<int>&)> algorithm) {
    for (int n : input_sizes) {
        exec_times.clear();

    
        std::vector<int> test_data;
        test_data.reserve(n); 
        for(int i = n; i > 0; --i) {
            test_data.push_back(i);
        }

        {
            auto warmup_copy = test_data;
            algorithm(warmup_copy);
        }

    
        std::vector<double> valid_times;
        
        for (int i = 0; i < repetitions + 5; ++i) {
            auto copy = test_data;

            std::this_thread::sleep_for(std::chrono::microseconds(100)); 
            
            auto start = std::chrono::high_resolution_clock::now();
            algorithm(copy);
            auto end = std::chrono::high_resolution_clock::now();
          
            std::chrono::duration<double, std::milli> duration_ms = end - start;
            
            exec_times.push_back(duration_ms.count());
        }
        
        std::sort(exec_times.begin(), exec_times.end());
        
        // Remover 20% dos valores mais extremos (10% de cada lado)
        size_t remove_count = exec_times.size() / 10;
        if (remove_count > 0) {
            exec_times.erase(exec_times.begin(), exec_times.begin() + remove_count);
            exec_times.erase(exec_times.end() - remove_count, exec_times.end());
        }
        
        // Calcular média dos valores filtrados
        double sum_times = std::accumulate(exec_times.begin(), exec_times.end(), 0.0);
        double avg_time = sum_times / exec_times.size();
        
        results.push_back({n, avg_time});
    }
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