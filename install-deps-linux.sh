#!/bin/bash

echo "This Shell Script will install dependencies for axmol" 
echo -n "Are you continue? (y/n) "
read answer
if echo "$answer" | grep -iq "^y" ;then
    echo "It will take few minutes"
else
    exit
fi

sudo apt-get update

# for vm, libxxf86vm-dev also required
# run 32bit applicatio: needed for lua relase mode as luajit has 32bit version
# https://askubuntu.com/questions/454253/how-to-run-32-bit-app-in-ubuntu-64-bit
sudo dpkg --add-architecture i386
# DEPENDS='libc6:i386 libncurses5:i386 libstdc++6:i386'
 

DEPENDS=' libx11-dev'
DEPENDS=' automake'
DEPENDS=' libtool'
DEPENDS+=' libxmu-dev'
DEPENDS+=' libglu1-mesa-dev'
DEPENDS+=' libgl2ps-dev'
DEPENDS+=' libxi-dev'
DEPENDS+=' libzip-dev'
DEPENDS+=' libpng-dev'
#DEPENDS+=' libcurl4-gnutls-dev'
DEPENDS+=' libfontconfig1-dev'
#DEPENDS+=' libsqlite3-dev'
#DEPENDS+=' libglew-dev'
#DEPENDS+=' libssl-dev'
DEPENDS+=' libgtk-3-dev'
DEPENDS+=' binutils'
DEPENDS+=' libbsd-dev'
DEPENDS+=' libasound2-dev'
DEPENDS+=' libxxf86vm-dev'

sudo apt-get install --allow-unauthenticated --yes $DEPENDS > /dev/null

echo "Installing latest freetype for linux ..."
mkdir buildsrc
cd buildsrc
git clone https://github.com/freetype/freetype.git
cd freetype
git checkout VER-2-12-1
sh autogen.sh
./configure --prefix=/usr --enable-freetype-config --disable-static
sudo make install
cd ..
cd ..
