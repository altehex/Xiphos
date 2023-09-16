#!/bin/bash

# set -x

BASE_DIR=`pwd`
BUILD_DIR=$BASE_DIR/build

EDK2_DIR=$BASE_DIR/src/edk2
EDK2_CONFIG_DIR=$BASE_DIR/src/edk2_config

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


git submodule update --init


# EDK II build
#--------------------------------------------*
echo "[ * ] Building EDK II..."

cd $EDK2_DIR
make -C BaseTools 
./edksetup.sh
cd ..
make -C edk2/BaseTools
cd $EDK2_DIR
export EDK_TOOLS_PATH=$HOME/src/edk2/BaseTools
./edksetup.sh BaseTools
cp $EDK2_CONFIG_DIR/target.txt $EDK2_DIR/Conf/target.txt

echo "[ * ] Finished building EDK II."

# Main build
#--------------------------------------------*
cd $BASE_DIR

[[ -d $BUILD_DIR ]] || mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Cleanup
rm -r $BUILD_DIR
