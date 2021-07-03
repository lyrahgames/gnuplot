#pragma once
#include <filesystem>
#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

namespace lyrahgames::gnuplot {

class temporary_file {
 public:
  static constexpr const char file_prefix[] = "lyrahgames_gnuplot_tmp_";
  static constexpr const char file_suffix[] = ".txt";

  temporary_file() {
    using namespace std;

    // Generate unique temporary random file.
    // There may be chance of a race condition.
    random_device rng{};
    do {
      filepath = filesystem::temp_directory_path() / file_prefix;
      filepath += to_string(rng()) + file_suffix;
    } while (filesystem::exists(filepath));

    // Open stream to generated filename.
    stream.open(filepath, ios::out);
    if (!stream)
      throw std::runtime_error("Failed to open stream to temporary file '" +
                               filepath.string() + "'.");
  }

  virtual ~temporary_file() noexcept {
    // On Windows, the removal of the file handle is asynchronous and a file
    // cannot be removed if there is an existing file handle to it. Therefore we
    // may not be able to remove the file directly after closing the stream.
    // As a consequence, we check for the removal multiple times until it
    // succeeds by using the nothrow variant of 'filesystem::remove'.
    // Further improvements can be added by using async operations to not block
    // the execution of the program or by using sleep timers to not go into a
    // busy waiting loop. But typically, this procedure is called at the end of
    // the program. Hence, it seems not to be necessary.
    stream.close();
    bool deleted = false;
    std::error_code ec;
    while (!deleted && std::filesystem::exists(filepath))
      deleted = std::filesystem::remove(filepath, ec);
  }

  // Copies are not allowed
  temporary_file(const temporary_file&) = delete;
  temporary_file& operator=(const temporary_file&) = delete;

  // Moves should be possible.
  temporary_file(temporary_file&&) = default;
  temporary_file& operator=(temporary_file&&) = default;

  const auto& path() const { return filepath; }

  void flush() { stream.flush(); }

  template <typename T>
  friend auto operator<<(temporary_file& file, T&& t) -> temporary_file& {
    file.stream << std::forward<T>(t);
    return file;
  }

 private:
  std::filesystem::path filepath{};
  std::fstream stream{};
};

}  // namespace lyrahgames::gnuplot
