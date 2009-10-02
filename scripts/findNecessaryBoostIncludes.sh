#!/bin/bash

#Caveat emptor:
#
#-This script is based on the output generated by gcc when a specific
# header is not found, should the format change at any time in the
# future, this script is rendered useless
#
#-We assume no other includes are lacking than boost includes
#
#-We assume the boost includes are in the form of fully qualified
# includes, and not relative includes
#
#-This script needs to be called multiple times untill no errors are found.

#Notes:
#
#Before starting a series of these scripts, the following command may
#be run in the internal coin boost directory to clean it out:
#
#  find -type f -not -path '*/.svn/*' -delete
#
#To clean up afterwards:
#  svn st | egrep '^!'  | cut -d\  -f2- | xargs svn del
#  svn st | egrep '^\?'  | cut -d\  -f2- | xargs svn add
#
#To check that everything is in order, the following command should return empty:
# svn st | egrep -v '^A' | egrep -v '^D'
#
#Also always remember if you have eg. a system installation of boost,
#you will want to make sure it is not picked up, when you are syncing
#against another boost base.


OS=$(uname)
if [ "${OS}" = "SunOS" ]
then 
  MKDIRHIER="/usr/X11/bin/mkdirhier"
else
  MKDIRHIER="mkdirhierWorkaround"
fi

#Since mkdirhier is not working with absolute paths on cygwin, lets do a workaround
mkdirhierWorkaround() {
    if [ -n $(echo -n $1 | cut -d/ -f1) ]
    then
      (cd / && mkdirhier $(echo -n $1 | cut -d/  -f2-))
    else
        mkdirhier $1
    fi
}

error() {
    echo $@ >/dev/stderr
    exit -1
}

usage() {
    echo -e "Usage is:\n\t $0 <BUILDDIR> <BOOSTDIR>";
}

#If the destination directory doesn't exist, we'll create it.
reallyCopy() {
    if ! cp $1 $2
    then
        ${MKDIRHIER} $(dirname $2)
        cp $1 $2
    fi
}

BASEDIR=$(pwd)
cd $(dirname $0)/..
COINDIR=$(pwd)
cd ${BASEDIR}

if [ -z "$1" ] || [ -z "$2" ]
then
    usage
    exit -1
fi

cd $1 2>/dev/null || error "No such directory: $1"
BUILDDIR=$(pwd)
cd ${BASEDIR}
cd $2 2>/dev/null || error "No such directory: $2"
BOOSTDIR=$(pwd)
cd ${BASEDIR}

if [ -z "${BUILDDIR}" ]
then
    usage
    exit 1
fi

if [ "${OS}" = "SunOS" ]
then 
  DETECTCOMMAND="make 2>&1 | egrep ': Error: Could not open include file' | cut -d: -f3- | cut -d\< -f2- | cut -d\> -f1 | cut -d/ -f2- | sort | uniq"
else
  DETECTCOMMAND="make 2>&1 | egrep ': No such file or directory' | cut -d: -f5 | cut -d/ -f2- | cut -d\'  -f1 | sort | uniq"
fi

CONFIGDIRS="
config
"

#We will always keep the platform configuration files.
for cdir in ${CONFIGDIRS}
do
    oneup=$(dirname ${cdir})
    #name=$(basename ${cdir})
    ${MKDIERHIER} ${COINDIR}/include/boost/${oneup}
    cp -r ${BOOSTDIR}/${cdir} ${COINDIR}/include/boost/${oneup} || error -e "No such file or directory: ${BOOSTDIR}/${cdir}.\nYou need to revise your special includes."
done

cd ${BUILDDIR}
for file in $(eval ${DETECTCOMMAND})
do
    reallyCopy ${BOOSTDIR}/$file ${COINDIR}/include/boost/$file
done
REMAINING=$(eval ${DETECTCOMMAND})
echo "${REMAINING}"
if [ -n "${REMAINING}" ]
then
    exitStatus=$(echo "${REMAINING}" | wc -l)
else
    exitStatus=0
fi
echo ${exitStatus}
exit ${exitStatus}
