#!/bin/bash
if [ "$(whoami)" != root ]; then
    echo Please run this script as root or using sudo
    exit
fi

rm -rv build
mkdir -p build
cd build || exit
cmake ..
make
make install