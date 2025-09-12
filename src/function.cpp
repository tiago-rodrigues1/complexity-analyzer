#include <function.hpp>
#include <math.h>       /* log2 */

double Constant::expected_value(double n) { return 1; }
double Linear::expected_value(double n) { return n; }
double Logarithmic::expected_value(double n) { return log2(n); }
double NLogN::expected_value(double n) { return n * log2(n); }
double Quadratic::expected_value(double n) { return pow(n, 2); }
double Cubic::expected_value(double n) { return pow(n, 3); }
