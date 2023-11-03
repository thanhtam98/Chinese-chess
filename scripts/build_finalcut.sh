#!/bin/bash

rm -rf final
rm -rf libfinal
sudo apt-get update -y
sudo apt-get install -y autotools-dev automake autoconf autoconf-archive libtool pkg-config
mkdir libfinal
git clone --depth 1 --branch 0.9.0 https://github.com/gansm/finalcut.git 
cd finalcut
autoreconf --install --force
./configure --prefix=$(realpath ../libfinal)
make -j$(nproc)
sudo make install
sudo chmod -R 777 $(realpath ../libfinal)
mv ../libfinal/include/final ../
rm -rf ../finalcut
cd ..