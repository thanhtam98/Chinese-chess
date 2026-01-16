# Chinese Chess - Quick Reference Guide

## Project Overview

**Chinese Chess for Terminal** - A networked Chinese chess game in the terminal with offline/online modes.

- **Language**: C++14
- **UI Framework**: FinalCut
- **Networking**: WebSocket++ (with JSON for message serialization)
- **Testing**: Google Test
- **Architecture**: Layered MVC with Observer and Builder patterns

---

## Module Map

```
📁 Core Logic (logic/)
   ├─ iBoard.h / Board.cpp          → Game board state (Singleton)
   ├─ iChessman.h / Chessman.cpp    → Individual pieces (Factory pattern)
   └─ Umpire.h / Umpire.cpp         → Check/mate validation

📁 Movement Rules (rule/)
   ├─ rule.h                         → Rule service interface
   ├─ ruleShapeBuilder.h/cpp         → Define piece movement shapes
   └─ ruleTargetBuilder.h/cpp        → Validate move targets

📁 User Interface (ui/)
   ├─ mainDialog.h/cpp              → Main window container
   ├─ introDialog.h/cpp             → Splash screen with animations
   ├─ configDialog.h/cpp            → Mode selection dialog
   ├─ boardDialog.h/cpp             → Game board display
   └─ moveManager.h/cpp             → Move orchestrator

📁 Network (websockpp/)
   ├─ connectionBase.h/cpp          → Abstract connection (Singleton)
   ├─ server.h/cpp                  → Server implementation
   ├─ client.h/cpp                  → Client implementation
   ├─ transfer.h/cpp                → Network protocol handler
   └─ wConfig.h                     → WebSocket configuration

📁 Utilities (utils/)
   ├─ constant.h                    → Enums (team, chessman, direction)
   ├─ point.h                       → 2D coordinates
   ├─ utils.h                       → Helper functions
   └─ log.h                         → Logging system
```

---

## Key Classes

### Board (Singleton)
```cpp
IBoard* board = Board::getInstance();
board->isOccupied(x, y);                      // Check if position has piece
board->getChessman(x, y);                     // Get piece at position
board->move(from, to);                        // Execute move
board->getPossibleMoves(target);              // Get valid moves
board->getGeneralLocation(team);              // Get general position
```

### Chessman (Factory)
```cpp
Piece piece{GENERAL, RED};
IChessman* general = IChessman::newInstance(piece, Point(4, 0));
general->getTeam();                           // RED
general->getCode();                           // GENERAL
general->getName();                           // "Red General"
general->getPossibleMoves(board);             // Valid moves
```

### Rule (Builder)
```cpp
vector<Point*>* moves = Rule::create(board)
    .at(targetPoint)
    .forChessman(chessman)
    .build()
    ->getPossibleMove();
```

### MoveManager
```cpp
MoveManager* mgr = new MoveManager(boardDialog);
mgr->setSourcePoint(point);                   // Select piece
mgr->calculatePossibleMoves(false);           // Highlight valid moves
mgr->setDestPoint(point);                     // Select destination
mgr->movePiece(false);                        // Execute move (false = offline)
```

### ConnectionBase (Singleton)
```cpp
ConnectionBase* conn = ConnectionBase::setInstance(WCLIENT);
conn->run();                                  // Start connection
conn->send(jsonMessage);                      // Send message
conn->setRecvCallback(callback);              // Set receive handler
```

---

## Board Layout

```
     0   1   2   3   4   5   6   7   8
   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┐
0  │   │   │   │   │G  │   │   │   │   │  RED General at (4,0)
1  │   │   │   │   │   │   │   │   │   │  RED Fortress: (0-2,0-2), (6-8,0-2)
2  │   │   │   │   │   │   │   │   │   │
3  │   │Cn │   │   │   │   │   │Cn │   │  Cannons at (1,3) and (7,3)
4  │───┼───┼───┼───┼───┼───┼───┼───┼───│  RIVER ← Blocks elephant
5  │   │Cn │   │   │   │   │   │Cn │   │
6  │   │   │   │   │   │   │   │   │   │
7  │   │   │   │   │   │   │   │   │   │  BLACK Start
8  │   │   │   │   │G  │   │   │   │   │  BLACK General at (4,8)
   └───┴───┴───┴───┴───┴───┴───┴───┴───┘

Piece Count (30 total):
- General: 1 per team
- Advisor: 2 per team
- Elephant: 2 per team
- Horse: 2 per team
- Chariot: 2 per team
- Cannon: 2 per team
- Soldier: 5 per team
```

---

## Game Flow

### Startup Sequence
```
main()
  ↓
FApplication::app()
  ↓
MainDialog::initLayout()
  ├─ IntroDialog (animations)
  ├─ ConfigDialog (mode selection)
  └─ BoardDialog (game board)
  ↓
app.exec() [Event loop]
```

### Move Sequence (Offline)
```
User clicks piece
  ↓
BoardDialog::clickedCallback()
  ├─ MoveManager::setSourcePoint()
  ├─ MoveManager::calculatePossibleMoves()
  └─ Highlight valid moves
  ↓
User clicks destination
  ↓
MoveManager::movePiece()
  ├─ Validate move
  ├─ Board::move()
  ├─ Update UI
  └─ Switch turns
```

### Move Sequence (Online)
```
Player 1: Move → Transfer::sendMsg() → ConnectionBase::send()
                                              ↓
                                        [Network]
                                              ↓
Player 2: Receive → onMessage() → Transfer::dispatchMsg()
                                    → MoveManager::movePieceTransferCb()
```

---

## Piece Movement Rules

| Piece | Movement | Restrictions |
|-------|----------|--------------|
| **General** | 1 step orthogonal | Within fortress only (3x3) |
| **Advisor** | 1 step diagonal | Within fortress only |
| **Elephant** | 2 steps diagonal | Cannot cross river (y=4) |
| **Horse** | Knight-like (2+1) | Can be blocked by adjacent pieces |
| **Chariot** | Any distance orthogonal | Moves until obstacle |
| **Cannon** | Any distance orthogonal | Must jump 1 piece to capture |
| **Soldier** | 1 step forward (backward after river) | Forward until cross river |

---

## Network Protocol

### Message Format
```json
{
  "op": "MOV",                    // or "SEL"
  "from": {"x": 2, "y": 0},
  "to": {"x": 2, "y": 2}          // optional for SEL
}
```

### Connection Types
```cpp
enum connection_type {
    WSERVER,           // Host (listen on 0.0.0.0:9002)
    WCLIENT,           // Client (connect to server)
    NON_CONNECTION     // Offline mode
};
```

### Server/Client Flow
```
Server: Displays IP → Waits for connection
Client: Input IP → Connect to Server → Connection established
Game: Server makes move → Client receives → Client makes move → Server receives
```

---

## Important Enums

### team_code
```cpp
enum team_code { RED, BLACK, TEAM_SIZE, T_NONE };
```

### chessman_code
```cpp
enum chessman_code {
    GENERAL, ADVISOR, ELEPHANT, HORSE, CHARIOT, 
    CANNON, SOLDIER, CHESSMAN_SIZE, C_NONE
};
```

### direction_code
```cpp
enum direction_code {
    WEST, EAST, NORTH, SOUTH,
    NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST,
    DIR_SIZE
};
```

---

## UI Color Scheme

```cpp
// RED team pieces
RED_BG = FColor::Red
FOCUS_RED_BG = FColor::Red1                    // Selected
POTENTIAL_RED_BG = FColor::LightPink4          // Valid move

// BLACK team pieces
BLACK_BG = FColor::Black
FOCUS_BLACK_BG = FColor::Grey50                // Selected
POTENTIAL_BLACK_BG = FColor::DeepPink6         // Valid move

// General-specific (check safety)
POTENTIAL_GENERAL_RED_BG = FColor::LightCyan3
POTENTIAL_GENERAL_BLACK_BG = FColor::DarkCyan2
```

---

## Build Commands

```bash
# Full setup
make setup              # Install deps + build project

# Building
make build              # Release build
make build-debug        # Debug with symbols
make clean              # Remove build artifacts
make rebuild            # Clean + build

# Testing
make test               # Run all tests
make test-verbose       # Detailed test output
make test-filter F=...  # Run specific test

# Running
make run                # Execute game
make run-debug          # Run with gdb

# Status
make status             # Show project status
```

---

## Testing

```bash
# Run all tests
./build/mainTest

# Run specific test
./build/mainTest --gtest_filter="PointTest*"

# With verbose output
./build/mainTest --gtest_verbose
```

---

## Common Tasks

### Adding a New Piece Type

1. Add to `chessman_code` enum in `constant.h`
2. Implement movement rules in `ruleShapeBuilder.cpp`
3. Update `Board::setup()` with starting positions
4. Add UI representation (label)

### Implementing Online Mode

1. ✅ ConnectionBase (abstract interface) - Done
2. ✅ Server/Client implementations - Done
3. ✅ Transfer (message protocol) - Done
4. ✅ Integration with MoveManager - Done

### Debugging

```cpp
// Enable logging
#include "log.h"
LOG_F(INFO, "Message: %s", var.c_str());

// Common log levels
LOG_F(INFO, "Information");
LOG_F(WARNING, "Warning");
LOG_F(ERROR, "Error");
```

---

## Key Design Patterns

| Pattern | Where | Why |
|---------|-------|-----|
| **Singleton** | Board, ConnectionBase | Single instance needed |
| **Factory** | IChessman::newInstance() | Create appropriate subclass |
| **Builder** | Rule system | Fluent move calculation |
| **Strategy** | Rule shapes/targets | Different algorithms |
| **Observer** | UI callbacks | Loose coupling |
| **Chain of Responsibility** | Dialog chain | Sequential processing |
| **Adapter** | Transfer | Convert moves to JSON |
| **State Machine** | Game states | Dialog transitions |

---

## Troubleshooting

### Build Issues
```bash
# Clean rebuild
make clean && make build

# With verbose output
./scripts/build.sh -v

# Check dependencies
make status
```

### Runtime Issues
```bash
# Run with debug symbols
make build-debug
gdb ./build/chinese-chess

# Enable logging
uncomment: freopen("/workspaces/chinese-chess/log.txt","w",stdout);
```

### Network Issues
```bash
# Check connection
netstat -tan | grep 9002

# Verify server is running
ps aux | grep chinese-chess

# Use verbose network logging in ConnectionBase
```

---

## Architecture Highlights

✅ **Separation of Concerns**: Logic, UI, Network clearly separated
✅ **Extensibility**: Easy to add new pieces or rules
✅ **Testability**: Unit tests with Google Test
✅ **Maintainability**: Clear naming, consistent style
✅ **Performance**: Efficient move calculation, proper threading
✅ **Cross-Platform**: Supports x86_64 and ARM64

---

## File Size Reference

```
main.cpp                          ~100 lines
logic/                            ~500 lines
rule/                             ~300 lines
ui/                               ~1000 lines
websockpp/                        ~400 lines
utils/                            ~200 lines
test/                             ~500 lines

Total: ~3000 lines of code
```

---

## Next Steps & TODO

- [ ] Checkmate detection (not just general capture)
- [ ] In-check validation before any move
- [ ] Public demo/blog post
- [ ] Refactor pieces to optimize memory
- [ ] Possible mobile port?

---

## Resources

- **FinalCut Docs**: [FinalCut GitHub](https://github.com/gansm/finalcut)
- **WebSocket++ Docs**: [WebSocket++ GitHub](https://github.com/zaphoyd/websocketpp)
- **JSON Docs**: [nlohmann/json GitHub](https://github.com/nlohmann/json)
- **Google Test**: [GoogleTest GitHub](https://github.com/google/googletest)

---

## Contact / Contributing

This is a professional C++ project with clean architecture. Contributions welcome!

Areas for contribution:
- Checkmate detection algorithm
- Additional UI themes/colors
- Performance optimization
- Documentation improvements
- Platform-specific enhancements (ARM improvements, etc.)

---

**Documentation Generated**: January 16, 2026
**Project Status**: Active Development (MVP Complete)
**Last Updated**: See commit history
