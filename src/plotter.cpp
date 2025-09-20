#include "include/plotter.hpp"
#include "utils.hpp"
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>
#include "gnuplot-iostream.h"

std::vector<double> normalize(const std::vector<double>& v) {
    std::vector<double> clone;
    double max = *std::max_element(v.begin(), v.end());

    for (size_t i = 0; i < v.size(); ++i) {
        clone.push_back(v[i]/max);
    }

    return clone;
}

void plot_graph(const std::string& algorithm_name,
                const std::vector<long long>& x_data,
                const std::vector<double>& y_data,
                size_t best_fit_index,
                std::vector<std::unique_ptr<ComplexityFunction>>& functions) {

  if (x_data.empty())
    return;

  std::string output_filename = "grafico_" + algorithm_name + ".png";
  std::string plot_title = "Análise de Complexidade para: " + algorithm_name;

  Gnuplot gp;
  gp << "set title '" << plot_title << "'\n"; 
  gp << "set xlabel 'Tamanho da Entrada (n)'\n";
  gp << "set ylabel 'Tempo Médio Normalizado (nano segundos)'\n";
  gp << "set grid\n";
  gp << "set key left top\n";
  gp << "set terminal pngcairo size 1200,800 font 'Arial,12'\n";
  gp << "set output '" << output_filename << "'\n";


  std::vector<std::string> func_names;
  std::vector<std::string> legend_titles;
  std::vector<std::string> colors = {"blue", "green", "red", "orange", "purple"};

  for (const auto& func : functions) {
    std::string plot_command = func->get_plot_command();
    gp << plot_command << "\n";

    std::string f_name = split(plot_command, '=')[0];
    func_names.push_back(f_name);
    legend_titles.push_back("Teórico " + func->get_name());
  }

  std::string plot_command
    = "plot '-' with points pointtype 7 pointsize 1.5 linecolor 'black' title 'Dados Empíricos'";

  for (size_t i = 0; i < func_names.size(); ++i) {
    std::string line_style = "with lines linecolor '" + colors[i] + "'";
    if (i == best_fit_index) {
      line_style += " linewidth 4 dashtype 1";
    } else {
      line_style += " linewidth 2 dashtype 2";
    }
    plot_command += ", " + func_names[i] + " " + line_style + " title '" + legend_titles[i] + "'";
  }

  gp << plot_command << "\n";
  gp.send1d(std::make_pair(x_data, normalize(y_data)));

  std::cout << "\nGráfico gerado com sucesso em '" << output_filename << "'" << std::endl;
}