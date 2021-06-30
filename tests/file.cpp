#include <cmath>
#include <fstream>
#include <numbers>
//
#include <lyrahgames/gnuplot/pipe.hpp>

using namespace std;
using namespace numbers;
using namespace lyrahgames;

int main() {
  fstream file{"tmp.dat", ios::out};
  const int n = 100;
  for (size_t i = 0; i < n; ++i) {
    const auto phi = 2 * pi * i / (n - 1);
    const auto x = cos(phi);
    const auto y = sin(2 * phi);
    file << i << '\t' << phi << '\t' << x << '\t' << y << '\n';
  }
  file << flush;

  gnuplot::pipe plot{};
  plot << "plot 'tmp.dat' u 3:4 w l\n";
}