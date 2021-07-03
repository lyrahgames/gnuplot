#include <iomanip>
#include <iostream>
//
#include <lyrahgames/gnuplot/gnuplot.hpp>

using namespace std;
using namespace lyrahgames;

int main() {
  // No other output should interfere. Hence, a string is first constructed.
  cout << ("gnuplot::pipe::command() = \"" + gnuplot::pipe::command() + "\"\n");
}
