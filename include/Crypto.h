//
// Created by dawid on 5/17/22.
//

#pragma once

#include <string>

/// https://github.com/WaterJuice/WjCryptLib/tree/master/lib
namespace crypto {
    std::string UUID();

    std::string sha256(const std::string &string);

    std::string encrypt(const std::string &str, std::string &iv_out, std::string &key_out);

    std::string encrypt(const std::string &str, std::string &iv_out, const std::string &key_);

    std::string encrypt(const std::string &str, const std::string &iv_str, const std::string &key_);

    std::string decrypt(const std::string &cipher, const std::string &iv_str, const std::string &key_);

    void encode_base64(const std::string &decoded, std::string &encoded_out);

    void decode_base64(const std::string &encoded, std::string &decoded_out);
};// namespace crypto