#ifndef PLOTTER_HPP
#define PLOTTER_HPP

#include <string>
#include <vector>
#include <memory>

#include "function.hpp"

void plot_graph(const std::string& algorithm_name,
                const std::vector<long long>& x_data,
                const std::vector<double>& y_data,
                size_t best_fit_index,
                std::vector<std::unique_ptr<ComplexityFunction>>& functions);

#endif  // PLOTTER_HPP