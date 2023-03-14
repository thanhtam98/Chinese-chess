# Chinese chess

## Todo
- [x] Write code for IBoard and IChessman
- [x] Write newInstance for IChessman and implementations for every chessman
- [x] Design move chessman mechanism
- [ ] Design the User Interface (Ref: https://github.com/gansm/finalcut/blob/main/doc/first-steps.md#first-steps-with-the-final-cut-widget-toolkit)
- [ ] Refactor behaviorProviders [Optional] 
- [ ] Refactor pieces to optimize memory usage [Optional]


## How to install final cut lib to project
```
sudo apt-get update
sudo apt-get install autotools-dev automake autoconf autoconf-archive libtool pkg-config
mkdir libfinal
git clone https://github.com/gansm/finalcut.git
cd finalcut
autoreconf --install --force
./configure --prefix=$(realpath ../libfinal)
make
sudo make install
mv ../libfinal/include/final ../
```