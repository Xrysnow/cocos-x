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
DEPENDS+=' libpng-dev'
DEPENDS+=' libxxf86vm-dev'

# glfw
DEPENDS+=' libx11-dev'
DEPENDS+=' libxrandr-dev'
DEPENDS+=' libxinerama-dev'
DEPENDS+=' libxcursor-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' libxext-dev'

# openal
DEPENDS+=' libasound2-dev'
DEPENDS+=' libpulse-dev'

# cocos UIEditBox
DEPENDS+=' libgtk-3-dev'
# cocos Device
DEPENDS+=' libfontconfig1-dev'

sudo apt-get install --yes $DEPENDS
