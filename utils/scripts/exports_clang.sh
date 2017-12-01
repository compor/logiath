#!/usr/bin/env bash

export CC=clang 
export CXX=clang++

export LLVMCONFIG=$(which llvm-config)

export GTEST_ROOT=/usr/local/gtest-libcxx

export CXX_FLAGS="-stdlib=libc++"

export LINKER_FLAGS="-Wl,-L$(${LLVMCONFIG} --libdir)" 
export LINKER_FLAGS="${LINKER_FLAGS} -Wl,-rpath=$(${LLVMCONFIG} --libdir)" 
export LINKER_FLAGS="${LINKER_FLAGS} -lc++ -lc++abi" 

export BUILD_TYPE=Debug

export LOGIATH_SKIP_TESTS=OFF
export LOGIATH_DEBUG=ON

