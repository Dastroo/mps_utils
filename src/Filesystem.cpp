//
// Created by dawid on 22.04.22.
//

#include "../include/Filesystem.h"
#include <my_utils/OSUtils.h>
#include <stdexcept>
#include <string>

namespace mps::filesystem {

std::string var() {
  if (mutl::is_linux())
    if (mutl::is_elevated())
      return "/var/local/multi-purpose-server/";
    else
      return std::string()
          .append(mutl::get_home_path())
          .append("/.local/share/multi-purpose-server/");
  else
    throw std::invalid_argument("unsupported operating system");
}

std::string usr() {
  if (mutl::is_linux())
    if (mutl::is_elevated())
      return "/usr/local/share/multi-purpose-server/";
    else
      return std::string()
          .append(mutl::get_home_path())
          .append("/.local/share/multi-purpose-server/");
  else
    throw std::invalid_argument("unsupported operating system");
}

std::string config() {
    if (mutl::is_linux())
        if (mutl::is_elevated())
            return "/usr/local/share/multi-purpose-server/config.json";
        else
            return std::string()
                    .append(mutl::get_home_path())
                    .append("/.local/share/multi-purpose-server/config.json");
    else
        throw std::invalid_argument("unsupported operating system");
}

std::string log() {
    if (mutl::is_linux())
        if (mutl::is_elevated())
            return "/var/local/multi-purpose-server/logs/";
        else
            return std::string()
                    .append(mutl::get_home_path())
                    .append("/.local/share/multi-purpose-server/logs/");
    else
        throw std::invalid_argument("unsupported operating system");
}

std::string cert() {
    if (mutl::is_linux())
        if (mutl::is_elevated())
            return "/usr/local/share/multi-purpose-server/cert.pem";
        else
            return std::string()
                    .append(mutl::get_home_path())
                    .append("/.local/share/multi-purpose-server/cert.pem");
    else
        throw std::invalid_argument("unsupported operating system");
}
std::string key() {
    if (mutl::is_linux())
        if (mutl::is_elevated())
            return "/usr/local/share/multi-purpose-server/key.pem";
        else
            return std::string()
                    .append(mutl::get_home_path())
                    .append("/.local/share/multi-purpose-server/key.pem");
    else
        throw std::invalid_argument("unsupported operating system");
}

} // namespace mps::filesystem