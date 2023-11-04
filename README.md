# Chinese chess

## Todo
- [x] Write code for IBoard and IChessman
- [x] Write newInstance for IChessman and implementations for every chessman
- [x] Design move chessman mechanism
- [x] Design the User Interface (Ref: https://github.com/gansm/finalcut/blob/main/doc/first-steps.md#first-steps-with-the-final-cut-widget-toolkit)
- [x] Refactor behaviorProviders [Optional] 
- [x] Refactor "include" in source tree.
- [x] Bug: After eliminating the opponent, the piece at the former location does not disappear.
- [x] Integrate websocketpp logging into internal logging system.
- [x] Implement logging module.
- [ ] Refactor pieces to optimize memory usage [Optional]
- [ ] Multi-platform support (build + run).
- [ ] Design server-client model for online gaming (websocketpp preferred).
- [ ] Design ConnectionBase class for both server and client.
- [ ] Check when the game is over. (MVP: General is captured).
- [ ] Checkmate detection: pubsub mechanism or brute-force.
- [ ] Public to community network (Blog + Demo).


## How to install final cut lib to project
``` bash
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
rm -rf ../finalcut
cd ..
```

## Troubleshoot
In case of the terminal doest show chessman characters, please use the following command before running the game!
``` bash
export LC_ALL=en_US.UTF-8
```

# Github mirroring

## Websocket Document
Reference:
1. https://github.com/zaphoyd/websocketpp
2. https://docs.websocketpp.org/tutorials.html
