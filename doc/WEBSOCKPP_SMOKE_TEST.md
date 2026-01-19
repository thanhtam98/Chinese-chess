# Websockpp Smoke Test (Server + Client)

This document shows how to run a minimal local server/client test that connects,
sends a JSON message, and receives an ACK.

## Prerequisites

Run a normal build once so the `_deps` include paths exist:

```bash
./scripts/build.sh
```

## Step-by-step

1) Build the server test app:

```bash
/usr/bin/c++ -std=c++14 -pthread \
  -I/workspaces/Chinese-chess -I/workspaces/Chinese-chess/utils/inc \
  -I/workspaces/Chinese-chess/websockpp/inc \
  -I/workspaces/Chinese-chess/build/_deps/websocketpp-src \
  -I/workspaces/Chinese-chess/build/_deps/json-src/include \
  tools/websockpp_server_smoke.cpp websockpp/src/server.cpp websockpp/src/client.cpp \
  websockpp/src/connectionBase.cpp websockpp/src/wConfig.cpp utils/src/log.cpp \
  -o /tmp/ws_server_smoke
```

2) Build the client test app:

```bash
/usr/bin/c++ -std=c++14 -pthread \
  -I/workspaces/Chinese-chess -I/workspaces/Chinese-chess/utils/inc \
  -I/workspaces/Chinese-chess/websockpp/inc \
  -I/workspaces/Chinese-chess/build/_deps/websocketpp-src \
  -I/workspaces/Chinese-chess/build/_deps/json-src/include \
  tools/websockpp_client_smoke.cpp websockpp/src/client.cpp websockpp/src/server.cpp \
  websockpp/src/connectionBase.cpp websockpp/src/wConfig.cpp utils/src/log.cpp \
  -o /tmp/ws_client_smoke
```

3) In terminal A, start the server (replace port if needed):

```bash
/tmp/ws_server_smoke 9102
```

4) In terminal B, start the client (replace host/port if needed):

```bash
/tmp/ws_client_smoke 127.0.0.1 9102
```

## Expected output

Server:

```
server received: {"from":[0,0],"opcode":0,"to":[1,1]}
```

Client:

```
client received: {"ack":true}
```

## Cleanup (optional)

```bash
rm -f /tmp/ws_server_smoke /tmp/ws_client_smoke
```
