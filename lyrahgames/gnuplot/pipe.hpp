#pragma once
#include <cstdio>
#include <cstdlib>
//
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#define POPEN  _popen
#define PCLOSE _pclose
#else
#define POPEN  popen
#define PCLOSE pclose
#endif

namespace lyrahgames::gnuplot {

class pipe {
 public:
  static constexpr char gnuplot_command_environment[] = "GNUPLOT";
  static constexpr char gnuplot_flags_environment[] = "GNUPLOT_FLAGS";

  static constexpr char gnuplot_default_command[] = "gnuplot";
  static constexpr char gnuplot_default_flags[] = "--persist --slow";

  pipe() {
    // Set gnuplot command.
    const char* gnuplot_command = std::getenv(gnuplot_command_environment);
    if (!gnuplot_command) gnuplot_command = gnuplot_default_command;

    // Set gnuplot flags.
    const char* gnuplot_flags = std::getenv(gnuplot_flags_environment);
    if (!gnuplot_flags) gnuplot_flags = gnuplot_default_flags;

    // Assemble command and open the pipe.
    using std::string;
    auto command = string(gnuplot_command) + " " + gnuplot_flags;
    auto flags = string(gnuplot_flags);
    if (!flags.empty()) command += " " + flags;
    if (!(pipe_ = POPEN(command.c_str(), "w")))
      throw std::runtime_error(
          "Failed to open gnuplot pipeline with command '" + command + "'!");
  }

  virtual ~pipe() noexcept {
    if (pipe_) PCLOSE(pipe_);
  }

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

  template <typename T>
  friend pipe& operator<<(pipe& plot, const T& t) {
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

}  // namespace lyrahgames::gnuplot

#undef POPEN
#undef PCLOSE