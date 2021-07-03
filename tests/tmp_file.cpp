#include <cmath>
#include <fstream>
#include <numbers>
//
#include <lyrahgames/gnuplot/gnuplot.hpp>

using namespace std;
using namespace numbers;
using namespace lyrahgames;

int main() {
  string tmp_file_path;
  {
    // Create a temporary file with an undefined name which is destroyed at the
    // end of the program.
    gnuplot::temporary_file file{};

    cout << ("Created temporary file '" + file.path().string() + "'.\n")
         << flush;

    // Output the plotting data to the temporary file.
    const int n = 1000;
    for (size_t i = 0; i < n; ++i) {
      const auto phi = 2 * pi * i / (n - 1);
      const auto x = cos(3.1 * phi);
      const auto y = sin(7.2 * phi);
      file << i << '\t' << phi << '\t' << x << '\t' << y << '\n';
    }
    file.flush();

    {
      // Create a gnuplot pipeline and plot the data.
      gnuplot::pipe plot{};
      plot << "plot '" << file.path().string() << "' u 3:4 w l\n";
    }

    cout << "Closed gnuplot pipeline.\n" << flush;
    tmp_file_path = file.path().string();
  }
  cout << ("Removed temporary file '" + tmp_file_path + "'.\n") << flush;
}
