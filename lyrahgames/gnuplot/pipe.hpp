#pragma once
#include <cstdio>
#include <cstdlib>
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
//
#include <lyrahgames/gnuplot/command.hpp>

#ifdef _WIN32
#define POPEN  _popen
#define PCLOSE _pclose
#else
#define POPEN  popen
#define PCLOSE pclose
#endif

namespace lyrahgames::gnuplot {

/// \class pipe pipe.hpp lyrahgames/gnuplot/pipe.hpp
/// Class that describes a handle to a Gnuplot pipeline. It can be used to open,
/// close, and send commands to Gnuplot directly inside the C++ sources.
///
/// \par Basic Example:
/// \include basic.cpp
/// \image html example_basic.png
///
/// \par Animation Example:
/// \include animation.cpp
///
/// \example basic.cpp \image html example_basic.png
/// \example animation.cpp
class pipe {
 public:
  /// Opens a pipeline to Gnuplot by calling the command given by command() and
  /// throws an std::runtime_error if it has not succeeded. After that a default
  /// style for plots is set.
  pipe() {
    const auto cmd = command();
    if (!(pipe_ = POPEN(cmd.c_str(), "w")))
      throw std::runtime_error(
          "Failed to open gnuplot pipeline with command '" + cmd + "'!");
    enable_default_style();
  }

  /// Waits for the plotting window to be closed and destroys the pipeline
  /// afterwards.
  virtual ~pipe() noexcept {
    if (!pipe_) return;
    wait_for_plot_to_close();
    PCLOSE(pipe_);
  }

  // The pipe is movable.
  pipe(pipe&& plot) : pipe_{plot.pipe_} { plot.pipe_ = nullptr; }
  pipe& operator=(pipe&& plot) {
    std::swap(pipe_, plot.pipe_);
    return *this;
  }

  // The pipe should not be copyable.
  pipe(const pipe&) = delete;
  pipe& operator=(const pipe&) = delete;

  // friend pipe& operator<<(pipe& plot, const char* cmd) {
  //   fputs(cmd, plot.pipe_);
  //   fflush(plot.pipe_);
  //   return plot;
  // }

  /// Takes any possible input and writes it into the pipe by using intermediary
  /// std::stringstream to make a formatted string.
  template <typename T>
  friend pipe& operator<<(pipe& plot, T&& t) {
    // Not very efficient but suffices for now.
    std::stringstream input{};
    input << std::forward<T>(t);
    fputs(input.str().c_str(), plot.pipe_);
    fflush(plot.pipe_);
    return plot;
  }

 private:
  /// Sets some defaults to enable a good style for plots.
  void enable_default_style() {
    fputs(
        "set object 1 rect from graph 0,graph 0 to graph 1,graph 1 fc rgb "
        "'#f6f6f6' fs solid 1.0 noborder behind\n"
        "set grid lt 1 lw 3 lc rgb '#fafafa'\n"
        "set key spacing 2 box opaque\n"
        "set style line 1 lt rgb 'black' lw 3 pt 13\n",
        pipe_);
    fflush(pipe_);
  }

  /// Sends command to not quit the pipe until
  /// its respective plot window has been closed.
  /// This makes the destructor of the pipe a blocking call.
  void wait_for_plot_to_close() {
    fputs("pause mouse close\n", pipe_);
    fflush(pipe_);
  }

 private:
  /// Handle for Pipeline
  FILE* pipe_{nullptr};
};

}  // namespace lyrahgames::gnuplot

#undef POPEN
#undef PCLOSE
