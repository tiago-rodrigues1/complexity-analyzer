#include "data_generator.hpp"
#include "utils.hpp"
#include "function.hpp"
#include "plotter.hpp"
#include "algorithms.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
#include <functional>

struct Algorithm {
    std::string name;
    std::function<void(std::vector<int>&)> function;
};

void analyze_and_plot(const std::string& algorithm_name, const std::string& file_path) {
    std::cout << "\n=== Analisando Resultados de '" << algorithm_name << "' ===" << std::endl;
    
    std::vector<long long> X_ll;
    std::vector<double> Y;
    Metadata meta;

    read_csv(file_path, X_ll, Y, meta);

    if (X_ll.empty()) {
        std::cerr << "Falha ao ler dados do CSV '" << file_path << "'. Pulando análise." << std::endl;
        return;
    }

    std::cout << "Dados lidos: " << X_ll.size() << " pontos" << std::endl;
    std::cout << "Tamanho mín: " << meta.min_entry << ", máx: " << meta.max_entry << std::endl;
    std::cout << "Tempo mín: " << meta.min_time << " ms, máx: " << meta.max_time << " ms" << std::endl;

    std::vector<double> x_cont = linspace(meta.min_entry, meta.max_entry, X_ll.size());

    std::vector<std::unique_ptr<ComplexityFunction>> functions;
    functions.emplace_back(std::make_unique<Linear>());
    functions.emplace_back(std::make_unique<NLogN>());
    functions.emplace_back(std::make_unique<Quadratic>());

    size_t best_fit_index = 0;
    double min_mse = std::numeric_limits<double>::max();

    std::cout << "\n--- Análise de Complexidade (MSE) ---" << std::endl;
    for (size_t i = 0; i < functions.size(); ++i) {
        auto& func = functions[i];
        func->set_data(x_cont);
        func->set_mse(Y, meta.max_time);
        double current_mse = func->get_mse();

        std::cout << "> " << func->get_name() << ": MSE = " << std::fixed << current_mse << std::endl;

        if (current_mse < min_mse) {
            min_mse = current_mse;
            best_fit_index = i;
        }
    }

    std::cout << "\n>>> Melhor complexidade: " << functions[best_fit_index]->get_name() << '\n';

    std::cout << "\n=== Gerando Gráfico para '" << file_path << "' ===" << std::endl;
    plot_graph(algorithm_name, X_ll, Y, best_fit_index);
}


int main() {
    const int MIN_SIZE = 1000;
    const int MAX_SIZE = 20000;
    const int N_SAMPLES = 20;

    std::vector<Algorithm> algorithms = {
        {
            "sequential_search",
            [](std::vector<int>& v) {
                sequential_search(v, -1); // O(n)
            }
        }
        // {
        //     "binary_search",
        //     [](std::vector<int>& v) {
        //         binary_search(v, v[v.size() / 2]); // O(log n)
        //     }
        // },
        // {
        //     "bubble_sort",
        //     [](std::vector<int>& v) {
        //         bubble_sort(v); // O(n^2)
        //     }
        // },
        // {
        //     "merge_sort",
        //     [](std::vector<int>& v) {
        //         merge_sort(v); // O(n log n)
        //     }
        // }
    };

    DataGenerator dg(N_SAMPLES, MIN_SIZE, MAX_SIZE);

    for (const auto& algo : algorithms) {
        std::cout << "\n=========================================\n";
        std::cout << "   Executando: " << algo.name << std::endl;
        std::cout << "=========================================\n";

        
        dg.run(algo.function);

        std::string filename = algo.name + ".csv";
        dg.export_to_csv(filename);


        // analyze_and_plot(algo.name, filename);
    }
    
    return 0;
}