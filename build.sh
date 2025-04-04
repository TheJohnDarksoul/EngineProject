#!/bin/sh

rm -rf $PWD/build
mkdir -p $PWD/build
cd $PWD/build
cmake -G Xcode -DBUILD_INSTALL_PREFIX=../install -CMAKE_BUILD_TYPE=Debug ..
cmake --build . --target install --config Debug
cd ..

