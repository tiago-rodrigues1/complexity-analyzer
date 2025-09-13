#include "data_generator.hpp"
#include "utils.hpp"
#include "include/function.hpp"
#include "include/plotter.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

int main() {
    const std::string file_path = "resultados.csv";
    
    data_generator dg(20000);
    
    std::cout << "=== Iniciando Coleta de Dados ===" << std::endl;
    dg.run_data_generator([](std::vector<int>& v) {
        std::sort(v.begin(), v.end());
    });
    dg.export_to_csv(file_path);
    
    std::cout << "\n=== Analisando Resultados ===" << std::endl;
    
    std::vector<long long> X_ll;
    std::vector<double> Y;
    Metadata meta;
    read_csv(file_path, X_ll, Y, meta);
    
    if (X_ll.empty()) {
        std::cerr << "Falha ao ler dados do CSV. Encerrando." << std::endl;
        return 1;
    }
    
    std::cout << "Dados lidos: " << X_ll.size() << " pontos" << std::endl;
    std::cout << "Tamanho mín: " << meta.min_entry << ", máx: " << meta.max_entry << std::endl;
    std::cout << "Tempo mín: " << meta.min_time << " ms, máx: " << meta.max_time << " ms" << std::endl;
    
    std::vector<long> X(X_ll.begin(), X_ll.end());
    std::vector<double> x_cont = linspace(meta.min_entry, meta.max_entry, X.size());
    
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
    
    std::cout << "\n>>> Best complexity: " << functions[best_fit_index]->get_name() << '\n';
    
    std::cout << "\n=== Gerando Gráfico ===" << std::endl;
    plot_graph(X_ll, Y, best_fit_index);
    
    return 0;
}