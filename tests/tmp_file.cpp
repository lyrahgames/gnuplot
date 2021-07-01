#include <cmath>
#include <fstream>
#include <numbers>
//
#include <lyrahgames/gnuplot/gnuplot.hpp>

using namespace std;
using namespace numbers;
using namespace lyrahgames;

int main() {
  gnuplot::temporary_file file{};
  const int n = 1000;
  for (size_t i = 0; i < n; ++i) {
    const auto phi = 2 * pi * i / (n - 1);
    const auto x = cos(3.1 * phi);
    const auto y = sin(7.2 * phi);
    file << i << '\t' << phi << '\t' << x << '\t' << y << '\n';
  }
  file.flush();

  gnuplot::pipe plot{};
  plot << "plot " << file.path() << " u 3:4 w l title 'data'\n";
}