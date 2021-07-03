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
  /// Environment variable used to customize gnuplot command string.
  static constexpr char gnuplot_command_env[] = "GNUPLOT";
  /// Environment variable used to customize gnuplot flags.
  static constexpr char gnuplot_flags_env[] = "GNUPLOT_FLAGS";

  /// Default Gnuplot Command Called When Opening the Pipe
  static constexpr char gnuplot_default_command[] = "gnuplot";
  /// Default Gnuplot Flags Added to Command When Opening Pipe
  static constexpr char gnuplot_default_flags[] = "";

  /// Generates the command string which used to open the pipeline.
  static auto command() -> std::string {
    using std::string;

    // Set gnuplot command.
    const char* gnuplot_cmd = std::getenv(gnuplot_command_env);
    if (!gnuplot_cmd) gnuplot_cmd = gnuplot_default_command;

    // Set gnuplot flags.
    const char* gnuplot_flags = std::getenv(gnuplot_flags_env);
    if (!gnuplot_flags) gnuplot_flags = gnuplot_default_flags;

    // Assemble command and open the pipe.
    auto cmd = string(gnuplot_cmd);
    auto flags = string(gnuplot_flags);
    if (!flags.empty()) cmd += " " + flags;

    return cmd;
  }

  pipe() {
    const auto cmd = command();
    if (!(pipe_ = POPEN(cmd.c_str(), "w")))
      throw std::runtime_error(
          "Failed to open gnuplot pipeline with command '" + cmd + "'!");
    enable_default_style();
  }

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
  /// stringstream to make a formatted string.
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

  /// Sends command to not quit the pipe until its respective plot window has
  /// been closed. This makes the destructor of the pipe a blocking call.
  void wait_for_plot_to_close() {
    fputs("pause mouse close\n", pipe_);
    fflush(pipe_);
  }

 private:
  FILE* pipe_{nullptr};
};

}  // namespace lyrahgames::gnuplot

#undef POPEN
#undef PCLOSE
