# Really Simple Gnuplot Pipeline for C++

Really Simple C++ Single Header-Only Library for Gnuplot Pipelines.
It is based on the [build2](https://build2.org/) build system.

![](https://img.shields.io/github/languages/top/lyrahgames/gnuplot-pipe.svg?style=for-the-badge)
![](https://img.shields.io/github/languages/code-size/lyrahgames/gnuplot-pipe.svg?style=for-the-badge)
![](https://img.shields.io/github/repo-size/lyrahgames/gnuplot-pipe.svg?style=for-the-badge)
![](https://img.shields.io/github/license/lyrahgames/gnuplot-pipe.svg?style=for-the-badge&color=blue)

<table>
    <tr>
        <td>
            <strong>master</strong>
        </td>
        <td>
            <a href="https://github.com/lyrahgames/gnuplot-pipe">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/gnuplot-pipe/master.svg?logo=github&logoColor=white">
            </a>
        </td>    
        <!-- <td>
            <a href="https://circleci.com/gh/lyrahgames/gnuplot-pipe/tree/master"><img src="https://circleci.com/gh/lyrahgames/gnuplot-pipe/tree/master.svg?style=svg"></a>
        </td>
        <td>
            <a href="https://codecov.io/gh/lyrahgames/gnuplot-pipe">
              <img src="https://codecov.io/gh/lyrahgames/gnuplot-pipe/branch/master/graph/badge.svg" />
            </a>
        </td> -->
    </tr>
    <!-- <tr>
        <td>
            develop
        </td>
        <td>
            <a href="https://github.com/lyrahgames/gnuplot-pipe/tree/develop">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/gnuplot-pipe/develop.svg?logo=github&logoColor=white">
            </a>
        </td>    
        <td>
            <a href="https://circleci.com/gh/lyrahgames/gnuplot-pipe/tree/develop"><img src="https://circleci.com/gh/lyrahgames/gnuplot-pipe/tree/develop.svg?style=svg"></a>
        </td>
        <td>
            <a href="https://codecov.io/gh/lyrahgames/gnuplot-pipe">
              <img src="https://codecov.io/gh/lyrahgames/gnuplot-pipe/branch/develop/graph/badge.svg" />
            </a>
        </td>
    </tr> -->
    <tr>
        <td>
        </td>
    </tr>
    <tr>
        <td>
            <strong>Current</strong>
        </td>
        <td>
            <a href="https://github.com/lyrahgames/gnuplot-pipe">
                <img src="https://img.shields.io/github/commit-activity/y/lyrahgames/gnuplot-pipe.svg?logo=github&logoColor=white">
            </a>
        </td>
        <!-- <td>
            <img src="https://img.shields.io/github/release/lyrahgames/gnuplot-pipe.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/release-pre/lyrahgames/gnuplot-pipe.svg?label=pre-release&logo=github&logoColor=white">
        </td> -->
        <td>
            <img src="https://img.shields.io/github/tag/lyrahgames/gnuplot-pipe.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/tag-date/lyrahgames/gnuplot-pipe.svg?label=latest%20tag&logo=github&logoColor=white">
        </td>
    </tr>
</table>

## Author
- Markus Pawellek "lyrahgames" (lyrahgames@mailbox.org)

## Requirements
- C++17
- Linux
- [build2](https://build2.org/) (or some manual work for other build systems)
- [gnuplot](http://www.gnuplot.info/)

## Tested Platforms
- Operating System: Linux
- Compiler: GCC | Clang
- Build System: [build2](https://build2.org/)

## Usage with build2
Add this repository to the `repositories.manifest` file of your build2 package.

    :
    role: prerequisite
    location: https://github.com/lyrahgames/gnuplot-pipe.git

Add the following entry to the `manifest` file with a possible version dependency.

    depends: lyrahgames-gnuplot-pipe

Add these entries to your `buildfile`.

    import libs = lyrahgames-gnuplot-pipe%lib{lyrahgames-gnuplot-pipe}
    exe{your-executable}: {hxx cxx}{**} $libs


## Installation
The standard installation process will only install the header-only library with some additional description, library, and package files.

    bpkg -d build2-packages cc \
      config.install.root=/usr/local \
      config.install.sudo=sudo

Get the latest package release and build it.

    bpkg build https://github.com/lyrahgames/gnuplot-pipe.git

Install the built package.

    bpkg install lyrahgames-gnuplot-pipe

For uninstalling, do the following.

    bpkg uninstall lyrahgames-gnuplot-pipe

If your package uses an explicit `depends: lyrahgames-gnuplot-pipe` make sure to initialize this dependency as a system dependency when creating a new configuration.

    bdep init -C @build cc config.cxx=g++ "config.cxx.coptions=-O3" -- "?sys:lyrahgames-gnuplot-pipe/*"

## Alternative Usage
To use other build systems or manual compilation, you only have to add the `lyrahgames/gnuplot_pipe.hpp` file to your project and include it in the compilation process.

## Example
All given examples are provided in the `tests` folder and can be compiled and executed by cloning the repository and running build2 in the root folder.

### Basic
```c++
#include <lyrahgames/gnuplot_pipe.hpp>

int main() {
  lyrahgames::gnuplot_pipe plot{};
  plot << "plot sin(x)\n"
       << "replot 0.5*cos(x)\n";
}
```
![Basic Example Output](docs/images/example_basic.png)

### Advanced Usage with File IO
```c++
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
```
![File Example Output](docs/images/example_file.png)

### Advanced Usage with Animations
```c++
#include <chrono>
#include <cmath>
#include <thread>
//
#include <lyrahgames/gnuplot_pipe.hpp>

using namespace std;
using namespace chrono_literals;
using namespace lyrahgames;

int main() {
  float a = 1;
  gnuplot_pipe plot{};

  for (size_t i = 0; i < 100; ++i) {
    plot << "plot sin(" << std::sin(a) << "*x)\n";
    a += 0.1;
    this_thread::sleep_for(50ms);
  }
}
```

## API
### Gnuplot Pipeline Constructor
```c++
lyrahgames::gnuplot_pipe::gnuplot_pipe();
```
Opens a Linux pipe to a new gnuplot process.
### Gnuplot Pipeline Destructor
```c++
virtual lyrahgames::gnuplot_pipe::~gnuplot_pipe();
```
Automatically closes and destroys the opened Linux pipe by using RAII principle.
### Gnuplot Pipeline Stream Operator
```c++
namespace lyrahgames {
template <typename T>
gnuplot_pipe& operator<<(gnuplot_pipe& plot, const T& t);
} // namespace lyrahgames
```
Given variable reference `t` of type `T` will be transformed into a string by using the standard stream operator `operator<<` and then send to the gnuplot process for further processing.

