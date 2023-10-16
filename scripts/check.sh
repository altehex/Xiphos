#!/bin/bash

# set -x
set -e

source ./variables.sh 

${PRINTF} " Building ${XIPHOS} for x86_64 on $(uname -sr)\n"
${PRINTF} ${PRETTY_LINE}

${PRINTF}     "${NOTIFY_SIGN} Checking for make...           "
if [[ ! -e /usr/bin/make ]]; then
	${PRINTF}     "${NOT_PRESENT}"
	${PRINTF}     "${ERROR_SIGN} Make is required\n"
	exit 1 
fi
${PRINTF} ${VERSION_FMT} $(make --version | head -n 1 | cut -d' ' -f3)
	
${PRINTF}     "${NOTIFY_SIGN} Checking for clang...          "
[[ ! -d $CLANG_PATH ]] && ${PRINTF} "${NOT_PRESENT}" || ${PRINTF} ${VERSION_FMT} $(clang --version | head -n 1 | cut -d' ' -f3)

${PRINTF}     "${NOTIFY_SIGN} Checking for x86_64-elf-gcc... "
if [[ -d $GCC_PATH ]]; then
	${PRINTF} ${VERSION_FMT} $(x86_64-elf-gcc --version | head -n 1 | cut -d' ' -f5)
else
	${PRINTF}     "${NOT_PRESENT}"
	${PRINTF}     "${PROMPT_SIGN} Install GCC cross-compiler?\n"
	${PRINTF}     "*-+--+-( ${YES} )-+-( ${NO_DEFAULT} )-+--+-> "
	read -n 1 INSTALL_GCC
	${PRINTF}        ""
	if [[ $INSTALL_GCC == 'Y' ]] || [[ $INSTALL_GCC == 'y' ]]; then
	   ./install_gcc.sh
	fi
fi
	
if [[ ! -d $CLANG_PATH ]] && [[ ! -e $GCC_PATH ]]; then
    ${PRINTF}     "[ !! ] GCC or Clang are required\n"
	exit 1
fi

${PRINTF}     "${OK_SIGN} OK\n"
${PRINTF}     "${PROMPT_SIGN} Run make?\n"
${PRINTF}     "*-+--+-( ${YES} )-+-( ${NO_DEFAULT} )-+--+-> "
read -n 1 RUN_MAKE
${PRINTF}    ""

[[ $RUN_MAKE == 'y' ]] || [[ $RUN_MAKE == 'Y' ]] && make -C .. all && ${PRINTF} ${PRETTY_LINE}
