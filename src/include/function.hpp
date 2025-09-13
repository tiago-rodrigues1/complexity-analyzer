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
      std::cerr << "Invalido\n";
      mse = std::numeric_limits<double>::max();
      return;
    }

    size_t n = y.size();
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    
    double max_theoretical = *std::max_element(data.begin(), data.end());
    if (max_theoretical == 0) {
      mse = std::numeric_limits<double>::max();
      return;
    }
    
    for (size_t i = 0; i < n; ++i) {
      double x_norm = data[i] / max_theoretical;
      double y_norm = y[i] / max_y;
      
      sum_x += x_norm;
      sum_y += y_norm;
      sum_xy += x_norm * y_norm;
      sum_x2 += x_norm * x_norm;
    }
    
    double denominator = n * sum_x2 - sum_x * sum_x;
    double a = (denominator != 0) ? (n * sum_xy - sum_x * sum_y) / denominator : 0;
    double b = (sum_y - a * sum_x) / n;
    
    double sum = 0;
    for (size_t i = 0; i < n; ++i) {
      double x_norm = data[i] / max_theoretical;
      double y_norm = y[i] / max_y;
      double predicted = a * x_norm + b;
      double error = y_norm - predicted;
      sum += error * error;
    }
    
    mse = sum / n;
    
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