#include <iostream>
#include <string>
//
#include <lyrahgames/gnuplot/pipe.hpp>

using namespace std;
using namespace lyrahgames;

int main(int argc, char* argv[]) {
  if ((argc == 2) && (string(argv[1]) == "--mock")) {
    string line;
    while (getline(cin, line))
      cout << line << '\n';
    return 0;
  }

  gnuplot::pipe plot{};
  plot << "plot sin(x)\n"
       << "replot 0.5*cos(x)\n";
}
