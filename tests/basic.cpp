#include <lyrahgames/gnuplot_pipe.hpp>

int main() {
  lyrahgames::gnuplot_pipe plot{};
  plot << "plot sin(x)\n"
       << "replot 0.5*cos(x)\n";
}