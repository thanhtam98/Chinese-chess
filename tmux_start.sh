#!/bin/bash

# Create a new tmux session with the first pane
tmux new-session -d -s game_session

# Split the window horizontally (top and bottom) with bottom pane smaller
# -p specifies the percentage size of the new pane
tmux split-window -v -p 30

# Select the top pane and split it vertically (left and right)
tmux select-pane -t 0
tmux split-window -h

# Select the bottom pane and split it vertically (left and right)
tmux select-pane -t 2
tmux split-window -h

# set mouse on
tmux set-option -t game_session mouse on
# Send commands to each pane
# Pane 0 (top-left): run game with 1.log
tmux send-keys -t 0 './run_game.sh -f 1.log' C-m

# Pane 1 (top-right): run game with 2.txt
tmux send-keys -t 1 './run_game.sh -f 2.log' C-m

# Pane 2 (bottom-left): tail 1.txt
tmux send-keys -t 2 'sleep 2 && tail -f 1.log' C-m

# Pane 3 (bottom-right): tail 2.txt
tmux send-keys -t 3 'sleep 2 && tail -f 2.log' C-m

# Attach to the session
tmux attach-session -t game_session
# ```

# The `-p 30` parameter means the bottom panes will take up 30% of the vertical space (you can adjust this number - smaller values make the bottom panes even smaller, e.g., `-p 20` for 20%).

# The layout will now look like this:
# ```
# ┌─────────────────┬─────────────────┐
# │  Pane 0         │  Pane 1         │
# │  run_game.sh    │  run_game.sh    │
# │  -f 1.txt       │  -f 2.txt       │
# │                 │                 │
# │                 │                 │
# ├─────────────────┼─────────────────┤
# │  Pane 2         │  Pane 3         │
# │  tail -f 1.txt  │  tail -f 2.txt  │
# └─────────────────┴─────────────────┘