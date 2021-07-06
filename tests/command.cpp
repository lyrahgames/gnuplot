#include <iomanip>
#include <iostream>
//
#include <lyrahgames/gnuplot/command.hpp>

using namespace std;
using namespace lyrahgames;

int main() {
  // No other output should interfere. Hence, a string is first constructed.
  cout << (gnuplot::command() + '\n');
}
