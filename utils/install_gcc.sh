#!/bin/bash

# set -x

source ./variables.sh 

CROSSDEV_REPO_DIR=/var/db/repos/crossdev
CROSSDEV_METADATA_DIR=$CROSSDEV_REPO_DIR/metadata
CROSSDEV_PROFILES_DIR=$CROSSDEV_REPO_DIR/profiles
CROSSDEV_REPO_NAME=$CROSSDEV_PROFILES_DIR/repo_name
CROSSDEV_LAYOUT_CONF=$CROSSDEV_METADATA_DIR/layout.conf

CROSSDEV_CONF_DIR=/etc/portage/repos.conf
CROSSDEV_CONF=$CROSSDEV_CONF_DIR/crossdev.conf

CROSSDEV_FLAGS='--stage1 -S --target x86_64-elf --show-fail-log'

gentoo-install()
{
	${PRINTF}    "${NOTIFY_SIGN} Installing for Gentoo.\n"
	if [[ ! -e /usr/bin/crossdev ]]; then
	    ${PRINTF}	"${ERROR_SIGN} This script will install crossdev. Make sure to check the dependencies.\n"
	    ${PRINTF}	${PRETTY_LINE}
	    emerge -av crossdev
	    [[ $? -ne 0 ]] && ${PRINTF} "${NOTIFY_SIGN} Quitting...\n"	 && return
	    ${PRINTF}	${PRETTY_LINE}

	    mkdir -p $CROSSDEV_METADATA_DIR $CROSSDEV_PROFILES_DIR
		
		${ECHO}    "crossdev" > $CROSSDEV_REPO_NAME

		${ECHO}    "masters = gentoo"      > $CROSSDEV_LAYOUT_CONF
		${ECHO}    "thin-manifests = true" > $CROSSDEV_LAYOUT_CONF

	    ${ECHO}	"[crossdev]"                        > $CROSSDEV_CONF
	    ${ECHO}	"location = /var/db/repos/crossdev" > $CROSSDEV_CONF
	    ${ECHO}	"priority = 10"                     > $CROSSDEV_CONF
	    ${ECHO}	"masters = gentoo"                  > $CROSSDEV_CONF
	    ${ECHO}	"auto-sync = no"                    > $CROSSDEV_CONF

		chown -R portage:portage /var/db/repos/crossdev
		
		${PRINTF}    "${OK_SIGN} Installed crossdev.\n"
	fi

	crossdev $CROSSDEV_FLAGS
	${PRINTF}	${PRETTY_LINE}
	[[ $? -eq 0 ]] && ${PRINTF} "${OK_SIGN} Installed x86_64-elf-gcc.\n" && return
	${PRINTF}    "${ERROR_SIGN} Installation failed.\n"
	exit 1
}

${PRINTF}        "${NOTIFY_SIGN} Checking OS... "
${PRINTF}        "${LIGHT_GREEN}%s %s\n${COLOR_END}" $(uname -sr)

if [[ -f /etc/gentoo-release ]]; then
	gentoo-install
else # elif
	${PRINTF}    ""
	# TODO: implement for other distros
fi
