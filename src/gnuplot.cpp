#include "gnuplot.hpp" // Inclui a própria declaração
#include "gnuplot-iostream.h"  // ADICIONADO: Para a classe Gnuplot
#include <cmath>              // ADICIONADO: Para log2() e pow()
#include <iostream>           // ADICIONADO: Para std::cerr/cout
#include <vector>             // ADICIONADO: Para std::vector

// A implementação (o corpo) da função vai aqui.
void plot_graph(
    const std::vector<long long>& x_data, 
    const std::vector<double>& y_data) 
{
    // ... (o resto do seu código da função plot_graph continua aqui, sem alterações)
    if (x_data.empty() || y_data.empty()) {
        std::cerr << "Não há dados para plotar!" << std::endl;
        return;
    }

    Gnuplot gp;
    // Configurações gerais do gráfico
    gp << "set title 'Análise Empírica vs. Curvas Teóricas'\n";
    gp << "set xlabel 'Tamanho da Entrada (n)'\n";
    gp << "set ylabel 'Tempo Médio (ms)'\n";
    gp << "set grid\n";
    gp << "set terminal pngcairo size 1024,768\n";
    gp << "set output 'grafico_completo.png'\n";

    // --- Lógica para as curvas teóricas ---
    long long ultimo_n = x_data.back();
    double ultimo_tempo = y_data.back();
    
    if(ultimo_n > 1) {
        // 1. Calcular um fator de escala para CADA complexidade
        double fator_n = ultimo_tempo / ultimo_n;
        double fator_nlogn = ultimo_tempo / (ultimo_n * log2(ultimo_n));
        double fator_nsquared = ultimo_tempo / (pow(ultimo_n, 2));

        // 2. Definir uma função Gnuplot para CADA complexidade
        gp << "f_n(x) = " << fator_n << " * x\n";
        gp << "f_nlogn(x) = " << fator_nlogn << " * x * (log(x)/log(2))\n";
        gp << "f_nsquared(x) = " << fator_nsquared << " * x**2\n";

        // 3. Montar o comando de plotagem com todas as curvas
        std::string plot_command = 
            "plot '-' with points title 'Dados Empíricos' pt 7, "
            "f_n(x) with lines title 'Teórico O(n)', "
            "f_nlogn(x) with lines title 'Teórico O(n log n)', "
            "f_nsquared(x) with lines title 'Teórico O(n^2)'\n";
        
        gp << plot_command;
    } else {
        // Se não for possível calcular as curvas, plota apenas os pontos
        gp << "plot '-' with points title 'Dados Empíricos' pt 7\n";
    }

    // Envia os dados dos vetores para o Gnuplot
    gp.send1d(std::make_pair(x_data, y_data));

    std::cout << "Gráfico gerado com sucesso em 'grafico_completo.png'" << std::endl;
}