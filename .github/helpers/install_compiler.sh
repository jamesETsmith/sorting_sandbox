#!/bin/bash

COMPILER=$1

echo "Trying to install ${COMPILER}"

wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
# Fingerprint: 6084 F3CF 814B 57C1 CF12 EFD5 15CF 4D18 AF4F 7421

if [ "${COMPILER}" = "clang++-10" ]
then
    echo "Nothing to install!"
elif [ "${COMPILER}" = "clang++-11" ]
then
    echo "Using LLVM script to install clang++11"
    VERSION=11
    sudo apt-get install clang-${VERSION} libclang-common-${VERSION}-dev libclang-${VERSION}-dev\
        libc++-${VERSION}-dev libomp-${VERSION}-dev
elif [ "${COMPILER}" = "clang++-13" ]
then
    echo "Using LLVM script to install clang++-13"
    VERSION=13
    sudo apt-get install clang-${VERSION} libclang-common-${VERSION}-dev libclang-${VERSION}-dev\
        libc++-${VERSION}-dev libomp-${VERSION}-dev
elif [ "${COMPILER}" = "g++-10" ]
then
    echo "Nothing to install!"
elif [ "${COMPILER}" = "g++-11" ]
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