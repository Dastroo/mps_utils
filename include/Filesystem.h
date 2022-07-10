//
// Created by dawid on 22.04.22.
//

#pragma once

#include <string>

namespace mps::filesystem {

    /// read & write directory path
    std::string var();

    /// read only directory path
    std::string usr();

    /// config file path
    std::string config();

    /// destination for all logger files
    std::string log();

    /// CA cert file path (cert.pem)
    std::string cert();

    /// key file path (key.pem)
    std::string key();

}// namespace mps::filesystem
