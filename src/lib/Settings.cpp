#include "../include/Settings.hpp"

#include <fstream>
#include <iostream>

Settings settings;

static inline std::string trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t\r\n");
  size_t end = s.find_last_not_of(" \t\r\n");
  return (start == std::string::npos || end == std::string::npos)
             ? std::string()
             : s.substr(start, end - start + 1);
}

Settings::Settings() { std::fill(std::begin(keys), std::end(keys), false); }

bool Settings::loadFromFile(const std::string &path) {
  std::ifstream in(path);
  if (!in.is_open()) {
    std::cerr << "Settings: cannot open file '" << path
              << "', using defaults\n";
    return false;
  }

  std::string line;
  while (std::getline(in, line)) {
    line = trim(line);
    if (line.empty() || line[0] == '#')
      continue;

    auto pos = line.find('=');
    if (pos == std::string::npos)
      continue;

    std::string key = trim(line.substr(0, pos));
    std::string value = trim(line.substr(pos + 1));

    // Unfortunately, C++ can't use switch on strings...
    if (key == "cameraSpeed") {
      cameraSpeed = std::stof(value);
    } else if (key == "mouseSensitivity") {
      mouseSensitivity = std::stof(value);
    }
  }

  return true;
}
