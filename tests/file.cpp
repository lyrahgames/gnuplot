#include <cmath>
#include <fstream>
//
#include <lyrahgames/gnuplot_pipe.hpp>

using namespace std;
using namespace lyrahgames;

int main() {
  std::fstream file{"tmp.dat", std::ios::out};
  const int n = 100;
  for (size_t i = 0; i < n; ++i) {
    const float phi = 2.0 * M_PI * i / (n - 1);
    const float x = cos(phi);
    const float y = sin(2 * phi);
    file << i << '\t' << phi << '\t' << x << '\t' << y << '\n';
  }
  file << flush;

  gnuplot_pipe plot{};
  plot << "plot 'tmp.dat' u 3:4 w l\n";
}