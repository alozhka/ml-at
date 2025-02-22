#!/bin/bash

echo "7 and 6 => 20"
../cmake-build-release/timber-cutter input1.txt output1.txt

echo "10 and 3 => 15"
../cmake-build-release/timber-cutter input2.txt output2.txt

echo "9 and 7 => 27"
../cmake-build-release/timber-cutter input3.txt output3.txt

echo "10 and 7 => 29"
../cmake-build-release/timber-cutter input4.txt output4.txt

echo "13 and 10 => 45" # 44
../cmake-build-release/timber-cutter input5.txt output5.txt

echo "100 and 3 => 105"
../cmake-build-release/timber-cutter input6.txt output6.txt

echo "10 and 4 => 18"
../cmake-build-release/timber-cutter input7.txt output7.txt
../cmake-build-release/timber-cutter input8.txt output8.txt
../cmake-build-release/timber-cutter input9.txt output9.txt
../cmake-build-release/timber-cutter input10.txt output10.txt

exit 0