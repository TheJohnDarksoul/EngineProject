mkdir build
cd build
cmake -G "Visual Studio 17 2022" -DBUILD_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --target install --config Debug
cd ..
