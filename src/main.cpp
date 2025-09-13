#include "data_generator.hpp"
#include "utils.hpp"
#include "include/function.hpp"  // Apenas o .hpp
#include "include/plotter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

int main() {
    const std::string file_path = "resultados.csv";
    
    data_generator dg(20000);
    dg.run_data_generator([](std::vector<int>& v) {
        std::sort(v.begin(), v.end());
    });
    dg.export_to_csv(file_path);
    
    std::vector<long long> X_ll;
    std::vector<double> Y;
    Metadata meta;
    read_csv(file_path, X_ll, Y, meta);
    
    if (X_ll.empty()) {
        std::cerr << "Falha ao ler dados do CSV. Encerrando." << std::endl;
        return 1;
    }
    
    std::vector<long> X(X_ll.begin(), X_ll.end());
    std::vector<double> x_cont = linspace(meta.min_entry, meta.max_entry, X.size());
    
    // Agora isso deve funcionar
    std::vector<std::unique_ptr<ComplexityFunction>> functions;
    functions.emplace_back(std::make_unique<Linear>());
    functions.emplace_back(std::make_unique<NLogN>());
    functions.emplace_back(std::make_unique<Quadratic>());
    
    size_t best_fit_index = 0;
    double min_mse = -1.0;
    
    std::cout << "\n--- Análise de Complexidade (MSE) ---\n";
    for (size_t i = 0; i < functions.size(); ++i) {
        auto& func = functions[i];
        func->set_data(x_cont);
        func->set_mse(Y, meta.max_time);
        double current_mse = func->get_mse();
        std::cout << "> " << func->get_name() << ": MSE = " << current_mse << '\n';
        
        if (min_mse < 0 || current_mse < min_mse) {
            min_mse = current_mse;
            best_fit_index = i;
        }
    }
    
    std::cout << "\n>>> Melhor ajuste encontrado: " << functions[best_fit_index]->get_name() << '\n';
    
    plot_graph(X_ll, Y, best_fit_index);
    return 0;
}