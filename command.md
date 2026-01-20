# Commands

## Build
- First-time setup (deps + build):
  - `make setup`
- Regular build:
  - `make build`
- Debug build (symbols, no optimizations):
  - `make build-debug`

## Run
- Run the game via Makefile:
  - `make run`
- Run directly (sets runtime env):
  - `./run_game.sh`

## Debug
- Build debug binary:
  - `make build-debug`
- Run under gdb:
  - `make run-debug`
  - or `gdb ./build/chinese-chess`
- In-game debug mode (free moves):
  - Press `D` on the mode selection screen

## Tmux 4-pane launcher
- Start a 2x2 pane layout (two game runs + two log tails):
  - `./tmux_start.sh`
- What it runs:
  - Pane 1: `./run_game.sh -f 1.txt`
  - Pane 2: `./run_game.sh -f 2.txt`
  - Pane 3: `tail -f 1.txt`
  - Pane 4: `tail -f 1.txt`
- Exit / stop:
  - Detach: `Ctrl-b d`
  - Stop programs: `Ctrl-c` in each pane
  - Kill the session: `tmux kill-session -t chinese-chess`
  - Kill and exit: `Ctrl-b & and y`
