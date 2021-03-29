#!/bin/bash
BuildDir="build"

cd /CppND-Capstone/
clang-format src/file_parser.* -i
clang-format src/option_portfolio.* -i
clang-format src/pricing.* -i
if [ ! -d "$BuildDir" ]; then
mkdir $BuildDir
else
rm -rf build
mkdir $BuildDir
fi
cd $BuildDir

# build project
cmake ..
make

# run the program created
./OptionsData

