//
// Created by dawid on 05.04.2022.
//

#pragma once


namespace mps {

    class ParameterBuilder {
        std::string parameters = "?";

    public:
        ParameterBuilder() = default;

        ~ParameterBuilder() = default;

        ParameterBuilder &add_param(const std::string &key, const std::string &value);

        ParameterBuilder &add_param(const std::string &key, char value);

        ParameterBuilder &add_param(const std::string &key, int value);

        ParameterBuilder &add_param(const std::string &key, long value);

        ParameterBuilder &add_param(const std::string &key, float value);

        ParameterBuilder &add_param(const std::string &key, double value);

        [[nodiscard]] std::string build() const;
    };

} // mps
