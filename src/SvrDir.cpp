//
// Created by dawid on 22.04.22.
//

#include <string>
#include <stdexcept>
#include <my_utils/OSUtils.h>
#include "../include/SvrDir.h"

namespace mps {

    std::string SvrDir::var() {
        if (mutl::is_linux())
            if (mutl::is_elevated())
                return "/var/local/multi-purpose-server/";
            else
                return std::string().append(mutl::get_home_path()).append("/.local/share/multi-purpose-server/");
        else
            throw std::invalid_argument("unsupported operating system");
    }

    std::string SvrDir::usr() {
        if (mutl::is_linux())
            if (mutl::is_elevated())
                return "/usr/local/share/multi-purpose-server/";
            else
                return std::string().append(mutl::get_home_path()).append("/.local/share/multi-purpose-server/");
        else
            throw std::invalid_argument("unsupported operating system");
    }

} // mps