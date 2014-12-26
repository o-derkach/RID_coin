#!/bin/bash
ls cmake &> /dev/null
RES=$?
if [[ $RES != 0 ]]; then
	mkdir cmake
fi
cd cmake
rm -rf *
cmake ..
make
echo -e "\e[1;31mYou can find your binary in $(pwd)"
