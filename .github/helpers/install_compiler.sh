#!/bin/bash

COMPILER=$1

echo "Trying to install ${COMPILER}"

install_llvm () {
    wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
    # Fingerprint: 6084 F3CF 814B 57C1 CF12 EFD5 15CF 4D18 AF4F 7421

    VERSION=$1
    # From: https://llvm.discourse.group/t/installing-llvm-releases-via-apt-get-unable-to-locate-package/2776/2
    sudo apt-add-repository "deb http://apt.llvm.org/focal/ llvm-toolchain-focal-${VERSION} main"

    sudo apt-get install libllvm-${VERSION}-ocaml-dev libllvm${VERSION} llvm-${VERSION} llvm-${VERSION}-dev llvm-${VERSION}-doc llvm-${VERSION}-examples llvm-${VERSION}-runtime
    sudo apt-get install clang-${VERSION} clang-tools-${VERSION} clang-${VERSION}-doc libclang-common-${VERSION}-dev libclang-${VERSION}-dev libclang1-${VERSION} clang-format-${VERSION} python-clang-${VERSION} clangd-${VERSION}
    sudo apt-get install libfuzzer-${VERSION}-dev
    sudo apt-get install lldb-${VERSION}
    sudo apt-get install lld-${VERSION}
    sudo apt-get install libc++-${VERSION}-dev libc++abi-${VERSION}-dev
    sudo apt-get install libomp-${VERSION}-dev
    sudo apt-get install libclc-${VERSION}-dev
    sudo apt-get install libunwind-${VERSION}-dev
}


if [ "${COMPILER}" = "clang++-10" ]
then
    echo "Nothing to install!"
# elif [ "${COMPILER}" = "clang++-12" ]
# then
#     echo "Using LLVM script to install clang++12"
#     install_llvm "12"
# elif [ "${COMPILER}" = "clang++-13" ]
# then
#     echo "Using LLVM script to install clang++-13"
#     install_llvm "13"
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