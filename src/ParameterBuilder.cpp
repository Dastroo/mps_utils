//
// Created by dawid on 05.04.2022.
//

#include <string>
#include <sstream>
#include "../include/ParameterBuilder.h"

namespace mps {

    ParameterBuilder &ParameterBuilder::add_param(const std::string &key, const std::string &value) {
        std::ostringstream oss;
        oss << '&' << key << '=' << value;
        parameters.append(oss.str());

        return *this;
    }

    ParameterBuilder &ParameterBuilder::add_param(const std::string &key, char value) {
        std::ostringstream oss;
        oss << '&' << key << '=' << value;
        parameters.append(oss.str());

        return *this;
    }

    ParameterBuilder &ParameterBuilder::add_param(const std::string &key, int value) {
        std::ostringstream oss;
        oss << '&' << key << '=' << value;
        parameters.append(oss.str());

        return *this;
    }

    ParameterBuilder &ParameterBuilder::add_param(const std::string &key, long value) {
        std::ostringstream oss;
        oss << '&' << key << '=' << value;
        parameters.append(oss.str());

        return *this;
    }

    ParameterBuilder &ParameterBuilder::add_param(const std::string &key, float value) {
        std::ostringstream oss;
        oss << '&' << key << '=' << value;
        parameters.append(oss.str());

        return *this;
    }

    ParameterBuilder &ParameterBuilder::add_param(const std::string &key, double value) {
        std::ostringstream oss;
        oss << '&' << key << '=' << value;
        parameters.append(oss.str());

        return *this;
    }

    std::string ParameterBuilder::build() const {
        return parameters;
    }

} // mps