#pragma once
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace lyrahgames::gnuplot {

class pipe {
public:
  static constexpr char gnuplot_cmd[] = "gnuplot -persist";

  pipe() {
    if (!(pipe_ = popen(gnuplot_cmd, "w")))
      throw std::runtime_error("Could not open Gnuplot pipeline!");
  }
  pipe(pipe &&plot) : pipe_{plot.pipe_} { plot.pipe_ = nullptr; }
  pipe &operator=(pipe &&plot) {
    std::swap(pipe_, plot.pipe_);
    return *this;
  }
  pipe(const pipe &) = delete;
  pipe &operator=(const pipe &) = delete;
  virtual ~pipe() {
    if (pipe_)
      pclose(pipe_);
  }

  // friend pipe& operator<<(pipe& plot, const char* cmd) {
  //   fputs(cmd, plot.pipe_);
  //   fflush(plot.pipe_);
  //   return plot;
  // }

  template <typename T> friend pipe &operator<<(pipe &plot, const T &t) {
    // Not very efficient but suffices for now.
    std::stringstream input{};
    input << t;
    fputs(input.str().c_str(), plot.pipe_);
    fflush(plot.pipe_);
    return plot;
  }

private:
  FILE *pipe_{nullptr};
};

} // namespace lyrahgames::gnuplot