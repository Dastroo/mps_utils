//
// Created by dawid on 22.04.22.
//

#pragma once


namespace mps {

    class SvrDir {
    public:
        /// read & write directory
        static std::string var();

        /// read only directory
        static std::string usr();
    };

} // mps
