#!/bin/bash

# set -x

BASE_DIR=`pwd`
BUILD_DIR=$BASE_DIR/build

EDK2_DIR=$BASE_DIR/src/edk2
EDK2_CON

echo "[ * ] Building for x86_64 on $(uname -sr)"

# Checking or components
#------------------------------------*
echo -n "[ * ] Check for Git... "
GIT_VERSION=$(git --version | cut -d' ' -f3)
if [[ $? -ne 0 ]]; then
	echo "not present"
	echo "[ ! ] Git is required for installing submodules"
	exit 1
fi
echo $GIT_VERSION

echo -n "[ * ] Check for make... "
MAKE_VERSION=$(make --version | head -n 1 | cut -d' ' -f3)
if [[ $! -ne 0 ]]; then
	echo "not present"
	echo "[ ! ] Make is required for building EDK II"
	exit 1 
fi
echo $MAKE_VERSION

echo -n "[ * ] Check for sed... "
SED_VERSION=$(sed --version | head -n 1 | cut -d' ' -f4)
if [[ $! -ne 0 ]]; then
	echo "not present"
	echo "[ ! ] Sed is not present. src/edk2/Conf/target.txt may need manual configuration. (See https://github.com/tianocore/tianocore.github.io/wiki/Common-instructions#modify-conf-files)"
	read -p "[ ? ] Continue? (N/y) " -n1 -s NO_SED
	if [[ $NO_SED != 'y' ]]; then
	    exit 1
	fi
else
    echo $SED_VERSION
fi


git submodule update --init >/dev/null


# EDK II build
#--------------------------------------------*
echo "[ * ] Building EDK II..."
cd $EDK2_DIR

git submodule update --init >/dev/null
make -C BaseTools 
. edksetup.sh
make -C edk2/BaseTools
export EDK_TOOLS_PATH=$HOME/src/edk2/BaseTools
. edksetup.sh BaseTools
cp src/edk2_config/target.txt
	
# Main build
#--------------------------------------------*
cd $BASE_DIR

[[ -d $BUILD_DIR ]] || mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Cleanup
rm -r $BUILD_DIR
