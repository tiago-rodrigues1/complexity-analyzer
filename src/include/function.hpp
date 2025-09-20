#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <algorithm>
#include <iostream>
#include <limits>
#include <math.h>
#include <numeric>
#include <sstream> 
#include <string>
#include <vector>

class ComplexityFunction {
protected:
  std::string name;
  std::vector<double> data;
  std::string plot_command;
  double mse;

private:
  double compute_mse(const std::vector<double>& x, const std::vector<double>& y) const {
    double sum = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
      double predicted = x[i];
      double error = y[i] - predicted;
      sum += error * error;
    }
    return sum / x.size();
  }

public:
  ComplexityFunction(const std::string& nm) : name(nm) {}
  virtual ~ComplexityFunction() = default;

  virtual double expected_value(double n) = 0;
  virtual void set_command_plot() = 0;

  std::vector<double> get_data() { return data; }
  std::string get_name() const { return name; }
  std::string get_plot_command() { return plot_command; }

  void set_data(const std::vector<long long>& x) {
    data.clear();
    data.reserve(x.size());

    for (const auto& n : x) {
      data.push_back(expected_value(n));
    }

    set_command_plot();
  }

  void set_mse(const std::vector<double>& y) {
    if (y.size() != data.size()) {
      mse = std::numeric_limits<double>::max();
      return;
    }

    if (data.empty()) {
      mse = std::numeric_limits<double>::max();
      return;
    }

    double max_theoretical = *std::max_element(data.begin(), data.end());
    if (max_theoretical == 0) {
      mse = std::numeric_limits<double>::max();
      return;
    }

    mse = compute_mse(data, y);
  }

  double get_mse() const { return mse; }

  const std::vector<double>& get_data() const { return data; }
};

/// Complexity Functions
class Constant : public ComplexityFunction {
public:
  Constant() : ComplexityFunction("O(1)") {}
  double expected_value(double n) override;
};

class Linear : public ComplexityFunction {
public:
  Linear() : ComplexityFunction("O(n)") {};
  double expected_value(double n) override;
  void set_command_plot() override {
    std::stringstream ss;
    ss << "f_n(x) = x /" << data.back();

    plot_command = ss.str();
  }
};

class Logarithmic : public ComplexityFunction {
public:
  Logarithmic() : ComplexityFunction("O(log n)") {}
  double expected_value(double n) override;
  void set_command_plot() override {
    std::stringstream ss;
    ss << "f_log(x) = log(x)/log(2)/" << data.back();

    plot_command = ss.str();
  }
};

class NLogN : public ComplexityFunction {
public:
  NLogN() : ComplexityFunction("O(n log n)") {}
  double expected_value(double n) override;
  void set_command_plot() override {
    std::stringstream ss;
    ss << "f_nlog(x) = x * log(x)/log(2)/" << data.back();

    plot_command = ss.str();
  }
};

class Quadratic : public ComplexityFunction {
public:
  Quadratic() : ComplexityFunction("O(n^2)") {}
  double expected_value(double n) override;
  void set_command_plot() override {
    std::stringstream ss;
    ss << "f_quad(x) = x**2/" << data.back();

    plot_command = ss.str();
  }
};

class Cubic : public ComplexityFunction {
public:
  Cubic() : ComplexityFunction("O(n^3)") {}
  double expected_value(double n) override;
  void set_command_plot() override {
    std::stringstream ss;
    ss << "f_cub(x) = x**3/" << data.back();

    plot_command = ss.str();
  }
};
#endif
