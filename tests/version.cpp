#include <iomanip>
#include <iostream>
//
#include <lyrahgames/gnuplot/version.hpp>

using namespace std;

int main() {
  cout << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION_STR"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION_STR << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION_ID"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION_ID << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION_FULL"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION_FULL << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION_MAJOR"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION_MAJOR << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION_MINOR"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION_MINOR << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_VERSION_PATCH"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_VERSION_PATCH << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_PRE_RELEASE"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_PRE_RELEASE << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_SNAPSHOT_SN"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_SNAPSHOT_SN << '\n'
       << left << setw(40) << "LYRAHGAMES_GNUPLOT_SNAPSHOT_ID"
       << " = " << right << setw(40) << LYRAHGAMES_GNUPLOT_SNAPSHOT_ID << '\n';
}
