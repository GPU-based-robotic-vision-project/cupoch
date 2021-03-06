#pragma once

#include <string>
#include <vector>

namespace cupoch {
namespace utility {
namespace filesystem {

std::string GetFileExtensionInLowerCase(const std::string &filename);

std::string GetFileNameWithoutExtension(const std::string &filename);

std::string GetFileNameWithoutDirectory(const std::string &filename);

std::string GetFileParentDirectory(const std::string &filename);

std::string GetWorkingDirectory();

bool ChangeWorkingDirectory(const std::string &directory);

// wrapper for fopen that enables unicode paths on Windows
FILE *FOpen(const std::string &filename, const std::string &mode);

}  // namespace filesystem
}  // namespace utility
}  // namespace cupoch