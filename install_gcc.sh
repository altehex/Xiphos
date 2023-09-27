#!/bin/bash

# set -x

CROSSDEV_METADATA_DIR=/var/db/repos/crossdev/metadata
CROSSDEV_LAYOUT_CONF=$CROSSDEV_METADATA_DIR/layout.conf
CROSSDEV_CONF_DIR=/etc/portage/repos.conf
CROSSDEV_CONF=$CROSSDEV_CONF_DIR/crossdev.conf

CROSSDEV_FLAGS='--stage1 -S --target x86_64-elf --show-fail-log'

gentoo-install()
{
	echo    "[ ** ] Installing for Gentoo."
	if [[ ! -e /usr/bin/crossdev ]]; then
	    echo	"[ !! ] This script will install crossdev. Make sure to"
	    echo	"		check the dependencies."
	    echo	"*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--*"
	    emerge -av crossdev
	    [[ $? -ne 0 ]] && echo "[ ** ] Quitting..."	 && return
	    echo	"*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--*"
	    echo	"[ ** ] Installed crossdev."

	    mkdir -p $CROSSDEV_METADATA_DIR
	    touch $CROSSDEV_LAYOUT_CONF
		echo    "masters = gentoo"      >> $CROSSDEV_LAYOUT_CONF
		echo    "thin-manifests = true" >> $CROSSDEV_LAYOUT_CONF

	    touch $CROSSDEV_CONF
	    echo	"[crossdev]"                        >> $CROSSDEV_CONF
	    echo	"location = /var/db/repos/crossdev" >> $CROSSDEV_CONF
	    echo	"priority = 10"                     >> $CROSSDEV_CONF
	    echo	"masters = gentoo"                  >> $CROSSDEV_CONF
	    echo	"auto-sync = no"                    >> $CROSSDEV_CONF

		echo    "[ :) ] Installed crossdev."
	fi

	echo	"*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--*"
	crossdev $CROSSDEV_FLAGS
	echo	"*-+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--*"
	[[ $? -eq 0 ]] && echo "[ :) ] Installed x86_64-elf-gcc." && return
	echo    "[ !! ] Installation failed."
	exit 1
}

echo -n     "[ ** ] Checking OS... "
echo        $(uname -sr)

if [[ -f /etc/gentoo-release ]]; then
	gentoo-install
else # elif
	echo    ""
	# TODO: implement for other distros
fi
