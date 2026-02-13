#!/bin/bash
cd ../build_conan
mkdir Release
mkdir Debug
cd Release
conan install .. -pr=release --build=missing
cd ..
conan install .. -pr=debug --build=missing