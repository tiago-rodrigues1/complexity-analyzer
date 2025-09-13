#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <math.h>
#include <string>
#include <vector>
#include <iostream>

class ComplexityFunction {
protected:
  std::string name;
  std::vector<double> data;
  double max_value = 0;
  double mse;

  public:
  ComplexityFunction(const std::string& nm) : name(nm) {}
  virtual ~ComplexityFunction() = default;
  
  virtual double expected_value(double n) = 0;

  std::string get_name() const {
    return name;
  }

  void set_data(const std::vector<double>& x) {
    for (const auto& n : x) {
      double expected = expected_value(n * 1.0);
      if (expected > max_value) max_value = expected;
      data.push_back(expected);
    }
  }

  void set_mse(const std::vector<double>& y, double max_y) {
    if (y.size() != data.size()) {
      std::cerr << "Invalido\n";
      return;
    }

    double sum = 0;

    for (size_t i = 0; i < data.size(); ++i) {
      double y_norm = y[i] / max_y;
      double data_norm = data[i] / max_value;
      double sqr_diff = pow((y_norm - data_norm), 2);
      sum += sqr_diff;
    }

    mse = sum / data.size();
  }

  double get_mse() {
    return mse;
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
