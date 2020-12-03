#pragma once
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace lyrahgames {

class gnuplot_pipe {
 public:
  static constexpr char gnuplot_cmd[] = "gnuplot -persist";

  gnuplot_pipe() {
    if (!(pipe_ = popen(gnuplot_cmd, "w")))
      throw std::runtime_error("Could not open Gnuplot pipeline!");
  }
  gnuplot_pipe(gnuplot_pipe&& plot) : pipe_{plot.pipe_} {
    plot.pipe_ = nullptr;
  }
  gnuplot_pipe& operator=(gnuplot_pipe&& plot) {
    std::swap(pipe_, plot.pipe_);
    return *this;
  }
  gnuplot_pipe(const gnuplot_pipe&) = delete;
  gnuplot_pipe& operator=(const gnuplot_pipe&) = delete;
  virtual ~gnuplot_pipe() {
    if (pipe_) pclose(pipe_);
  }

  // friend gnuplot_pipe& operator<<(gnuplot_pipe& plot, const char* cmd) {
  //   fputs(cmd, plot.pipe_);
  //   fflush(plot.pipe_);
  //   return plot;
  // }

  template <typename T>
  friend gnuplot_pipe& operator<<(gnuplot_pipe& plot, const T& t) {
    // Not very efficient but suffices for now.
    std::stringstream input{};
    input << t;
    fputs(input.str().c_str(), plot.pipe_);
    fflush(plot.pipe_);
    return plot;
  }

 private:
  FILE* pipe_{nullptr};
};

}  // namespace lyrahgames