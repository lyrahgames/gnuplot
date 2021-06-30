#include <lyrahgames/gnuplot/pipe.hpp>

using namespace lyrahgames;

int main() {
  gnuplot::pipe plot{};
  plot << "plot sin(x)\n"
       << "replot 0.5*cos(x)\n";
}