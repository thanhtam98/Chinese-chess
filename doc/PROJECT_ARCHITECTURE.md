# Chinese Chess - Comprehensive Project Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Core Modules](#core-modules)
4. [Function Call Flow](#function-call-flow)
5. [Component Interactions](#component-interactions)
6. [Game Logic](#game-logic)
7. [UI Framework](#ui-framework)
8. [Network Communication](#network-communication)
9. [Build System](#build-system)

---

## Project Overview

### What is Chinese Chess for Terminal?

Chinese Chess for Terminal is a networked Chinese chess game designed to run in a terminal environment. It features:

- **Two Game Modes**:
  - **Offline Mode**: Single computer, local multiplayer
  - **Online Mode**: Network-based gameplay via WebSocket connection (LAN/VPN/Docker)
  
- **Debug Mode**: Special mode allowing free chessman movement without turn restrictions (Press 'D')

- **Modern Architecture**: Built with C++14, using professional terminal UI (FinalCut), WebSocket++ for networking, and Google Test for testing

- **Cross-Platform Support**: Runs on x86_64 (Intel/AMD) and ARM64 (Apple Silicon, ARM servers, Raspberry Pi 4+)

### Technology Stack

| Component | Technology | Purpose |
|-----------|-----------|---------|
| UI Framework | FinalCut | Terminal-based GUI rendering |
| Networking | WebSocket++ | Real-time game state synchronization |
| JSON Handling | nlohmann/json | Data serialization/deserialization |
| Testing | Google Test | Unit and integration testing |
| Build System | CMake 3.14+ | Cross-platform build management |
| C++ Standard | C++14 | Core language standard |

---

## Architecture

### High-Level Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                    PRESENTATION LAYER (UI)                      │
│  MainDialog → IntroDialog → ConfigDialog → BoardDialog          │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│                    APPLICATION LAYER                            │
│  MoveManager ← → Umpire ← → Transfer ← → ConnectionBase         │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│                    BUSINESS LOGIC LAYER                         │
│  Board (IBoard) ← → Chessman (IChessman) ← → Rule               │
└────────────────────────┬────────────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────────────┐
│                    UTILITY LAYER                                │
│  Utils ← → Point ← → Constant ← → Log                           │
└─────────────────────────────────────────────────────────────────┘
```

### Module Organization

```
Chinese-Chess/
├── logic/              # Game board and piece logic (MVC Model)
│   ├── inc/
│   │   ├── iBoard.h           # Board interface
│   │   ├── board.h            # Board implementation
│   │   ├── iChessman.h        # Chessman interface
│   │   ├── chessman.h         # Chessman implementation
│   │   └── umpire.h           # Game rules enforcement
│   └── src/
│
├── rule/               # Chess movement rules (Strategy pattern)
│   ├── inc/
│   │   ├── rule.h             # Rule service interface
│   │   ├── abstractRuleBuilder.h
│   │   ├── ruleShapeBuilder.h # Defines piece movement shapes
│   │   └── ruleTargetBuilder.h# Defines valid targets
│   └── src/
│
├── ui/                 # User Interface (Observer pattern)
│   ├── inc/
│   │   ├── mainDialog.h       # Main window container
│   │   ├── introDialog.h      # Intro/splash screen
│   │   ├── configDialog.h     # Mode selection
│   │   ├── boardDialog.h      # Game board UI
│   │   ├── moveManager.h      # Move orchestrator
│   │   └── iDialogChain.h     # Dialog state pattern
│   ├── label/                 # UI components
│   ├── selection/             # Selection UI components
│   ├── turn/                  # Turn indicator UI
│   └── src/
│
├── websockpp/          # Network communication
│   ├── inc/
│   │   ├── connectionBase.h   # Abstract connection interface
│   │   ├── server.h           # Server implementation
│   │   ├── client.h           # Client implementation
│   │   ├── transfer.h         # Move protocol handler
│   │   └── wConfig.h          # WebSocket configuration
│   └── src/
│
├── utils/              # Shared utilities
│   ├── inc/
│   │   ├── utils.h            # Helper functions
│   │   ├── point.h            # 2D coordinate system
│   │   ├── constant.h         # Enums and constants
│   │   └── log.h              # Logging system
│   └── src/
│
└── final/              # FinalCut library headers (included)
```

---

## Core Modules

### 1. Logic Module - Board & Pieces

#### IBoard Interface & Board Implementation

**File**: [logic/inc/iBoard.h](../logic/inc/iBoard.h)

```cpp
class IBoard {
    // Check if position is occupied
    virtual bool isOccupied(int x, int y) = 0;
    virtual bool isOccupied(Point *point) = 0;
    
    // Get chessman at position
    virtual IChessman* getChessman(int x, int y) = 0;
    virtual IChessman* getChessman(Point *point) = 0;
    
    // Move piece from one position to another
    virtual void move(Point* from, Point* to) = 0;
    
    // Get all possible moves for a piece
    virtual std::vector<Point*> getPossibleMoves(Point* target) = 0;
    
    // Track general (king) location for check detection
    virtual Point* getGeneralLocation(team_code team) = 0;
    virtual void setGeneralLocation(team_code team, Point* location) = 0;
    
    // Game end handling
    virtual void endGame(team_code winningTeam) = 0;
    
protected:
    IChessman* map[BOARD_WIDTH][BOARD_LENGTH];  // 10x9 Chinese chess board
    bool isGameOver;
    team_code winningTeam;
};
```

**Board Implementation** (`logic/src/board.cpp`):
- **Singleton Pattern**: Only one board instance exists in the game
- **Setup Method**: Initializes all 30 pieces in their starting positions
- **Move Validation**: Delegates to Rule module for valid move calculation
- **General Tracking**: Maintains location of both generals for check detection

#### IChessman Interface & Chessman Implementation

**File**: [logic/inc/iChessman.h](../logic/inc/iChessman.h)

```cpp
class IChessman {
    // Get possible moves without board context
    virtual std::vector<Point*> getPossibleMoves() = 0;
    
    // Get possible moves considering board state
    virtual std::vector<Point*> getPossibleMoves(IBoard* board) = 0;
    
    // Execute move to new position
    virtual bool move(Point* point) = 0;
    
    // Get piece attributes
    virtual team_code getTeam() = 0;           // RED or BLACK
    virtual chessman_code getCode() = 0;       // GENERAL, SOLDIER, etc.
    virtual string getName() = 0;              // Display name
    
    // Factory method for creating pieces
    static IChessman* newInstance(Piece piece, Point *point);
    
protected:
    Point* slot;                // Current position
    Piece piece;                // Type and team info
};
```

**Chessman Types** (8 types, 30 total pieces):

| Chessman | Red | Black | Movement Rules |
|----------|-----|-------|-----------------|
| General | 1 | 1 | Moves 1 step horizontally/vertically within fortress |
| Advisor | 2 | 2 | Moves 1 step diagonally within fortress |
| Elephant | 2 | 2 | Moves 2 steps diagonally (cannot cross river) |
| Horse | 2 | 2 | Moves like chess knight but can be blocked |
| Chariot | 2 | 2 | Moves horizontally/vertically any distance |
| Cannon | 2 | 2 | Moves like chariot, captures by jumping over 1 piece |
| Soldier | 5 | 5 | Moves forward 1 step (backward after crossing river) |

#### Umpire Class - Game Rules Enforcement

**File**: [logic/inc/umpire.h](../logic/inc/umpire.h)

```cpp
class Umpire {
    // Check if move would leave general in check
    bool preCheckMate(Point* from, Point* to);
    bool preCheckMate(Point* from, Point* to, team_code team);
    
    // Get all positions that attack the general
    std::vector<Point*> checkMate(void);
    std::vector<Point*> checkMate(team_code team);
    
    // Process checkmate logic
    std::vector<Point*> processCheckMate(team_code team);
};
```

**Responsibilities**:
- Validates moves don't leave own general in check
- Detects checkmate conditions
- Enforces check restrictions (general must escape check)

---

### 2. Rule Module - Movement Validation

**File**: [rule/inc/rule.h](../rule/inc/rule.h)

The Rule module uses the **Builder Pattern** to calculate valid moves:

```cpp
class Rule {
    // Fluent builder interface
    static RuleTargetBuilder create(IBoard *_board);
    
    Point* getTarget();
    vector<Point*>* getPossibleMove();
    IBoard* getIBoard();
    
private:
    Point* target;
    vector<Point*> possibleMoves;
    IBoard* board;
};
```

**RuleShapeBuilder** - Defines movement shapes:
- Calculates base movement pattern (e.g., chariot moves in 4 directions)
- Returns raw moves without target validation

**RuleTargetBuilder** - Validates targets:
- Applies board boundaries
- Checks for obstacles
- Validates team-specific rules (e.g., elephant can't cross river)
- Removes friendly pieces from valid targets

**Usage Example**:
```cpp
vector<Point*> moves = Rule::create(board)
    .at(targetPoint)
    .forChessman(chessman)
    .build()
    ->getPossibleMove();
```

---

### 3. UI Module - FinalCut-Based Interface

**File**: [ui/inc/mainDialog.h](../ui/inc/mainDialog.h)

The UI is built as a **State Machine** using the **Chain of Responsibility Pattern**:

```
MainDialog
├── IntroDialog (Intro screen with animations)
├── ConfigDialog (Mode and connection selection)
└── BoardDialog (Actual game board)
```

#### MainDialog - Application Entry Point

```cpp
class MainDialog : public FDialog {
    explicit MainDialog(FWidget* parent = nullptr);
    void initLayout() override;
    
private:
    IntroDialog *introDialog;      // 90s-style intro with animations
    ConfigDialog* configDialog;    // Mode selection (Offline/Online)
    BoardDialog *boardDialog;      // Game board
};
```

**FinalCut Framework**:
- **FDialog**: Base dialog class
- **FWidget**: Base widget class for UI components
- **FApplication**: Main application class
- **FColor**: Terminal color support
- **FEvent**: Keyboard/mouse event handling

#### IntroDialog - Intro Screen

**File**: [ui/inc/introDialog.h](../ui/inc/introDialog.h)

```cpp
class IntroDialog: public IDialogChain {
    void onTimer(FTimerEvent* event) override;        // Animation timer
    void onKeyPress(FKeyEvent*) override;              // Skip on key press
    void onMouseDown(FMouseEvent* event) override;     // Skip on mouse click
};
```

Features:
- 90s retro-style animation
- Skippable via keyboard or mouse
- Timer-based animation updates

#### ConfigDialog - Configuration Screen

**File**: [ui/inc/configDialog.h](../ui/inc/configDialog.h)

```cpp
class ConfigDialog: public IDialogChain {
    void okCallback();          // Proceed to game
    void backCallback();        // Return to intro
    void onKeyPress(FKeyEvent*) override;
    void onTimer(FTimerEvent* event) override;

private:
    FButton ok{"Next &>", this};
    FButton back{"&< Back", this};
    SelectableChain* currentSelection;
    ModeSelection* modeSelection;         // Offline/Online mode
    WaitableChain* serverWaitableChain;   // Server IP display
    WaitableChain* clientWaitableChain;   // Client IP input
};
```

**Mode Selection Flow**:
1. Select Offline or Online mode
2. If Online:
   - If Server: Display IP address, wait for connection
   - If Client: Input server IP address
3. Proceed to game board

#### BoardDialog - Game Board UI

**File**: [ui/inc/boardDialog.h](../ui/inc/boardDialog.h)

```cpp
class BoardDialog: public IDialogChain {
    friend class MoveManager;
    
    explicit BoardDialog(FDialog* parent);
    void initLayout() override;
    void clickedCallback();         // Handle piece click
    void moveCallback();            // Handle piece move
    void dispatchChessmanMove(Point* source, Point* destination);
    
private:
    void addCallback(ILabel* label, std::string event);
    
    IBoard* board;
    MoveManager* moveManager;
    
    // UI Components
    RiverBorderLabels riverBoundaryLabels;
    FortressLabels fortressLabels;
    VerticleLineLabels verticleLineLabels;
    HorizontalLineLabels horizontalLineLabels;
    TeamSignalLabels *teamSignalLabels;
    ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];
};
```

**Board Layout**:
```
        0   1   2   3   4   5   6   7   8
    ┌───┬───┬───┬───┬───┬───┬───┬───┬───┐
 0  │   │   │   │   │G  │   │   │   │   │  RED General
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 1  │   │   │   │   │   │   │   │   │   │
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 2  │   │   │   │   │   │   │   │   │   │  RED Start
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 3  │   │   │   │   │   │   │   │   │   │
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 4  │   │   │───────────┼───────────   │   │  RIVER (blocking line)
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 5  │   │   │   │   │   │   │   │   │   │
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 6  │   │   │   │   │   │   │   │   │   │  BLACK Start
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 7  │   │   │   │   │   │   │   │   │   │
    ├───┼───┼───┼───┼───┼───┼───┼───┼───┤
 8  │   │   │   │   │G  │   │   │   │   │  BLACK General
    └───┴───┴───┴───┴───┴───┴───┴───┴───┘
        Fortress (3x3 at positions [0-2,0-2], [6-8,7-9])
```

**Color Scheme**:
```cpp
BLACK_BG = FColor::Black
FOCUS_BLACK_BG = FColor::Grey50              // Selected piece
POTENTIAL_BLACK_BG = FColor::DeepPink6       // Valid move targets
POTENTIAL_GENERAL_BLACK_BG = FColor::DarkCyan2  // General safe moves

RED_BG = FColor::Red
FOCUS_RED_BG = FColor::Red1
POTENTIAL_RED_BG = FColor::LightPink4
POTENTIAL_GENERAL_RED_BG = FColor::LightCyan3
```

---

### 4. MoveManager - Game Flow Orchestrator

**File**: [ui/inc/moveManager.h](../ui/inc/moveManager.h)

```cpp
class MoveManager {
    // Source and destination management
    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    void setDestPoint(Point* dest);
    Point* getDestPoint();
    
    // UI decoration (highlighting)
    void decorateTargetedPieces(bool value);    // Highlight selected piece
    void decoratePotentialPieces(bool value);   // Highlight valid moves
    
    // Move execution
    bool movePiece(bool isNotify);              // Execute move with validation
    
    // Calculation
    void calculatePossiblePotentials();         // Find capturable pieces
    bool preCalculatePossiblePotentials();      // Pre-move validation
    void calculatePossibleMoves(bool isNotify); // Find valid moves
    
    // Network callbacks
    void movePieceTransferCb(Point* from, Point* to);
    void selPieceTransferCb(Point* from);
    
    void setConnectionInstance(ConnectionBase *con);

private:
    IBoard* board;
    Umpire* umpire;
    BoardDialog* mainDialog;
    Point* source;              // Currently selected piece
    Point* dest;                // Target destination
    vector<Point*> possibleMoves;           // Valid moves for selected piece
    vector<Point*> possiblePotentials;      // Pieces that can be captured
};
```

**MoveManager State Machine**:
1. User clicks piece → `setSourcePoint()`
2. Manager highlights piece and calculates valid moves → `calculatePossibleMoves()`
3. User clicks target → `setDestPoint()`
4. Manager validates move → `movePiece()`
5. If online mode: send move to opponent → `Transfer::sendMsg()`
6. Update board state and switch turns

---

### 5. WebSocket Network Module

#### ConnectionBase - Abstract Connection Interface

**File**: [websockpp/inc/connectionBase.h](../websockpp/inc/connectionBase.h)

```cpp
enum connection_type {
    WSERVER,      // Acts as game host
    WCLIENT,      // Connects to host
    NON_CONNECTION // Offline mode
};

class ConnectionBase {
    // Singleton management
    static ConnectionBase* setInstance(connection_type type);
    static ConnectionBase* getInstance();
    
    // Communication
    virtual void run() = 0;                              // Start connection
    int send(json const js);                             // Send JSON message
    void setRecvCallback(ConnectionBaseCallback cb);     // Set receive handler
    
    virtual int _send(std::string const payload) = 0;    // Implementation
    string _recv(void);
    
protected:
    static ConnectionBase* instance;
    std::thread wThread;
    connection mConnection;           // WebSocket++ connection
    ConnectionBaseCallback mCallback;  // Callback on message receive
    bool mIsConnected;
};
```

**Factory Pattern Implementation**:
```cpp
ConnectionBase* conn = ConnectionBase::setInstance(WCLIENT);
// Returns appropriate implementation: Server or Client
```

#### Server & Client Implementations

**Server** (`websockpp/src/server.cpp`):
- Listens on configurable port (default 9002)
- Accepts single client connection
- Displays IP address for client to connect
- Synchronizes game state with client

**Client** (`websockpp/src/client.cpp`):
- Connects to server IP
- Sends and receives game state updates
- Waits for connection confirmation

#### Transfer - Move Protocol Handler

**File**: [websockpp/inc/transfer.h](../websockpp/inc/transfer.h)

```cpp
enum trans_code {
    MOV,    // Move piece
    SEL,    // Select piece (for highlighting)
    TOTAL_CODE
};

class Transfer {
    Transfer(ConnectionBase *connection);
    
    // Send operations
    void sendMsg(trans_code opcode, Point *from, Point *to);  // MOV
    void sendMsg(trans_code opcode, Point *from);              // SEL
    
    // Receive and dispatch
    void setCallback(MovCallback_t mcb, SelCallback_t scb);
    void dispatchMsg(json js);  // Route to appropriate callback
    
private:
    ConnectionBase *mConnection;
    MovCallback_t mMovCallback;     // Handle remote move
    SelCallback_t mSelCallback;     // Handle remote selection
};
```

**JSON Message Format**:
```json
// Move message
{
    "op": "MOV",
    "from": {"x": 0, "y": 0},
    "to": {"x": 1, "2": 1}
}

// Selection message
{
    "op": "SEL",
    "from": {"x": 0, "y": 0}
}
```

---

## Function Call Flow

### 1. Application Startup Flow

```
main.cpp
  ↓
FApplication::app(argc, argv)
  ↓
app.initTerminal()  // Initialize FinalCut terminal
  ↓
MainDialog::MainDialog(app)
  ├→ IntroDialog::IntroDialog()
  ├→ ConfigDialog::ConfigDialog()
  └→ BoardDialog::BoardDialog()
  ↓
app.exec()  // Enter event loop
```

### 2. Game Initialization Flow

```
MainDialog::initLayout()
  ↓
IntroDialog::initLayout()  // Show intro screen
  ├→ animation timers
  └→ wait for key/mouse press
  ↓
ConfigDialog::initLayout()  // Mode selection
  ├→ Show Offline/Online radio buttons
  ├→ If Online:
  │   ├→ ConnectionBase::setInstance(WSERVER or WCLIENT)
  │   ├→ ConnectionBase::getInstance()->run()  // Start connection thread
  │   └→ Wait for connection
  └→ on "Next" button: proceed to BoardDialog
  ↓
BoardDialog::initLayout()
  ├→ Board::getInstance()  // Create/get board singleton
  ├→ Board::setup()  // Initialize all 30 chess pieces
  ├→ Create UI labels for board grid
  ├→ Create UI labels for pieces
  ├→ MoveManager::MoveManager()  // Create move orchestrator
  └→ Register callbacks for piece clicks
```

### 3. Move Execution Flow (Offline Mode)

```
User clicks piece at (2, 0)
  ↓
BoardDialog::clickedCallback()
  ├→ Emit "clicked" event
  └→ FLabel::clicked signal
  ↓
MoveManager::setSourcePoint(Point(2, 0))
  ├→ source = Point(2, 0)
  └→ decorateTargetedPieces(true)  // Highlight selected piece
  ↓
MoveManager::calculatePossibleMoves(false)  // false = don't notify network
  ├→ IChessman* piece = board->getChessman(source)
  ├→ vector<Point*> moves = piece->getPossibleMoves(board)
  │   ├→ Rule::create(board).at(source).forChessman(piece).build()
  │   └→ Rule returns valid moves considering board state
  ├→ Umpire::preCheckMate() validation (for general moves)
  ├→ decoratePotentialPieces(true)  // Highlight valid destinations
  └→ Store in possibleMoves vector
  ↓
User clicks destination at (3, 0)
  ↓
BoardDialog::moveCallback()
  ├→ Emit "move" event
  └→ FLabel::move signal
  ↓
MoveManager::setDestPoint(Point(3, 0))
  ├→ dest = Point(3, 0)
  └→ Check if dest in possibleMoves
  ↓
MoveManager::movePiece(false)
  ├→ Validate move is in possibleMoves
  ├→ IChessman* capturedPiece = board->getChessman(dest)
  ├→ board->move(source, dest)  // Execute move
  │   └→ map[dest.x][dest.y] = map[source.x][source.y]
  │   └→ map[source.x][source.y] = nullptr
  ├→ Update UI labels (remove from source, add to dest)
  ├→ Check for game over condition
  ├→ Switch turns (update team indicator)
  └→ Return true
  ↓
Switch to next player's turn
```

### 4. Move Execution Flow (Online Mode)

```
[Server] User clicks piece
  ↓
MoveManager::movePiece(true)  // true = notify network
  ├→ Execute local move (same as offline)
  └→ Transfer::sendMsg(MOV, source, dest)
  ↓
Transfer::sendMsg(MOV, source, dest)
  ├→ Create JSON: {"op": "MOV", "from": {...}, "to": {...}}
  └→ ConnectionBase::send(json)
  ↓
ConnectionBase::send(json)
  ├→ Convert JSON to string
  └→ _send(string) → WebSocket++ sends to client
  ↓
[Client] WebSocket message received
  ↓
ConnectionBase::onMessage(msg)
  ├→ Parse JSON from message
  └→ Call mCallback(json)  // Invoke Transfer's callback
  ↓
Transfer::dispatchMsg(json)
  ├→ Check opcode (MOV or SEL)
  ├→ if MOV: call mMovCallback(from, to)
  └→ if SEL: call mSelCallback(from)
  ↓
MoveManager::movePieceTransferCb(from, to)
  ├→ Execute remote move locally
  ├→ Update UI
  └→ Switch turns
```

### 5. Network Initialization Flow

```
ConfigDialog::okCallback()
  ├→ Read mode selection (Offline/Online/Debug)
  ├→ If Online:
  │   ├→ ConnectionBase::setInstance(WSERVER or WCLIENT)
  │   ├→ ConnectionBase::getInstance()
  │   ├→ conn->run()  // Start in separate thread
  │   └→ Transfer::setCallback(moveCb, selCb)
  └→ Proceed to BoardDialog
  ↓
ConnectionBase::run()  [In separate thread]
  ├→ Initialize WebSocket++ endpoint
  ├→ If Server:
  │   ├→ Listen on port 9002
  │   ├→ Display IP address
  │   └→ Accept incoming connection
  └→ If Client:
      ├→ Connect to provided IP:9002
      └→ Wait for confirmation
  ↓
On connection established:
  ├→ mIsConnected = true
  ├→ Start message receive loop
  └→ Listen for incoming game messages
```

### 6. Piece Movement Calculation Flow

```
MoveManager::calculatePossibleMoves(target)
  ↓
IBoard::getPossibleMoves(target)
  ├→ IChessman* piece = board->getChessman(target)
  └→ piece->getPossibleMoves(board)
  ↓
Chessman::getPossibleMoves(board)
  ├→ Rule::create(board).at(target).forChessman(this).build()
  ↓
RuleShapeBuilder (Chain of Responsibility)
  ├→ Get chessman type and team
  ├→ Apply shape rules:
  │   ├→ General: 1 step orthogonal within fortress (3x3)
  │   ├→ Advisor: 1 step diagonal within fortress
  │   ├→ Elephant: 2 steps diagonal, can't cross river
  │   ├→ Horse: Knight-like move, can be blocked
  │   ├→ Chariot: Orthogonal any distance
  │   ├→ Cannon: Orthogonal any distance, capture by jumping
  │   └→ Soldier: Forward 1 step (backward after river)
  └→ Return base moves (may include friendly pieces/obstacles)
  ↓
RuleTargetBuilder (Decorator pattern)
  ├→ Filter out-of-bounds moves
  ├→ Remove friendly pieces
  ├→ Apply team restrictions (elephant river, soldier etc)
  ├→ Check for obstacles (horse can be blocked)
  ├→ Handle capture logic (cannon must jump)
  └→ Return valid destination points
  ↓
Umpire::preCheckMate() [General moves only]
  ├→ Simulate move (from, to, team)
  ├→ Check if general would be in check after move
  └→ Remove move if it leaves general exposed
  ↓
Return vector<Point*> possibleMoves
```

---

## Component Interactions

### Diagram: Full Game Session

```
┌──────────────┐
│  FApplication│
└──────┬───────┘
       │
       ├─────────────────────────────────────┐
       │                                     │
  ┌────▼────────┐                  ┌────────▼────────┐
  │ MainDialog  │                  │   FinalCut UI   │
  └──┬───────┬──┘                  │   Framework     │
     │       │                     └─────────────────┘
     ├──────▼────────┐
     │ IntroDialog   │
     ├──────┬────────┤
     │      └──────────────────┐
     ├──────▼────────┐         │
     │ ConfigDialog  │         │
     ├──────┬────────┤         │
     │      │        │         │
  ┌──┴──────▼─┐ ┌────▼──────┐  │
  │ConnectionB│ │ Transfer  │  │
  │   ase     │ │           │  │
  └──┬──────┬─┘ └────▲──────┘  │
     │      │        │         │
  ┌──▼──┐ ┌─▼─────┐  │         │
  │Server│ │Client │  │(callback)
  └──────┘ └───────┘  │         │
           WebSocket  │         │
                      │         │
     ├──────▼────────┐│         │
     │ BoardDialog   ├┘         │
     ├──────┬────────┘          │
     │      │                   │
  ┌──┴──────▼───────┐           │
  │  MoveManager    │           │
  ├──┬─────────┬────┤           │
  │  │    │    │    │           │
  ├──▼─┐ ┌─▼──▼┐  │ ├──────────┘
  │Umpire │Rule  │ │
  └──────┘└──────┘ │
     │             │
  ┌──▼─────────────▼──┐
  │  Board (Singleton) │
  ├─────┬─────────────┤
  │ map │  map[10][9] │
  │     │  Contains   │
  │     │  IChessman  │
  │     │  pointers   │
  └──┬──┴──────────────┘
     │
  ┌──▼─────────────────┐
  │    Chessman[][]     │
  │  (30 pieces total)  │
  └─────────────────────┘
```

### Data Flow: Message Passing

```
User Action (click)
  │
  └─→ FinalCut Event System
       │
       └─→ BoardDialog::onMouseDown/onClick
            │
            ├─→ MoveManager::setSourcePoint/setDestPoint
            │    │
            │    ├─→ Board::getChessman()
            │    ├─→ Rule::calculate()
            │    └─→ Umpire::validate()
            │
            └─→ MoveManager::movePiece()
                 │
                 ├─→ Board::move()
                 ├─→ UI update (redraw pieces)
                 │
                 └─→ (if online) Transfer::sendMsg()
                      │
                      └─→ ConnectionBase::send()
                           │
                           └─→ WebSocket++ → Network
```

---

## Game Logic

### Board Coordinate System

```
BOARD_WIDTH = 10 (x-axis, 0-9)
BOARD_LENGTH = 9 (y-axis, 0-8)

Point(x, y) where:
- x: 0-9 (left to right)
- y: 0-8 (top to bottom)

River: y = 4 (separates RED side 0-4 and BLACK side 5-8)
Fortress: 3x3 area at:
- RED: (0-2, 0-2) and (6-8, 0-2)
- BLACK: (0-2, 6-8) and (6-8, 6-8)
```

### Piece Starting Positions

**RED Team (top side)**:
```
y=0:  C H E A G A E H C    (Chariot, Horse, Elephant, Advisor, General, Advisor, Elephant, Horse, Chariot)
      0 1 2 3 4 5 6 7 8

y=2:  S   S   S   S   S    (Soldiers at x=0,2,4,6,8)
y=3:      Cn          Cn    (Cannons at x=1,7)
```

**BLACK Team (bottom side)**:
```
y=6:      Cn          Cn    (Cannons at x=1,7)
y=7:  S   S   S   S   S    (Soldiers at x=0,2,4,6,8)

y=8:  C H E A G A E H C    (Same as RED)
      0 1 2 3 4 5 6 7 8
```

### Turn Management

```
Active Player:
- Can select and move own pieces
- Cannot move during opponent's turn

Turn Switch:
1. Move executed successfully
2. Board validates move
3. Update turn indicator
4. Switch to opponent
5. (if online) Send move notification
6. Wait for opponent's move

Game Over Conditions:
- General captured (MVP - currently implemented)
- Checkmate (future: to be implemented)
- Forfeit
```

### Check & Checkmate Logic

**Umpire::preCheckMate()** validates that:
1. Selected piece is not moving the general into check
2. If general is in check, only moves that escape check are allowed
3. After move, general must not be in check

**Check Detection**:
- Simulates move from→to
- Finds general location
- Tests if any opponent piece can attack general
- If yes, move is invalid

### Capture Logic

**Regular Pieces**: Captured when move destination = opponent piece location

**Cannon**: Special capture rules
- Moves like chariot (orthogonal)
- Captures by jumping over exactly 1 piece
- Cannot capture without jumping piece in between

---

## UI Framework

### FinalCut Features Used

| Feature | Purpose |
|---------|---------|
| FDialog | Main container for game screens |
| FButton | Interactive buttons (Next, Back, etc) |
| FLabel | Display board pieces and grid |
| FRadioButton | Mode selection (Offline/Online) |
| FLineEdit | Input fields (IP address) |
| FColorPalette | Terminal color management |
| Event System | Mouse clicks, keyboard input |
| Timer | Animation and UI updates |

### Dialog Chain Pattern

The game uses a state machine where only one dialog is active:

```
IntroDialog → ConfigDialog → BoardDialog
   (Intro)    (Config)      (Game)
     ↑                         │
     └─────── Back ────────────┘
```

Each dialog:
1. Inherits from `IDialogChain`
2. Implements `initLayout()` for UI setup
3. Implements `initHook()` for post-setup logic
4. Handles navigation to next dialog

### Color Management

```cpp
enum FColor {
    Black, Red, DarkCyan, DarkMagenta,
    DarkBlue, Brown, DarkGreen, Grey,
    Grey50, Red1, DarkCyan2, DeepPink6,
    LightPink4, LightCyan3, Default,
    // ... 250+ colors available
};
```

---

## Network Communication

### Online Game Flow

```
Server (Red Player)              Network               Client (Black Player)
       │                                                      │
       ├─ Listen on 0.0.0.0:9002                            │
       ├─ Display IP: 192.168.1.100                         │
       │                                                      │
       │  Waits for connection ◄──────────────────────────── Connect to 192.168.1.100:9002
       │                                                      │
       ├──────────────────────────────────────────────────→  Connection established
       │                                                      │
       │  Game starts, Red to move                           │
       │                                                      │
       │  User makes move                                    │
       │  {"op":"MOV", "from":{x:1,y:0}, "to":{x:1,y:2}}   │
       ├──────────────────────────────────────────────────→  Receive move
       │                                                      ├─ Validate move
       │                                                      ├─ Update board
       │                                                      └─ Render UI
       │                                                      │
       │  Black's turn                                       │
       │                                                      │  User makes move
       │  Receive move ◄─ {"op":"MOV", "from":{x:1,y:8}    │
       │  ├─ Validate                                        │
       │  ├─ Update board                                    │
       │  └─ Render UI                                       │
       │                                                      │
       │  Continue until game over...                        │
```

### Connection State Machine

```
Offline:
  NON_CONNECTION → Game Ready

Server:
  UNCONNECTED → LISTENING → CONNECTED → GAME → DISCONNECTED

Client:
  UNCONNECTED → CONNECTING → CONNECTED → GAME → DISCONNECTED
```

---

## Build System

### CMake Structure

```cmake
cmake_minimum_required(VERSION 3.14)
project(chinese-chess)

# Dependencies
find_package(Boost)
include(FetchContent)
FetchContent_Declare(
    googletest       # Unit testing
    websocketpp      # WebSocket++
    json             # nlohmann/json
)

# Source collection
file(GLOB UTILS_SOURCES "utils/src/*.cpp")
file(GLOB LOGIC_SOURCES "logic/src/*.cpp")
file(GLOB RULE_SOURCES "rule/src/*.cpp")
file(GLOB UI_SOURCES "ui/src/*.cpp")
file(GLOB WEBSOCKPP_SOURCES "websockpp/src/*.cpp")

# Main executable
add_executable(chinese-chess ${ALL_SOURCES})
target_link_libraries(chinese-chess
    PRIVATE finalcut boost_system nlohmann_json::nlohmann_json
)

# Tests
add_executable(mainTest test/*.cc)
target_link_libraries(mainTest gtest_main ${libraries})
add_test(NAME mainTest COMMAND mainTest)
```

### Build Targets

```bash
make build              # Build release
make build-debug        # Build debug with symbols
make clean              # Remove build artifacts
make test               # Run all tests
make run                # Execute game
make setup              # Full setup (deps + build)
cmake --build build     # Direct cmake build
```

### Compiler Configuration

```cmake
C++ Standard: C++14
Debug Flags: -g -O0 -Wall -Wextra
Release Flags: -O3 -DNDEBUG
Threading: -pthread
```

---

## Key Design Patterns

| Pattern | Used In | Purpose |
|---------|---------|---------|
| **Singleton** | Board | Single game board instance |
| **Factory** | Chessman, ConnectionBase | Object creation abstraction |
| **Strategy** | Rule, RuleBuilder | Different move calculation strategies |
| **Builder** | Rule | Fluent interface for move calculation |
| **Observer** | MoveManager, UI events | Loose coupling between UI and logic |
| **Chain of Responsibility** | Dialog chain, Rule processing | Sequential processing pipeline |
| **Adapter** | Transfer | Adapt board events to network messages |
| **State** | Game states (Intro→Config→Game) | State machine for dialogs |

---

## Summary

This Chinese Chess game is a well-architected terminal-based application featuring:

✅ **Clean Architecture**: Separated concerns (UI, Logic, Network, Utils)
✅ **Design Patterns**: Professional use of proven patterns
✅ **Extensible**: Easy to add new features
✅ **Testable**: Unit tests with Google Test framework
✅ **Networked**: Real-time multiplayer via WebSocket
✅ **Cross-Platform**: Supports x86_64 and ARM64
✅ **User-Friendly**: Intuitive terminal UI with FinalCut

The codebase demonstrates professional C++ development practices with proper abstraction layers, component isolation, and maintainable code organization.
