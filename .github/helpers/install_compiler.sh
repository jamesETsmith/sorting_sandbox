#!/bin/bash

COMPILER=$1

echo "Trying to install ${COMPILER}"

if [ "${COMPILER}" = "clang++10" ]
then
    echo "Nothing to install!"
elif [ "${COMPILER}" = "clang++11" ]
then
    echo "Using LLVM script to install clang++11"
    wget https://apt.llvm.org/llvm.sh
    chmod +x llvm.sh
    sudo ./llvm.sh 11
elif [ "${COMPILER}" = "clang++13" ]
then
    echo "Using LLVM script to install clang++13"
    wget https://apt.llvm.org/llvm.sh
    chmod +x llvm.sh
    sudo ./llvm.sh 13
elif [ "${COMPILER}" = "g++10" ]
then
    echo "Nothing to install!"
elif [ "${COMPILER}" = "g++11" ]
then
    # https://stackoverflow.com/a/67453352/9371695
    sudo apt install build-essential manpages-dev software-properties-common
    sudo add-apt-repository ppa:ubuntu-toolchain-r/test
    sudo apt update && sudo apt install gcc-11 g++-11
else
    echo "Compiler not supported!!"
    echo "See .github/helpers/install_compiler.sh for allowed compilers"
    exit 1
fi