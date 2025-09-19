#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <limits>

class ComplexityFunction {
protected:
  std::string name;
  std::vector<double> data;
  double mse;

private:

// Finds the best fit line (linear regression) for the given points
std::pair<double,double> linear_regression(const std::vector<double>& x, const std::vector<double>& y) const {
    size_t n = x.size();
    double sum_x = std::accumulate(x.begin(), x.end(), 0.0);
    double sum_y = std::accumulate(y.begin(), y.end(), 0.0);
    double sum_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
    double sum_x2 = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);

    double denominator = n * sum_x2 - sum_x * sum_x;
    double a = (denominator != 0) ? (n * sum_xy - sum_x * sum_y) / denominator : 0;
    double b = (sum_y - a * sum_x) / n;

    return {a, b};
}

// Computes the Mean Squared Error between predicted and actual values
double compute_mse(const std::vector<double>& x, const std::vector<double>& y, double a, double b) const {
    double sum = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double predicted = a * x[i] + b;
        double error = y[i] - predicted;
        sum += error * error;
    }
    return sum / x.size(); // computes the mean of squared errors
}

public:
  ComplexityFunction(const std::string& nm) : name(nm) {}
  virtual ~ComplexityFunction() = default;
  
  virtual double expected_value(double n) = 0;

  std::string get_name() const {
    return name;
  }

  void set_data(const std::vector<double>& x) {
    data.clear();
    data.reserve(x.size());

    for (const auto& n : x) {
      data.push_back(expected_value(n));
    }
  }

  void set_mse(const std::vector<double>& y, double max_y) {
    if (y.size() != data.size()) {
        mse = std::numeric_limits<double>::max();
        return;
    }

    if (data.empty()) {
        mse = std::numeric_limits<double>::max();
        return;
    }

    double max_theoretical = *std::max_element(data.begin(), data.end());
    if (max_theoretical == 0 || max_y == 0) {
        mse = std::numeric_limits<double>::max();
        return;
    }

    // Normalize values
    std::vector<double> x_norm(data.size());
    std::vector<double> y_norm(y.size());
    for (size_t i = 0; i < data.size(); ++i) {
        x_norm[i] = data[i] / max_theoretical;
        y_norm[i] = y[i] / max_y;
    }

    // Fit linear regression
    auto [a, b] = linear_regression(x_norm, y_norm);

    // Compute MSE
    mse = compute_mse(x_norm, y_norm, a, b);

    // Penalize if slope is negative
    if (a < 0) {
        mse *= 10;
    }
  }

  double get_mse() const {
    return mse;
  }
  
  const std::vector<double>& get_data() const {
    return data;
  }
};

/// Complexity Functions
class Constant : public ComplexityFunction {
public:
  Constant() : ComplexityFunction("O(1)") {}
  double expected_value(double n) override;
};

class Linear : public ComplexityFunction {
public:
  Linear() : ComplexityFunction("O(n)") {}
  double expected_value(double n) override;
};

class Logarithmic : public ComplexityFunction {
public:
  Logarithmic() : ComplexityFunction("O(log n)") {}
  double expected_value(double n) override;
};

class NLogN : public ComplexityFunction {
public:
  NLogN() : ComplexityFunction("O(n log n)") {}
  double expected_value(double n) override;
};

class Quadratic : public ComplexityFunction {
public:
  Quadratic() : ComplexityFunction("O(n^2)") {}
  double expected_value(double n) override;
};

class Cubic : public ComplexityFunction {
public:
  Cubic() : ComplexityFunction("O(n^3)") {}
  double expected_value(double n) override;
};

class Exponential : public ComplexityFunction {
public:
  Exponential() : ComplexityFunction("O(2^n)") {}
  double expected_value(double n) override;
};

class Factorial : public ComplexityFunction {
public:
  Factorial() : ComplexityFunction("O(n!)") {}
  double expected_value(double n) override;
};

#endif
