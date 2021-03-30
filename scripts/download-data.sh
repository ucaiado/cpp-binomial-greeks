#!/bin/bash

pushd .
cd ../CppND-Capstone/data
[ -e *.csv ] && rm *.csv
[ -e *.zip ] && rm *.zip
wget -q https://www.dropbox.com/s/a23cezde4494gdy/cppnd_capstone_data.zip
unzip cppnd_capstone_data.zip
rm cppnd_capstone_data.zip
mv data/*.csv .
rm -r data/
popd
