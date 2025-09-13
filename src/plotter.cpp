#include "include/plotter.hpp"
#include "gnuplot-iostream.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <numeric>

std::pair<double, double> linear_regression(const std::vector<long long>& x_data, 
                                           const std::vector<double>& y_data,
                                           std::function<double(double)> transform_x) {
    size_t n = x_data.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    
    for (size_t i = 0; i < n; ++i) {
        double x_transformed = transform_x(static_cast<double>(x_data[i]));
        double y = y_data[i];
        
        sum_x += x_transformed;
        sum_y += y;
        sum_xy += x_transformed * y;
        sum_x2 += x_transformed * x_transformed;
    }
    
    double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double intercept = (sum_y - slope * sum_x) / n;
    
    return {slope, intercept};
}

void plot_graph(
    const std::vector<long long>& x_data, 
    const std::vector<double>& y_data,
    size_t best_fit_index) 
{
    if (x_data.empty()) return;

    Gnuplot gp;
    gp << "set title 'Análise de Complexidade Empírica vs. Teórica'\n";
    gp << "set xlabel 'Tamanho da Entrada (n)'\n";
    gp << "set ylabel 'Tempo Médio (ms)'\n";
    gp << "set grid\n";
    gp << "set key left top\n"; 
    gp << "set terminal pngcairo size 1200,800 font 'Arial,12'\n"; 
    gp << "set output 'grafico_analise.png'\n";

    
    // Para O(n)
    auto [a_linear, b_linear] = linear_regression(x_data, y_data, [](double x) { return x; });
    
    // Para O(n log n)
    auto [a_nlogn, b_nlogn] = linear_regression(x_data, y_data, [](double x) { return x * log2(x); });
    
    // Para O(n²)
    auto [a_quad, b_quad] = linear_regression(x_data, y_data, [](double x) { return x * x; });

    gp << "f_n(x) = " << a_linear << " * x + " << b_linear << "\n";
    gp << "f_nlogn(x) = " << a_nlogn << " * x * (log(x)/log(2)) + " << b_nlogn << "\n";
    gp << "f_nsquared(x) = " << a_quad << " * x**2 + " << b_quad << "\n";

    std::vector<std::string> func_names = {"f_n(x)", "f_nlogn(x)", "f_nsquared(x)"};
    std::vector<std::string> legend_titles = {"Teórico O(n)", "Teórico O(n log n)", "Teórico O(n²)"};
    std::vector<std::string> colors = {"blue", "green", "red"};

    std::string plot_command = "plot '-' with points pointtype 7 pointsize 1.5 linecolor 'black' title 'Dados Empíricos'";

    for(size_t i = 0; i < func_names.size(); ++i) {
        std::string line_style = "with lines linecolor '" + colors[i] + "'";
        
        if(i == best_fit_index) {
            line_style += " linewidth 4 dashtype 1"; // Linha mais grossa e sólida
        } else {
            line_style += " linewidth 2 dashtype 2"; // Linha mais fina e tracejada
        }
        
        plot_command += ", " + func_names[i] + " " + line_style + " title '" + legend_titles[i] + "'";
    }
    
    gp << plot_command << "\n";
    gp.send1d(std::make_pair(x_data, y_data));

    std::cout << "\n=== Métricas de Ajuste ===" << std::endl;
    std::cout << "O(n): a=" << a_linear << ", b=" << b_linear << std::endl;
    std::cout << "O(n log n): a=" << a_nlogn << ", b=" << b_nlogn << std::endl;
    std::cout << "O(n²): a=" << a_quad << ", b=" << b_quad << std::endl;
    
    std::cout << "\nGráfico gerado com sucesso em 'grafico_analise.png'" << std::endl;
}