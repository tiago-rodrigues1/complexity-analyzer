#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <vector>
#include <string>

void plot_graph(
    const std::vector<long long>& x_data, 
    const std::vector<double>& y_data,
    size_t best_fit_index);

#endif // PLOTTER_HPP