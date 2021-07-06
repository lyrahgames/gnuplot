#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>

namespace lyrahgames::gnuplot {

/// Environment variable used to customize gnuplot command string.
constexpr char command_env[] = "GNUPLOT";
/// Environment variable used to customize gnuplot flags.
constexpr char flags_env[] = "GNUPLOT_FLAGS";

/// Default Gnuplot Command Called When Opening the Pipe
constexpr char default_command[] = "gnuplot";
/// Default Gnuplot Flags Added to Command When Opening Pipe
constexpr char default_flags[] = "";

/// Generates the command string which is used to open the pipeline.
/// At runtime, the string can be customized by using the environment
/// variables 'GNUPLOT' and 'GNUPLOT_FLAGS'. In this case, the string looks
/// like '$GNUPLOT $GNUPLOT_FLAGS'.
auto command() -> std::string {
  using std::string;

  // Set gnuplot command.
  const char* gnuplot_cmd = std::getenv(command_env);
  if (!gnuplot_cmd) gnuplot_cmd = default_command;

  // Set gnuplot flags.
  const char* gnuplot_flags = std::getenv(flags_env);
  if (!gnuplot_flags) gnuplot_flags = default_flags;

  // Assemble command and open the pipe.
  auto cmd = string(gnuplot_cmd);
  auto flags = string(gnuplot_flags);
  if (!flags.empty()) cmd += " " + flags;

  return cmd;
}

}  // namespace lyrahgames::gnuplot
