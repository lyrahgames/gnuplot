#pragma once
#include <filesystem>
#include <fstream>
#include <random>
#include <stdexcept>
#include <string>

namespace lyrahgames::gnuplot {

/// \class temporary_file temporary_file.hpp lyrahgames/gnuplot/temporary_file.hpp
/// This class describes a handle to a
/// file which was temporarily created
/// with an undefined name to transmit data
/// to the Gnuplot pipeline.
///
/// \par Example:
/// \include tmp_file.cpp
///
/// \example tmp_file.cpp
class temporary_file {
 public:
  /// Prefix of all generated temporary file names.
  static constexpr const char file_prefix[] = "lyrahgames_gnuplot_tmp_";
  /// Suffix of all generated temporary file names.
  static constexpr const char file_suffix[] = ".txt";

  /// Creates a new unique file inside the directory
  /// given by std::filesystem::temp_directory_path()
  /// with a prefix given by file_prefix,
  /// a suffix given by file_suffix, and an undefined middle part.
  /// The file is created and directly opened for writing by an std::fstream.
  ///
  /// Generating a random file name and creating and opening it afterwards,
  /// is not an atomic operation.
  /// Therefore the method used may result in inconsistent access
  /// when multiple processes from different applications using this library
  /// would like to create temporary files.
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

  /// Closes the file stream and deletes the generated
  /// temporary file if it still exists.
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

  /// Returns the path of the temporary file.
  auto path() const -> const std::filesystem::path& { return filepath; }

  /// Flushes the content of the file stream into the temporary file.
  void flush() { stream.flush(); }

  /// Transmits formatted data to the file stream
  /// by perfect forwarding the argument using the stream operator.
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
