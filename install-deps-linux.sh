#!/bin/bash

echo "This script will install dependencies for cocos" 
echo -n "Continue? (y/n) "
read answer
if echo "$answer" | grep -iq "^y" ;then
    echo "Start ..."
else
    exit
fi

sudo apt-get update

DEPENDS=''

# common
DEPENDS+=' libzip-dev'
DEPENDS+=' libpng-dev'
DEPENDS+=' libbsd-dev'
DEPENDS+=' libxxf86vm-dev'

# glfw
DEPENDS+=' libx11-dev'
DEPENDS+=' libxrandr-dev'
DEPENDS+=' libxinerama-dev'
DEPENDS+=' libxcursor-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' libxext-dev'
DEPENDS+=' libxmu-dev'

# openal
DEPENDS+=' libasound2-dev'

# cocos UIEditBox
DEPENDS+=' libgtk-3-dev'
# cocos Device
DEPENDS+=' libfontconfig1-dev'

# DEPENDS+=' automake'
# DEPENDS+=' binutils'
# DEPENDS+=' libtool'
# DEPENDS+=' libglu1-mesa-dev'
# DEPENDS+=' libgl2ps-dev'
# DEPENDS+=' libsqlite3-dev'
# DEPENDS+=' libssl-dev'

sudo apt-get install --allow-unauthenticated --yes $DEPENDS
