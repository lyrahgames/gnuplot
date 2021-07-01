#include <chrono>
#include <cmath>
#include <thread>
//
#include <lyrahgames/gnuplot/gnuplot.hpp>

using namespace std;
using namespace chrono_literals;
using namespace lyrahgames;

int main() {
  float a = 1;
  gnuplot::pipe plot{};
  for (size_t i = 0; i < 100; ++i) {
    plot << "plot sin(" << sin(a) << "*x)\n";
    a += 0.1;
    this_thread::sleep_for(50ms);
  }
}