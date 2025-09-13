// src/plotter.cpp

#include "include/plotter.hpp"
#include "gnuplot-iostream.h"
#include <cmath>
#include <iostream>
#include <vector>

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
    gp << "set terminal pngcairo size 1024,768\n";
    gp << "set output 'grafico_analise.png'\n";

    long long ultimo_n = x_data.back();
    double ultimo_tempo = y_data.back();
    
    if(ultimo_n > 1) {
        double fator_n = ultimo_tempo / ultimo_n;
        double fator_nlogn = ultimo_tempo / (ultimo_n * log2(ultimo_n));
        double fator_nsquared = ultimo_tempo / (pow(ultimo_n, 2));

        gp << "f_n(x) = " << fator_n << " * x\n";
        gp << "f_nlogn(x) = " << fator_nlogn << " * x * (log(x)/log(2))\n";
        gp << "f_nsquared(x) = " << fator_nsquared << " * x**2\n";

        std::vector<std::string> func_names = {"f_n(x)", "f_nlogn(x)", "f_nsquared(x)"};
        std::vector<std::string> legend_titles = {"Teórico O(n)", "Teórico O(n log n)", "Teórico O(n^2)"};

        std::string plot_command = "plot '-' with points title 'Dados Empíricos' pt 7 lc 'black'";

        for(size_t i = 0; i < func_names.size(); ++i) {
            plot_command += ", " + func_names[i] + " with lines title '" + legend_titles[i] + "'";
            // Se for o melhor índice, adiciona um estilo de destaque (linha mais grossa)
            if(i == best_fit_index) {
                plot_command += " lw 3"; // lw = line width
            }
        }
        
        gp << plot_command << "\n";
    } else {
        gp << "plot '-' with points title 'Dados Empíricos' pt 7\n";
    }

    gp.send1d(std::make_pair(x_data, y_data));
    std::cout << "Gráfico gerado com sucesso em 'grafico_analise.png'" << std::endl;
}