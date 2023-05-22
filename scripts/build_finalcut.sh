#!/bin/bash

rm -rf final
rm -rf libfinal
sudo apt-get update -y
sudo apt-get install -y autotools-dev automake autoconf autoconf-archive libtool pkg-config
mkdir libfinal
git clone https://github.com/gansm/finalcut.git
cd finalcut
autoreconf --install --force
./configure --prefix=$(realpath ../libfinal)
make
sudo make install
mv ../libfinal/include/final ../
rm -rf ../finalcut
cd ..