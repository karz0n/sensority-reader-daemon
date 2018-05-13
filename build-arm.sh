#!/usr/bin/env bash

if [[ -z "${ARM_SDK_PATH}" ]]; then
    echo "Path to ARM SDK not set" 1>&2
    exit 1;
fi

cmake -E echo "======================================"
cmake -E echo "              Prepare                 "
cmake -E echo "======================================"

cmake -E remove_directory build
cmake -E make_directory build
cmake -E chdir build \
    cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/arm-toolchain.cmake \
          -DCMAKE_BUILD_TYPE=${BUILD_TYPE:-Release} \
          ..

cmake -E echo "======================================"
cmake -E echo "               Build                  "
cmake -E echo "======================================"

cmake -E time \
    cmake --build build \
          --config ${BUILD_TYPE:-Release}

