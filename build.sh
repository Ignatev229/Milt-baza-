#! /bin/env bash

mkdir -p ./build
cd ./build || exit 1

qmake ../

make -j"$(nproc)"

compiledb make -j"$(nproc)"

