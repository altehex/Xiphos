#!/bin/bash

# set -x

echo "[ * ] Building ThanatOS for x86_64 on $(uname -sr)"

# Checking or components
#------------------------------------*

echo -n "[ * ] Check for make... "
MAKE_VERSION=$(make --version | head -n 1 | cut -d' ' -f3)
if [[ $! -ne 0 ]]; then
	echo "not present"
	echo "[ ! ] Make is required for building ThanatOS"
	exit 1 
fi
echo $MAKE_VERSION


# Main build
#--------------------------------------------*

make all

echo "[ * ] Finished building ThanatOS"
echo "[ @ ] You can clean the directory by invoking './build.sh clean'"

