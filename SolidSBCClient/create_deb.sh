#!/bin/bash

###################
# settings
###################

PACKAGE_DEBUG=1

#will be exported as maintainer
export DEBFULLNAME="mo-sys.de"

#will be exported as author
DEBAUTHOR="moritz.wagner@mo-sys.de"

###################
# end of settings
###################

#############################################################

REVISION="17." #`svn up |  awk '{print $2}'`
REVISION=${REVISION//\./}

PACKAGE_FULLNAME="solidsbcclient-$REVISION"
PACKAGE_DIR="debian/$PACKAGE_FULLNAME"

rm -Rf debian/
mkdir -p $PACKAGE_DIR

if [ $PACKAGE_DEBUG = 1 ]; then
	echo "!!! ================================= !!!"
	echo "!!! WARNING: packaging debug binaries !!!"
	echo "!!! ================================= !!!"
	echo "Are you really sure you want to do this? (y/n)"
	echo ""
	read -n1
    if [ "$REPLY" != "y" ]; then
    	exit 0
    fi
    echo ""
	cp Debug/SolidSBCClient $PACKAGE_DIR/SolidSBCClient
else
	cp Release/SolidSBCClient $PACKAGE_DIR/SolidSBCClient
fi

tar -zcf $PACKAGE_DIR.orig.tar.gz $PACKAGE_DIR
cd $PACKAGE_DIR
dh_make -s -e $DEBAUTHOR
dpkg-buildpackage -b

echo $DESTDIR
cd ..
