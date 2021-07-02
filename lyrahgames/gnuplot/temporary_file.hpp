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
    stream.close();
    std::filesystem::remove(filepath);
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
