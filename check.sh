#!/bin/bash

# set -x

CLANG_PATH=/usr/lib/clang
GCC_PATH=/usr/lib/gcc/x86_64-elf

echo " Building ThanatOS for x86_64 on $(uname -sr)"
echo "*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--*"

echo -n     "[ ** ] Checking for make...           "
if [[ ! -e /usr/bin/make ]]; then
	echo    "not present"
	echo    "[ !! ] Make is required"
	exit 1 
fi
echo $(make --version | head -n 1 | cut -d' ' -f3)
	
echo -n     "[ ** ] Checking for clang...          "
[[ ! -d $CLANG_PATH ]] && echo "not present" || echo $(clang --version | head -n 1 | cut -d' ' -f3)

echo -n     "[ ** ] Checking for x86_64-elf-gcc... "
if [[ -d $GCC_PATH ]]; then
	echo $(x86_64-elf-gcc --version | head -n 1 | cut -d' ' -f5)
else
	echo    "not present"
	echo    "[ ?? ] Install GCC cross-compiler?"
	read -p "*-+--+-( [y] Yes )-+-( [N] No )-+--+-> " -n 1 INSTALL_GCC
	echo    ""
	if [[ $INSTALL_GCC == 'Y' ]] || [[ $INSTALL_GCC == 'y' ]]; then
	   ./install_gcc.sh
	fi
fi
	
if [[ ! -d $CLANG_PATH ]] && [[ ! -e $GCC_PATH ]]; then
    echo    "[ !! ] GCC or Clang are required"
	exit 1
fi

echo    "[ :) ] OK"
echo    "[ ?? ] Run make? "
read -p "*-+--+-( [y] Yes )-+-( [N] No )-+--+-> " -n 1 RUN_MAKE

[[ $RUN_MAKE == 'y' ]] || [[ $RUN_MAKE == 'Y' ]] && make all
