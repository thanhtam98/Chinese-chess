# Checkmate Detection - Analysis & Solution

## Table of Contents

1. [Current Implementation Analysis](#1-current-implementation-analysis)
2. [The Gap: What is Missing](#2-the-gap-what-is-missing)
3. [Chinese Chess End-Game Rules](#3-chinese-chess-end-game-rules)
4. [Proposed Solution](#4-proposed-solution)
5. [Detailed Design](#5-detailed-design)
6. [Integration Points](#6-integration-points)
7. [Edge Cases](#7-edge-cases)
8. [Testing Strategy](#8-testing-strategy)

---

## 1. Current Implementation Analysis

### 1.1 What Exists Today

The project has a class called `Umpire` (`logic/inc/umpire.h`, `logic/src/umpire.cpp`) that handles move validation related to the General (King). Despite its method names containing "checkMate", it only implements **check detection** — not **checkmate detection**.

#### `processCheckMate(team_code team)` — Check Detection

```cpp
// logic/src/umpire.cpp:61-99
std::vector<Point*> Umpire::processCheckMate(team_code team) {
    Point *generalLocation = mBoard->getGeneralLocation(team);
    IChessman *generalChessman = mBoard->getChessman(generalLocation);

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            IChessman *chessman = mBoard->getChessman(x, y);
            if (chessman == nullptr) continue;
            if (chessman->getTeam() == generalChessman->getTeam()) continue;

            std::vector<Point*> possibleMoves = chessman->getPossibleMoves(mBoard);
            if (std::find(possibleMoves.begin(), possibleMoves.end(),
                generalLocation) != possibleMoves.end()) {
                ret.push_back(Point::of(x, y));     // attacker position
            }
        }
    }
    if (ret.size() != 0) {
        ret.push_back(generalLocation);              // general under attack
    }
    return ret;
}
```

**What it does:** Scans all opponent pieces to find which ones can attack the given team's General. Returns the list of attacker positions (plus the General's position for UI highlighting).

**What it does NOT do:** It does not check whether the team has any legal move to escape the check.

#### `preCheckMate(from, to, team)` — Pre-Move Validation

```cpp
// logic/src/umpire.cpp:11-21
bool Umpire::preCheckMate(Point* from, Point* to, team_code team) {
    IBoard* snapshot = new Board(Board::getInstance());
    snapshot->move(from, to);
    setBoard(snapshot);
    auto result = processCheckMate(team);
    delete snapshot;
    return result.size() != 0 ? true : false;
}
```

**What it does:** Simulates a move on a board copy, then checks if the team's General would be in check after the move. Returns `true` if the General would be under attack (move is illegal).

#### `MoveManager::preCalculatePossiblePotentials()` — Move Gatekeeper

```cpp
// ui/src/moveManager.cpp:61-81
bool MoveManager::preCalculatePossiblePotentials() {
    IChessman* chessman = board->getChessman(source);
    team_code team = chessman->getTeam();
    return !umpire->preCheckMate(source, dest, team);
}
```

**What it does:** Called before every move execution in `movePiece()`. Rejects any move that would leave the moving player's own General in check.

#### Game Over — General Capture Only

```cpp
// logic/src/board.cpp:55-74
void Board::move(Point* from, Point* to) {
    IChessman* fromChessman = getChessman(from);
    if (isOccupied(to)) {
        IChessman* toChessman = getChessman(to);
        if (toChessman->getCode() == GENERAL) {
            endGame(fromChessman->getTeam());   // only trigger
        }
        delete toChessman;
    }
    // ...
}
```

**What it does:** The game ends **only** when a General piece is physically captured. This means the game never ends via checkmate — it requires the opponent to literally take the General piece.

### 1.2 Current Flow Summary

```
Player clicks piece → calculatePossibleMoves() → highlight valid squares
Player clicks destination → preCalculatePossiblePotentials()
  → umpire->preCheckMate(source, dest, team)
    → Simulate move on snapshot board
    → processCheckMate(team) — is MY general still in check?
    → If yes → reject move
    → If no  → allow move
  → board->move(source, dest)
    → If captured piece is GENERAL → endGame()
  → calculatePossiblePotentials() — highlight any check state
  → Switch turn
```

### 1.3 Naming Confusion

| Method Name | What it Actually Does | Expected Meaning |
|---|---|---|
| `processCheckMate()` | Detects **check** (General under attack) | Should detect **checkmate** (no escape) |
| `preCheckMate()` | Validates a move won't self-check | Pre-move checkmate validation |
| `checkMate()` | Returns check state for display | Should determine checkmate |

The methods implement **check** detection but are named as if they handle **checkmate**. This is the root of the confusion and the core gap.

---

## 2. The Gap: What is Missing

### 2.1 No Checkmate Detection

**Checkmate** = The General is in check AND the player has NO legal move to escape.

The current code can detect that a General is in check, and it can prevent illegal moves (self-check). But it never asks the critical question:

> "Does the player whose turn it is have ANY legal move at all?"

Without this, the game:
- Never declares a winner via checkmate
- Requires the General to be literally captured (which shouldn't happen if check is properly enforced)
- Creates a paradox: if `preCheckMate` blocks all moves for a player in checkmate, the player is stuck with no moves but the game doesn't end

### 2.2 No Stalemate Detection

**Stalemate** = The General is NOT in check BUT the player has NO legal move.

In Chinese chess (Xiangqi), stalemate is a **loss** for the stalemated player (unlike international chess where it's a draw). This is also not implemented.

### 2.3 No Post-Move Checkmate Evaluation

After a player makes a move, the system should check:
1. Is the opponent's General now in check? (already implemented via `calculatePossiblePotentials`)
2. Does the opponent have any legal move? (NOT implemented)
3. If no legal move exists → game over

---

## 3. Chinese Chess End-Game Rules

### 3.1 Checkmate (Chiếu bí / 将死)

A player is **checkmated** when:
- Their General is under attack (in check)
- No piece of theirs can make a legal move to:
  - Move the General to a safe square
  - Block the attack
  - Capture the attacking piece

**Result:** The checkmated player **loses**.

### 3.2 Stalemate (Hết nước / 困毙)

A player is **stalemated** when:
- Their General is NOT under attack
- They have no legal move with any piece

**Result:** In Chinese chess, the stalemated player **loses** (unlike international chess). This is sometimes called "kùnbì" (困毙).

### 3.3 Perpetual Check (Chiếu dài / 长将)

A player who delivers check on every move (perpetual check) **loses**. This is a more advanced rule that could be implemented later.

### 3.4 Summary of End Conditions

| Condition | General in Check? | Legal Moves? | Result |
|---|---|---|---|
| Checkmate | Yes | None | Player loses |
| Stalemate | No | None | Player loses (in Xiangqi) |
| Normal play | Yes or No | Has moves | Continue |

---

## 4. Proposed Solution

### 4.1 High-Level Approach

Add a new method `isCheckmate()` to the `Umpire` class that:
1. Iterates over ALL pieces of the given team
2. For each piece, gets all raw possible moves
3. For each possible move, simulates it and checks if the General is still in check
4. If ANY move results in the General NOT being in check → NOT checkmate
5. If NO move escapes check → CHECKMATE

### 4.2 Algorithm

```
function isCheckmate(team):
    for each square (x, y) on the board:
        piece = board.getChessman(x, y)
        if piece is null OR piece.team != team:
            continue

        possibleMoves = piece.getPossibleMoves(board)
        for each move in possibleMoves:
            if NOT preCheckMate(Point(x,y), move, team):
                return false    // found a legal move → not checkmate

    return true                 // no legal move found → checkmate (or stalemate)
```

### 4.3 Distinguishing Checkmate from Stalemate

```
function getGameEndState(team):
    hasLegalMove = !isCheckmate(team)    // reuse the same logic

    if hasLegalMove:
        return CONTINUE

    isInCheck = processCheckMate(team).size() > 0

    if isInCheck:
        return CHECKMATE               // General under attack, no escape
    else:
        return STALEMATE               // No legal move, but not in check
```

In Chinese chess, both checkmate and stalemate result in a loss, but distinguishing them is useful for:
- UI messaging ("Checkmate!" vs "Stalemate!")
- Game history/logging
- Potential future rule variations

---

## 5. Detailed Design

### 5.1 New Types

Add to `constant.h`:

```cpp
enum game_end_state {
    GAME_CONTINUE,
    GAME_CHECKMATE,
    GAME_STALEMATE
};
```

### 5.2 New Umpire Methods

Add to `logic/inc/umpire.h`:

```cpp
class Umpire {
public:
    // ... existing methods ...

    // Returns true if the given team has no legal moves
    bool hasNoLegalMoves(team_code team);

    // Returns the game end state for the given team
    game_end_state evaluateGameEnd(team_code team);
};
```

### 5.3 Implementation

Add to `logic/src/umpire.cpp`:

```cpp
bool Umpire::hasNoLegalMoves(team_code team) {
    IBoard* board = Board::getInstance();

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            IChessman* chessman = board->getChessman(x, y);

            if (chessman == nullptr) continue;
            if (chessman->getTeam() != team) continue;

            Point* from = Point::of(x, y);
            std::vector<Point*> moves = chessman->getPossibleMoves(board);

            for (Point* to : moves) {
                // Simulate: does this move leave our General safe?
                if (!preCheckMate(from, to, team)) {
                    return false;  // At least one legal move exists
                }
            }
        }
    }
    return true;  // No legal move found
}

game_end_state Umpire::evaluateGameEnd(team_code team) {
    if (!hasNoLegalMoves(team)) {
        return GAME_CONTINUE;
    }

    setBoard(Board::getInstance());
    auto attackers = processCheckMate(team);

    if (attackers.size() > 0) {
        return GAME_CHECKMATE;
    } else {
        return GAME_STALEMATE;
    }
}
```

### 5.4 Optimization: Early Exit

The naive approach iterates ALL pieces and ALL their moves. For performance, the key optimization is **early exit**: return `false` as soon as any legal move is found. This means in most game states, we exit very quickly (the first piece with a legal move terminates the search).

**Worst case** (actual checkmate/stalemate): must scan every piece and every move. On a 9x10 board with ~16 pieces remaining and ~10 moves each, that's ~160 simulations. Each simulation copies the board (9x10 = 90 cells) and scans for attackers. This is fast enough for a turn-based game.

### 5.5 Optional: Pre-filtering with Check Detection

For additional optimization when the General IS in check, we can narrow the search:

```cpp
bool Umpire::hasNoLegalMoves(team_code team) {
    IBoard* board = Board::getInstance();
    setBoard(board);
    auto attackers = processCheckMate(team);
    bool isInCheck = attackers.size() > 0;

    if (isInCheck) {
        // Optimization: when in check, prioritize:
        // 1. General moves (can it escape?)
        // 2. Pieces that can capture the attacker
        // 3. Pieces that can block the attack line
        // But the general approach still works correctly.
    }

    // General approach: try all pieces, all moves
    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            IChessman* chessman = board->getChessman(x, y);
            if (chessman == nullptr) continue;
            if (chessman->getTeam() != team) continue;

            Point* from = Point::of(x, y);
            std::vector<Point*> moves = chessman->getPossibleMoves(board);

            for (Point* to : moves) {
                if (!preCheckMate(from, to, team)) {
                    return false;
                }
            }
        }
    }
    return true;
}
```

---

## 6. Integration Points

### 6.1 After Each Move — Check for Opponent's Checkmate

The primary integration point is `MoveManager::movePiece()`. After a successful move, check if the **opponent** is in checkmate.

**Current flow** (`ui/src/moveManager.cpp:94-138`):

```cpp
bool MoveManager::movePiece(bool shouldNotify) {
    if (preCalculatePossiblePotentials() == false) {
        return false;
    }
    // ... swap UI labels, execute board->move() ...

    board->move(source, dest);
    calculatePossiblePotentials();       // ← highlight check state

    if (shouldNotify) {
        transfer->sendMsg(MOV, source, dest);
    }
    return true;
}
```

**Modified flow:**

```cpp
bool MoveManager::movePiece(bool shouldNotify) {
    if (preCalculatePossiblePotentials() == false) {
        return false;
    }
    // ... swap UI labels, execute board->move() ...

    board->move(source, dest);
    calculatePossiblePotentials();

    // NEW: Check if opponent is in checkmate or stalemate
    team_code currentTeam = board->getChessman(dest)->getTeam();
    team_code opponentTeam = (currentTeam == RED) ? BLACK : RED;
    game_end_state endState = umpire->evaluateGameEnd(opponentTeam);

    if (endState == GAME_CHECKMATE) {
        board->endGame(currentTeam);
        // Show "Checkmate! [currentTeam] wins!" message
    } else if (endState == GAME_STALEMATE) {
        board->endGame(currentTeam);
        // Show "Stalemate! [currentTeam] wins!" message
    }

    if (shouldNotify) {
        transfer->sendMsg(MOV, source, dest);
    }
    return true;
}
```

### 6.2 After Turn Switch — UI Notification

Add a visual notification when checkmate/stalemate is detected. The `BoardDialog` could show a dialog/message.

```cpp
// In boardDialog.h, add:
void showGameOverDialog(team_code winner, game_end_state reason);
```

### 6.3 Preventing Moves After Game Over

Ensure no more moves can be made after checkmate:

```cpp
// In MoveManager::movePiece(), at the very start:
if (board->isGameOver) {
    return false;
}
```

The `IBoard` already has `bool isGameOver` — use it to block further moves.

### 6.4 Online Mode Synchronization

For online mode, the checkmate evaluation should happen on BOTH sides after a move is received. The `movePieceTransferCb` callback should also trigger the evaluation:

```cpp
void MoveManager::movePieceTransferCb(Point *from, Point *to) {
    setSourcePoint(from);
    setDestPoint(to);
    decorateTargetedPieces(false);
    movePiece(false);       // This now includes checkmate detection
    ITurn::end();
    mainDialog->redrawTeamSignal();
}
```

Since `movePiece()` already handles the checkmate check, online mode is automatically covered.

### 6.5 Full Integration Diagram

```
After a move is executed:
  │
  ├─→ board->move(source, dest)
  │     └─→ (remove old General-capture game-over, or keep as safety net)
  │
  ├─→ calculatePossiblePotentials()
  │     └─→ Highlight check state on UI
  │
  ├─→ [NEW] umpire->evaluateGameEnd(opponentTeam)
  │     ├─→ hasNoLegalMoves(opponentTeam)
  │     │     ├─→ For each opponent piece:
  │     │     │     ├─→ getPossibleMoves(board)
  │     │     │     └─→ For each move: preCheckMate(from, to, team)
  │     │     │           ├─→ Simulate move on snapshot
  │     │     │           └─→ processCheckMate(team)
  │     │     │                 └─→ Any attacker can reach General?
  │     │     └─→ If ANY move is legal → return false (not checkmate)
  │     │
  │     ├─→ If hasNoLegalMoves == true:
  │     │     ├─→ processCheckMate(team) to distinguish check vs no-check
  │     │     ├─→ Return GAME_CHECKMATE or GAME_STALEMATE
  │     │
  │     └─→ If hasNoLegalMoves == false:
  │           └─→ Return GAME_CONTINUE
  │
  ├─→ If GAME_CHECKMATE or GAME_STALEMATE:
  │     ├─→ board->endGame(winnerTeam)
  │     └─→ Show game-over UI
  │
  └─→ Switch turn (ITurn::end())
```

---

## 7. Edge Cases

### 7.1 Double Check

When two pieces simultaneously attack the General, only the General itself can move (blocking or capturing one attacker doesn't help). The algorithm handles this correctly because `preCheckMate` simulates the full board state after any move.

### 7.2 Flying General Rule

The "flying general" rule (two Generals cannot face each other on the same column with no piece between them) is already implemented in `GeneralBehaviorProvider::handleAfter()`. This is automatically considered during `getPossibleMoves()`, so the checkmate algorithm handles it correctly.

### 7.3 Pinned Pieces

A piece that is "pinned" (moving it would expose the General to check) cannot legally move. The `preCheckMate` simulation handles this: if moving a pinned piece exposes the General, `preCheckMate` returns `true`, and the move is excluded from legal moves.

### 7.4 Discovered Check Leading to Checkmate

When a piece moves and reveals an attack on the opponent's General from another piece, the opponent might be in checkmate. The algorithm handles this because it evaluates the full board state after each simulated move.

### 7.5 Board Snapshot Memory Management

`preCheckMate` creates a `new Board(Board::getInstance())` snapshot for each simulation. Inside `hasNoLegalMoves()`, this is called multiple times. Each snapshot is properly `delete`d after use. However, for performance, consider creating a single mutable snapshot and undoing moves instead of creating/destroying board copies:

```cpp
// Performance optimization (optional, for later):
bool Umpire::hasNoLegalMoves(team_code team) {
    IBoard* snapshot = new Board(Board::getInstance());

    for (int x = 0; x < BOARD_WIDTH; x++) {
        for (int y = 0; y < BOARD_LENGTH; y++) {
            // ... try moves on snapshot, undo after each ...
        }
    }
    delete snapshot;
}
```

### 7.6 Empty Board / No General

If a General is missing (shouldn't happen, but defensive programming):
- `getGeneralLocation()` returns `nullptr`
- `processCheckMate()` would crash on null dereference
- Add a null check: `if (generalLocation == nullptr) return {};`

---

## 8. Testing Strategy

### 8.1 Unit Tests

Add tests in `test/` directory:

```cpp
// test/checkmateTest.cc

// Test 1: Simple checkmate - General cornered with no escape
TEST(CheckmateTest, SimpleCheckmate) {
    // Setup: Red General at (4,0), Black Chariot at (4,2), (3,1)
    // Red has no legal move
    // Expected: isCheckmate(RED) == true
}

// Test 2: Not checkmate - General can escape
TEST(CheckmateTest, GeneralCanEscape) {
    // Setup: Red General at (4,0), Black Chariot at (4,2)
    // General can move to (3,0) or (5,0)
    // Expected: isCheckmate(RED) == false
}

// Test 3: Block the check
TEST(CheckmateTest, CanBlockCheck) {
    // Setup: Red General at (4,0), Red Advisor at (3,1), Black Chariot at (4,9)
    // Advisor can move to (4,1) to block
    // Expected: isCheckmate(RED) == false
}

// Test 4: Capture the attacker
TEST(CheckmateTest, CanCaptureAttacker) {
    // Setup: Red General at (4,0), Red Chariot at (0,2), Black Chariot at (4,2)
    // Red Chariot can capture Black Chariot
    // Expected: isCheckmate(RED) == false
}

// Test 5: Stalemate
TEST(CheckmateTest, Stalemate) {
    // Setup: Red General at (3,0), blocked by own pieces, no enemy check
    // Red has no legal moves
    // Expected: evaluateGameEnd(RED) == GAME_STALEMATE
}

// Test 6: Double check - only General move can save
TEST(CheckmateTest, DoubleCheckMate) {
    // Setup: Red General attacked by two pieces, all escape squares covered
    // Expected: isCheckmate(RED) == true
}

// Test 7: Flying general causes check
TEST(CheckmateTest, FlyingGeneralCheck) {
    // Setup: Moving a piece reveals Generals facing each other
    // The move is illegal due to flying general rule
}

// Test 8: Normal game state
TEST(CheckmateTest, NormalGameNotCheckmate) {
    // Setup: Standard opening position
    // Expected: isCheckmate(RED) == false AND isCheckmate(BLACK) == false
}
```

### 8.2 Integration Tests

Test the full flow from `movePiece()` triggering game end:

```cpp
TEST(IntegrationTest, MoveCausesCheckmate) {
    // Setup board near checkmate position
    // Execute the move that delivers checkmate
    // Verify board->isGameOver == true
    // Verify board->winningTeam is correct
}
```

### 8.3 Manual Test Scenarios

| # | Scenario | Steps | Expected Result |
|---|---|---|---|
| 1 | Basic checkmate | Create position where General is cornered | Game ends, winner declared |
| 2 | Check but not checkmate | Deliver check with escape available | Game continues, check highlighted |
| 3 | Stalemate | Create position with no legal moves, no check | Game ends, winner declared |
| 4 | Online checkmate | Deliver checkmate in online mode | Both sides see game over |
| 5 | Debug mode | Verify checkmate detection in debug mode | Works without turn restrictions |

---

## Summary

| Aspect | Current State | After Implementation |
|---|---|---|
| Check detection | Implemented | Unchanged |
| Pre-move validation | Implemented | Unchanged |
| Checkmate detection | Not implemented | `Umpire::hasNoLegalMoves()` + `evaluateGameEnd()` |
| Stalemate detection | Not implemented | Covered by `evaluateGameEnd()` |
| Game over trigger | General captured | Checkmate / Stalemate / General captured (safety net) |
| UI notification | Check highlighting only | Check highlighting + Game over dialog |
| Online sync | Moves only | Moves + game end state |

The solution reuses the existing `preCheckMate()` simulation approach, making it a natural extension of the current architecture. The early-exit optimization ensures good performance in normal play, and the worst-case scenario (actual checkmate) involves at most ~160 board simulations — well within acceptable limits for a turn-based terminal game.
