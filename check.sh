#!/bin/bash

# set -x

echo "[ * ] Building ThanatOS for x86_64 on $(uname -sr)"

# Checking or components
#------------------------------------*

echo -n "[ * ] Checking for make... "
if [[ ! -e /usr/bin/make ]]; then
	echo "not present"
	echo "[ ! ] Make is required"
	exit 1 
fi
echo $(make --version | head -n 1 | cut -d' ' -f3)

echo -n "[ * ] Checking for gcc... "
[[ ! -e /usr/bin/gcc ]]   && echo "not present" || echo $(gcc --version | head -n 1 | cut -d' ' -f6)
	
echo -n "[ * ] Checking for clang... "
[[ ! -d /usr/lib/clang ]] && echo "not present" || echo $(clang --version | head -n 1 | cut -d' ' -f3)

if [[ ! -d /usr/lib/clang ]] && [[ ! -e /usr/bin/gcc ]]; then
    echo "[ ! ] GCC or Clang are required"
	exit 1
fi

echo "[ * ] OK"
read -p "[ ? ] Run make? (y/n) " -n 1 RUN_MAKE

[[ $RUN_MAKE == 'y' ]] || [[ $RUN_MAKE == 'Y' ]] && make all
