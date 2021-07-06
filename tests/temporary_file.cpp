#include <cassert>
#include <filesystem>
#include <string>
//
#include <lyrahgames/gnuplot/temporary_file.hpp>

using namespace std;
using namespace lyrahgames;

int main() {
  filesystem::path path;
  {
    gnuplot::temporary_file file{};
    path = file.path();
    assert(filesystem::is_regular_file(path));
    assert(filesystem::equivalent(path.parent_path(),
                                  filesystem::temp_directory_path()));
  }
  assert(!filesystem::exists(path));
}
