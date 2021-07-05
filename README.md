<h1 align="center">
    Lyrahgames' Gnuplot Pipeline Package
</h1>

<p align="center">
    C++ Header-Only Library Implementing a Really Simple Gnuplot Pipeline
</p>

<table align="center">
    <tr>
        <td><img src="docs/images/example_basic.png" width="300"/></td>
        <td><img src="docs/images/example_file.png" width="300"/></td>
    </tr>
</table>

## Development Status

<p align="center">
    <img src="https://img.shields.io/github/languages/top/lyrahgames/gnuplot.svg?style=for-the-badge">
    <img src="https://img.shields.io/github/languages/code-size/lyrahgames/gnuplot.svg?style=for-the-badge">
    <img src="https://img.shields.io/github/repo-size/lyrahgames/gnuplot.svg?style=for-the-badge">
    <a href="COPYING.md">
        <img src="https://img.shields.io/github/license/lyrahgames/gnuplot.svg?style=for-the-badge&color=blue">
    </a>
</p>

<p align="center">
    <a href="https://lyrahgames.github.io/gnuplot">
        <img src="https://img.shields.io/website/https/lyrahgames.github.io/gnuplot.svg?down_message=offline&label=Documentation&style=for-the-badge&up_color=blue&up_message=online">
    </a>
</p>

<b>
<table align="center">
    <tr>
        <td>
            master
        </td>
        <td>
            <a href="https://github.com/lyrahgames/gnuplot">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/gnuplot/master.svg?logo=github&logoColor=white">
            </a>
        </td>    
        <!-- <td>
            <a href="https://circleci.com/gh/lyrahgames/gnuplot/tree/master"><img src="https://circleci.com/gh/lyrahgames/gnuplot/tree/master.svg?style=svg"></a>
        </td> -->
        <!-- <td>
            <a href="https://codecov.io/gh/lyrahgames/gnuplot">
              <img src="https://codecov.io/gh/lyrahgames/gnuplot/branch/master/graph/badge.svg" />
            </a>
        </td> -->
        <td>
            <a href="https://ci.cppget.org/?builds=lyrahgames-gnuplot&pv=&tc=*&cf=&mn=&tg=&rs=*">
                <img src="https://img.shields.io/badge/b|2 ci.cppget.org-Click here!-blue">
            </a>
        </td>
    </tr>
    <!-- <tr>
        <td>
            develop
        </td>
        <td>
            <a href="https://github.com/lyrahgames/gnuplot/tree/develop">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/gnuplot/develop.svg?logo=github&logoColor=white">
            </a>
        </td>    
        <td>
            <a href="https://circleci.com/gh/lyrahgames/gnuplot/tree/develop"><img src="https://circleci.com/gh/lyrahgames/gnuplot/tree/develop.svg?style=svg"></a>
        </td>
        <td>
            <a href="https://codecov.io/gh/lyrahgames/gnuplot">
              <img src="https://codecov.io/gh/lyrahgames/gnuplot/branch/develop/graph/badge.svg" />
            </a>
        </td>
    </tr> -->
    <tr>
        <td>
        </td>
    </tr>
    <tr>
        <td>
            Current
        </td>
        <td>
            <a href="https://github.com/lyrahgames/gnuplot">
                <img src="https://img.shields.io/github/commit-activity/y/lyrahgames/gnuplot.svg?logo=github&logoColor=white">
            </a>
        </td>
        <!-- <td>
            <img src="https://img.shields.io/github/release/lyrahgames/gnuplot.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/release-pre/lyrahgames/gnuplot.svg?label=pre-release&logo=github&logoColor=white">
        </td> -->
        <td>
            <img src="https://img.shields.io/github/tag/lyrahgames/gnuplot.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/tag-date/lyrahgames/gnuplot.svg?label=latest%20tag&logo=github&logoColor=white">
        </td>
        <!-- <td>
            <a href="https://queue.cppget.org/gnuplot">
                <img src="https://img.shields.io/website/https/queue.cppget.org/gnuplot.svg?down_message=empty&down_color=blue&label=b|2%20queue.cppget.org&up_color=orange&up_message=running">
            </a>
        </td> -->
    </tr>
</table>
</b>

## Requirements
<b>
<table>
    <tr>
        <td>Language Standard:</td>
        <td>C++20</td>
    </tr>
    <tr>
        <td>Compiler:</td>
        <td>
            GCC | Clang | MinGW | MSVC
        </td>
    </tr>
    <tr>
        <td>Build System:</td>
        <td>
            <a href="https://build2.org/">build2</a>
        </td>
    </tr>
    <tr>
        <td>Operating System:</td>
        <td>
            Linux | Windows | MacOS
        </td>
    </tr>
    <tr>
        <td>Dependencies:</td>
        <td>
            <a href="http://www.gnuplot.info/">
                gnuplot
            </a>
        </td>
    </tr>
</table>
</b>

## Getting Started

```c++
#include <lyrahgames/gnuplot/gnuplot.hpp>
using namespace lyrahgames;
int main() {
  gnuplot::pipe plot{};
  plot << "plot sin(x)\n"
       << "replot 0.5*cos(x)\n";
}
```

## Usage with build2
Add this repository to the `repositories.manifest` file of your build2 package.

    :
    role: prerequisite
    location: https://github.com/lyrahgames/gnuplot.git

Add the following entry to the `manifest` file with a possible version dependency.

    depends: lyrahgames-gnuplot

Add these entries to your `buildfile`.

    import libs = lyrahgames-gnuplot%lib{lyrahgames-gnuplot}
    exe{your-executable}: {hxx cxx}{**} $libs


## Installation
The standard installation process will only install the header-only library with some additional description, library, and package files.

    bpkg -d build2-packages cc \
      config.install.root=/usr/local \
      config.install.sudo=sudo

Get the latest package release and build it.

    bpkg build https://github.com/lyrahgames/gnuplot.git

Install the built package.

    bpkg install lyrahgames-gnuplot

For uninstalling, do the following.

    bpkg uninstall lyrahgames-gnuplot

If your package uses an explicit `depends: lyrahgames-gnuplot` make sure to initialize this dependency as a system dependency when creating a new configuration.

    bdep init -C @build cc config.cxx=g++ "config.cxx.coptions=-O3" -- "?sys:lyrahgames-gnuplot/*"

## Alternative Usage
To use other build systems or manual compilation, you only have to add the `lyrahgames/gnuplot/` directory to your project and include it in the compilation process.

## Build the Documentation

    b docs/doxygen@../gnuplot-gcc/lyrahgames-gnuplot/docs/doxygen/

## Examples
- [Examples in the API Documentation](https://lyrahgames.github.io/gnuplot/examples.html)

## API
- [API Documentation](https://lyrahgames.github.io/gnuplot/)

## References
- [Gnuplot FAQ: *Calling Gnuplot in a pipe ...*](http://www.gnuplot.info/faq/faq.html#x1-810008.8)
