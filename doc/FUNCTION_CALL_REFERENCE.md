# Chinese Chess - Detailed Function Call Reference

## Table of Contents
1. [Core Classes & Methods](#core-classes--methods)
2. [Function Call Sequences](#function-call-sequences)
3. [Callback System](#callback-system)
4. [Data Flow Diagrams](#data-flow-diagrams)

---

## Core Classes & Methods

### IBoard / Board (Singleton Pattern)

**Location**: `logic/inc/iBoard.h`, `logic/src/board.cpp`

```cpp
class IBoard {
    // Board state checking
    bool isOccupied(int x, int y);
    bool isOccupied(Point *point);
    // Check if a position has a piece
    // Returns: true if occupied, false if empty
    
    // Piece retrieval
    IChessman* getChessman(int x, int y);
    IChessman* getChessman(Point *point);
    // Get piece at position
    // Returns: IChessman* pointer or nullptr
    
    // Move execution
    void move(Point* from, Point* to);
    // Move piece from one position to another
    // Side effects:
    //   - Captures piece at destination (if exists)
    //   - Updates map array
    //   - Updates general location if moving general
    
    // Move calculation
    std::vector<Point*> getPossibleMoves(Point* target);
    // Calculate all valid moves for piece at target
    // Returns: vector of valid destination points
    // Process:
    //   1. Get chessman at target
    //   2. Call Rule builder for move calculation
    //   3. Filter moves considering board state
    //   4. Return valid moves
    
    // General (King) tracking
    Point* getGeneralLocation(team_code team);
    void setGeneralLocation(team_code team, Point* location);
    // Track general positions for check detection
    
    // Game state
    void endGame(team_code winningTeam);
    // Called when game ends (MVP: general captured)

protected:
    IChessman* map[BOARD_WIDTH][BOARD_LENGTH];  // 10x9 board
    bool isGameOver;
    team_code winningTeam;
};

class Board : public IBoard {
    static IBoard* getInstance();
    // Get singleton instance
    // Pattern:
    //   First call: creates instance and initializes board
    //   Subsequent calls: return existing instance
    // Returns: IBoard* pointing to Board singleton
    
    Board(IBoard *t);  // Private constructor
    
private:
    static IBoard* instance;
    void setup();
    // Initialize board with 30 chess pieces
    // Called in constructor
    // Creates: General, Advisor, Elephant, Horse, Chariot, Cannon, Soldier
    
    Point* generalLocation[TEAM_SIZE];  // [RED, BLACK]
};
```

**Usage Example**:
```cpp
IBoard* board = Board::getInstance();

// Check if position occupied
if (board->isOccupied(3, 0)) {
    IChessman* piece = board->getChessman(3, 0);
}

// Get possible moves
vector<Point*> moves = board->getPossibleMoves(new Point(0, 0));

// Execute move
board->move(from, to);
```

---

### IChessman / Chessman (Factory Pattern)

**Location**: `logic/inc/iChessman.h`, `logic/src/chessman.cpp`

```cpp
class IChessman {
    // Get possible moves
    std::vector<Point*> getPossibleMoves();
    // Without board context (abstract moves)
    // Returns: theoretical moves ignoring obstacles
    
    std::vector<Point*> getPossibleMoves(IBoard* board);
    // With board context (validated moves)
    // Returns: actual valid moves considering board state
    // Process:
    //   1. Calls Rule::create(board).at(position).forChessman(this)
    //   2. Rule applies shape and target validation
    //   3. Returns filtered moves
    
    // Move execution
    bool move(Point* point);
    // Move this piece to new position
    // Returns: true if successful, false otherwise
    
    // Piece identification
    team_code getTeam();          // RED or BLACK
    chessman_code getCode();       // GENERAL, ADVISOR, etc.
    string getName();              // "Red General", "Black Soldier", etc.
    
    // Factory method
    static IChessman* newInstance(Piece piece, Point *point);
    // Create appropriate chessman subclass based on Piece type
    // Parameters:
    //   piece: {chessman_code, team_code}
    //   point: starting position
    // Returns: Pointer to created Chessman object

protected:
    Point* slot;
    Piece piece;
};

class Chessman : public IChessman {
    Chessman(Piece piece, Point *point);
    // Constructor
    // Initializes piece with type, team, and position
    
    ~Chessman();
    // Destructor
    // Cleanup (currently minimal)
    
    // Implement all virtual methods from IChessman
    // Delegates move calculation to Rule system
};
```

**Piece Types** (chessman_code enum):

| Code | Name | Count | Starting Position |
|------|------|-------|-------------------|
| 0 | GENERAL | 1 per team | (4, 0) and (4, 8) |
| 1 | ADVISOR | 2 per team | (3,0), (5,0) and (3,8), (5,8) |
| 2 | ELEPHANT | 2 per team | (2,0), (6,0) and (2,8), (6,8) |
| 3 | HORSE | 2 per team | (1,0), (7,0) and (1,8), (7,8) |
| 4 | CHARIOT | 2 per team | (0,0), (8,0) and (0,8), (8,8) |
| 5 | CANNON | 2 per team | (1,2), (7,2) and (1,6), (7,6) |
| 6 | SOLDIER | 5 per team | (0,3), (2,3), (4,3), (6,3), (8,3) and (0,5), (2,5), (4,5), (6,5), (8,5) |

**Usage Example**:
```cpp
// Factory creation
Piece redGeneral{GENERAL, RED};
IChessman* piece = IChessman::newInstance(redGeneral, new Point(4, 0));

// Get team and type
team_code team = piece->getTeam();           // RED
chessman_code code = piece->getCode();       // GENERAL
string name = piece->getName();              // "Red General"

// Calculate moves
IBoard* board = Board::getInstance();
vector<Point*> moves = piece->getPossibleMoves(board);
```

---

### Rule / RuleBuilder (Builder Pattern)

**Location**: `rule/inc/rule.h`, `rule/src/rule.cpp`

```cpp
class Rule {
    // Fluent builder interface
    static RuleTargetBuilder create(IBoard *_board);
    // Start building a rule query
    // Returns: RuleTargetBuilder for chaining
    // Example: Rule::create(board).at(target).forChessman(piece).build()
    
    Point* getTarget();
    // Get target position being analyzed
    
    vector<Point*>* getPossibleMove();
    // Get calculated valid moves
    // Returns: pointer to vector of Point*
    
    IBoard* getIBoard();
    // Get associated board

private:
    Point* target;
    vector<Point*> possibleMoves;
    IBoard* board;
};

class RuleShapeBuilder {
    // First stage: Calculate base movement shape
    // Considers:
    //   - Piece type (GENERAL, HORSE, CHARIOT, etc.)
    //   - Piece team
    // Ignores:
    //   - Board obstacles
    //   - Target restrictions
    
    // Returns: Raw moves including friendly pieces
};

class RuleTargetBuilder {
    // Second stage: Validate and filter moves
    // Applies:
    //   - Board boundary checking
    //   - Obstacle detection
    //   - Team-specific rules (elephant can't cross river, etc.)
    //   - Capture logic (cannon must jump)
    
    // Returns: Only valid destination points
};
```

**Fluent Usage Pattern**:
```cpp
// Create rule builder
RuleTargetBuilder builder = Rule::create(board);

// Set target position
builder = builder.at(Point(0, 0));

// Set piece type
builder = builder.forChessman(piece);

// Build and get result
Rule* rule = builder.build();
vector<Point*>* moves = rule->getPossibleMove();
```

**Movement Calculation for Each Piece**:

1. **General (King)**:
   - Shape: 4 directions (up, down, left, right), 1 step
   - Target: Only within fortress (3x3)
   - Fortress: RED(0-2,0-2)/(6-8,0-2), BLACK(0-2,6-8)/(6-8,6-8)

2. **Advisor**:
   - Shape: 4 diagonals, 1 step
   - Target: Only within fortress

3. **Elephant**:
   - Shape: 4 diagonals, 2 steps
   - Target: Cannot cross river (y=4 divides board)
   - Obstacle: Can be blocked by intervening piece

4. **Horse**:
   - Shape: Chess knight-like move
   - Target: No river restriction
   - Obstacle: Can be blocked by adjacent piece

5. **Chariot (Rook)**:
   - Shape: 4 directions (orthogonal), any distance
   - Target: Until obstacle
   - Obstacle: Stops at first obstruction

6. **Cannon**:
   - Shape: 4 directions (orthogonal), any distance
   - Target: Until obstacle or jump piece
   - Special: Must jump exactly 1 piece to capture

7. **Soldier**:
   - Shape: Forward 1 step (backward after crossing river)
   - Target: Varies based on position and team

---

### Umpire (Check Detection)

**Location**: `logic/inc/umpire.h`, `logic/src/umpire.cpp`

```cpp
class Umpire {
    // Validate move doesn't leave general in check
    bool preCheckMate(Point* from, Point* to);
    // Check for current player
    // Parameters:
    //   from: source position
    //   to: destination position
    // Returns: true if move is safe, false if would leave general in check
    // Process:
    //   1. Determine which team is moving
    //   2. Simulate move
    //   3. Find team's general position
    //   4. Check if any opponent piece can attack general
    //   5. Restore board state
    //   6. Return safety status
    
    bool preCheckMate(Point* from, Point* to, team_code team);
    // Check for specific team
    // Same as above but explicitly specify team
    
    // Detect positions attacking the general
    std::vector<Point*> checkMate(void);
    // Get all positions attacking current player's general
    // Returns: vector of attacking piece positions
    
    std::vector<Point*> checkMate(team_code team);
    // Get all positions attacking specified team's general
    // Returns: vector of attacking piece positions
    
    // Advanced checkmate detection
    std::vector<Point*> processCheckMate(team_code team);
    // Comprehensive checkmate analysis
    // Returns: attacking positions and possible escape moves
    
private:
    IBoard *mBoard;
    void setBoard(IBoard* board);
    // Set board reference for validation
};
```

**Check Detection Algorithm**:
```
checkMate(team):
1. Get general location: general_pos = board->getGeneralLocation(team)
2. Iterate all opponent pieces:
   FOR each opponent piece at (x, y):
      valid_moves = board->getPossibleMoves((x, y))
      IF general_pos in valid_moves:
         attacker is checking general, add to result
3. RETURN list of attacking positions
```

**Usage in Move Validation**:
```cpp
Umpire umpire;

// Before accepting move
if (!umpire.preCheckMate(from, to)) {
    // Move leaves general in check - REJECT
    moveAccepted = false;
} else {
    // Move is safe - ACCEPT
    board->move(from, to);
    moveAccepted = true;
}
```

---

### MoveManager (Game Flow Orchestrator)

**Location**: `ui/inc/moveManager.h`, `ui/src/moveManager.cpp`

```cpp
class MoveManager {
    // Source and destination management
    void setSourcePoint(Point* source);
    Point* getSourcePoint();
    // Set/get selected piece position
    
    void setDestPoint(Point* dest);
    Point* getDestPoint();
    // Set/get target move destination
    
    // UI decoration (highlighting)
    void decorateTargetedPieces(bool value);
    // Highlight the selected piece
    // Parameters: true = highlight, false = remove highlight
    // Side effect: Updates UI label colors
    
    void decoratePotentialPieces(bool value);
    // Highlight valid move destinations
    // Parameters: true = highlight, false = remove highlight
    // Side effect: Updates UI label colors
    
    // Move execution
    bool movePiece(bool isNotify);
    // Execute validated move
    // Parameters:
    //   isNotify: true = send to network, false = local only
    // Returns: true if move successful, false if rejected
    // Process:
    //   1. Validate move in possibleMoves list
    //   2. Call board->move(source, dest)
    //   3. Update UI pieces
    //   4. Check game over condition
    //   5. Switch turns
    //   6. (if isNotify) call Transfer::sendMsg()
    
    // Calculation methods
    void calculatePossiblePotentials();
    // Find capturable pieces (for UI highlighting)
    
    bool preCalculatePossiblePotentials();
    // Pre-validate captures before move
    
    void calculatePossibleMoves(bool isNotify);
    // Calculate valid moves for selected piece
    // Parameters:
    //   isNotify: true = send selection to network, false = local only
    // Process:
    //   1. Get piece from board
    //   2. Call board->getPossibleMoves(source)
    //   3. Store in possibleMoves vector
    //   4. Highlight potential moves
    //   5. (if isNotify) call Transfer::sendMsg(SEL, ...)
    
    // Network callbacks
    void movePieceTransferCb(Point* from, Point* to);
    // Callback when remote player moves piece
    // Parameters: remote move coordinates
    // Process:
    //   1. Execute move locally
    //   2. Update board and UI
    //   3. Switch turns
    
    void selPieceTransferCb(Point* from);
    // Callback when remote player selects piece
    // Parameters: remote selection coordinates
    // Side effect: Highlight remote player's selection for visibility
    
    void setConnectionInstance(ConnectionBase *con);
    // Set network connection for sending moves
    
    Transfer *transfer;
    // Network message handler
    
private:
    IBoard* board;                          // Game board
    Umpire* umpire;                         // Check validator
    BoardDialog* mainDialog;                // UI reference
    Point* source;                          // Selected piece
    Point* dest;                            // Move destination
    vector<Point*> possibleMoves;           // Valid destinations
    vector<Point*> possiblePotentials;      // Capturable pieces
};
```

**State Machine**:
```
Idle
  ↓ [User clicks piece]
Source Selected
  ├─ decorateTargetedPieces(true)
  ├─ calculatePossibleMoves(isNotify)
  └─ decoratePotentialPieces(true)
  ↓ [User clicks destination]
Dest Selected
  ├─ Validate dest in possibleMoves
  └─ movePiece(isNotify)
      ├─ board->move()
      ├─ UI update
      ├─ checkGameOver()
      ├─ switchTurns()
      └─ (if isNotify) Transfer::sendMsg()
  ↓
Move Complete / Idle
```

---

### BoardDialog (Game Board UI)

**Location**: `ui/inc/boardDialog.h`, `ui/src/boardDialog.cpp`

```cpp
class BoardDialog: public IDialogChain {
    explicit BoardDialog(FDialog* parent);
    // Constructor
    // Parameters: parent FDialog (MainDialog)
    // Initializes UI framework
    
    void initLayout() override;
    // FinalCut lifecycle method
    // Called during dialog initialization
    // Process:
    //   1. Board::getInstance() - get/create board
    //   2. Create grid UI labels (board borders)
    //   3. Create piece UI labels (30 pieces)
    //   4. MoveManager::MoveManager() - create move orchestrator
    //   5. Register event callbacks
    
    void clickedCallback();
    // FinalCut callback: piece label clicked
    // Process:
    //   1. Get clicked label coordinates
    //   2. Determine if source or destination selection
    //   3. Call MoveManager::setSourcePoint() or setDestPoint()
    //   4. Calculate moves
    //   5. Highlight valid moves
    
    void moveCallback();
    // FinalCut callback: piece move event
    // Triggered when user confirms move
    
    void dispatchChessmanMove(Point* source, Point* destination);
    // Public method to execute move from MoveManager
    // Parameters: source and destination coordinates
    // Updates: Board state and UI display
    
    void initHook() override;
    // Post-initialization setup
    // Called after UI fully initialized
    
private:
    void addCallback(ILabel* label, std::string event);
    // Add click callback to UI label
    
    IBoard* board;
    MoveManager* moveManager;
    
    // UI Component collections
    RiverBorderLabels riverBoundaryLabels;      // River graphics
    FortressLabels fortressLabels;              // Fortress boundaries
    VerticleLineLabels verticleLineLabels;      // Grid lines
    HorizontalLineLabels horizontalLineLabels;  // Grid lines
    TeamSignalLabels *teamSignalLabels;         // Turn indicator
    
    ILabel* pieces[BOARD_WIDTH][BOARD_LENGTH];  // 10x9 piece UI
};
```

**Event Flow**:
```
User clicks piece at (2, 0)
  ↓
FinalCut detects mouse click
  ↓
pieces[2][0]->clicked() signal
  ↓
BoardDialog::clickedCallback()
  ├─ Get label coordinates: (2, 0)
  ├─ Check if first click (source) or second click (dest)
  └─ if first: MoveManager::setSourcePoint(Point(2, 0))
               ├─ Calculate possible moves
               └─ decoratePotentialPieces(true)
     if second: MoveManager::setDestPoint(Point(3, 0))
                ├─ Validate move
                └─ MoveManager::movePiece()
```

---

### ConnectionBase (Network Abstraction)

**Location**: `websockpp/inc/connectionBase.h`, `websockpp/src/connectionBase.cpp`

```cpp
enum connection_type {
    WSERVER,           // Host server
    WCLIENT,           // Client connecting to server
    NON_CONNECTION     // Offline mode
};

typedef std::function<void(json js)> ConnectionBaseCallback;
// Callback type for receiving JSON messages

class ConnectionBase {
    // Factory method
    static ConnectionBase* setInstance(connection_type type);
    // Create and set singleton instance
    // Parameters: WSERVER, WCLIENT, or NON_CONNECTION
    // Returns: ConnectionBase* (Server or Client subclass)
    // Process:
    //   1. Delete existing instance if any
    //   2. Create new instance based on type
    //   3. Store in static instance
    //   4. Return instance
    
    static ConnectionBase* getInstance();
    // Get current singleton instance
    // Returns: ConnectionBase* or nullptr
    
    // Connection management
    virtual void run() = 0;
    // Start connection in separate thread
    // Implementations:
    //   Server: Listen for incoming connection
    //   Client: Connect to server
    
    // Message sending
    int send(json const js);
    // Send JSON message to peer
    // Parameters: JSON object to send
    // Returns: bytes sent (positive) or error code (negative)
    // Process:
    //   1. Serialize JSON to string
    //   2. Call _send(string)
    //   3. Return result
    
    virtual int _send(std::string const payload) = 0;
    // Implementation-specific send
    // Subclasses override with WebSocket++ specific code
    
    // Receiving
    string _recv(void);
    // Receive message from peer
    // Returns: JSON string from message queue
    
    // Callback management
    void setRecvCallback(ConnectionBaseCallback cb);
    // Set callback invoked on message receive
    // Parameters: function<void(json)> callback
    // Usage: When message received, call cb(json)
    
private:
    static ConnectionBase* instance;
    
    std::thread wThread;                    // Connection thread
    connection mConnection;                 // WebSocket++ connection
    ConnectionBaseCallback mCallback;       // Receive callback
    bool mIsConnected;                      // Connection status
    
protected:
    void onOpen(websocketpp::connection_hdl hdl);
    // WebSocket++ callback: connection opened
    // Sets mIsConnected = true
    
    void onMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);
    // WebSocket++ callback: message received
    // Process:
    //   1. Extract message payload
    //   2. Parse JSON
    //   3. Call mCallback(json)
    
    void onClose(websocketpp::connection_hdl hdl);
    // WebSocket++ callback: connection closed
    // Sets mIsConnected = false
    
    void initSem();
    // Initialize semaphores for thread synchronization
};
```

**Singleton Pattern**:
```cpp
// First call
ConnectionBase* conn = ConnectionBase::setInstance(WCLIENT);
// Creates new Client instance, stores in static variable, returns it

// Subsequent calls
ConnectionBase* conn2 = ConnectionBase::getInstance();
// Returns previously created instance

// Different type
ConnectionBase* conn3 = ConnectionBase::setInstance(WSERVER);
// Deletes Client instance, creates Server instance, returns it
```

**Server Implementation** (`websockpp/src/server.cpp`):
```cpp
class Server : public ConnectionBase {
    void run() override;
    // Start server
    // Process:
    //   1. Create WebSocket++ endpoint
    //   2. Bind to port 9002
    //   3. Register onOpen, onMessage, onClose callbacks
    //   4. Listen and accept connections
    //   5. Display IP address to user
    
    int _send(string payload) override;
    // Send via WebSocket++
};
```

**Client Implementation** (`websockpp/src/client.cpp`):
```cpp
class Client : public ConnectionBase {
    void run() override;
    // Start client
    // Process:
    //   1. Create WebSocket++ endpoint
    //   2. Connect to server IP (from ConfigDialog)
    //   3. Register callbacks
    //   4. Wait for connection confirmation
    //   5. Signal ready to UI
    
    int _send(string payload) override;
    // Send via WebSocket++
};
```

---

### Transfer (Network Protocol Handler)

**Location**: `websockpp/inc/transfer.h`, `websockpp/src/transfer.cpp`

```cpp
enum trans_code {
    MOV,             // Move piece message
    SEL,             // Select piece message (for highlighting)
    TOTAL_CODE
};

typedef std::function<void(Point* from, Point* to)> MovCallback_t;
typedef std::function<void(Point* from)> SelCallback_t;

class Transfer {
    // Constructor
    Transfer(ConnectionBase *connection);
    // Parameters: ConnectionBase instance for sending
    
    // Connection management
    void setConnection(ConnectionBase *connection);
    // Update connection reference (for switching modes)
    
    // Sending messages
    void sendMsg(trans_code opcode, Point *from, Point *to);
    // Send move message (MOV opcode)
    // Parameters:
    //   opcode: MOV
    //   from: source position
    //   to: destination position
    // JSON: {"op":"MOV", "from":{"x":2,"y":0}, "to":{"x":2,"y":2}}
    
    void sendMsg(trans_code opcode, Point *from);
    // Send selection message (SEL opcode)
    // Parameters:
    //   opcode: SEL
    //   from: selected piece position
    // JSON: {"op":"SEL", "from":{"x":2,"y":0}}
    
    // Callback management
    void setCallback(MovCallback_t mcb, SelCallback_t scb);
    // Set callbacks for receiving messages
    // Parameters:
    //   mcb: function<void(Point*, Point*)> - called on MOV
    //   scb: function<void(Point*)> - called on SEL
    
    // Message dispatching
    void dispatchMsg(json js);
    // Parse incoming JSON and dispatch to callback
    // Parameters: JSON message from network
    // Process:
    //   1. Extract "op" field
    //   2. Parse coordinates from "from" and "to"
    //   3. If MOV: call mMovCallback(from, to)
    //   4. If SEL: call mSelCallback(from)

private:
    ConnectionBase *mConnection;    // Network layer
    MovCallback_t mMovCallback;     // Handle remote move
    SelCallback_t mSelCallback;     // Handle remote selection
};
```

**Message Protocol**:

Move Message:
```json
{
    "op": "MOV",
    "from": {"x": 0, "y": 3},
    "to": {"x": 0, "y": 4}
}
```

Selection Message:
```json
{
    "op": "SEL",
    "from": {"x": 2, "y": 0}
}
```

---

## Function Call Sequences

### Sequence 1: Complete Game Startup

```
main()
  ├─ FApplication app(argc, argv)
  │
  ├─ app.initTerminal()
  │   └─ Initialize FinalCut terminal system
  │
  ├─ MainDialog board(&app)
  │   ├─ MainDialog::MainDialog()
  │   │   ├─ IntroDialog::IntroDialog() [not shown]
  │   │   ├─ ConfigDialog::ConfigDialog()
  │   │   │   └─ ModeSelection setup
  │   │   └─ BoardDialog::BoardDialog()
  │   │       └─ (not initialized yet)
  │   │
  │   └─ MainDialog::initLayout()
  │       └─ IntroDialog::initLayout()
  │           └─ Display intro screen
  │
  ├─ FWidget::setMainWidget(&board)
  │   └─ Set as main window
  │
  ├─ board.show()
  │   └─ Display MainDialog
  │
  └─ app.exec()
      └─ Enter event loop
          ├─ Display IntroDialog animations
          ├─ Wait for key press to advance
          │
          ├─ Show ConfigDialog
          │   ├─ Display mode selection (Offline/Online)
          │   ├─ If Online:
          │   │   ├─ ConnectionBase::setInstance(WSERVER or WCLIENT)
          │   │   ├─ ConnectionBase::getInstance()->run()
          │   │   │   └─ Start connection in separate thread
          │   │   └─ Wait for connection
          │   │
          │   └─ On "Next" button:
          │       ├─ ConfigDialog::okCallback()
          │       └─ Switch to BoardDialog
          │
          ├─ Show BoardDialog
          │   ├─ BoardDialog::initLayout()
          │   │   ├─ Board::getInstance()
          │   │   │   ├─ First call: creates Board instance
          │   │   │   ├─ Board::setup()
          │   │   │   │   ├─ Create 30 IChessman instances
          │   │   │   │   │   └─ IChessman::newInstance(piece, point)
          │   │   │   │   └─ Place in map[x][y]
          │   │   │   └─ Return board
          │   │   │
          │   │   ├─ Create UI labels for 10x9 board
          │   │   │   ├─ Create grid labels
          │   │   │   └─ Create 30 piece labels
          │   │   │
          │   │   ├─ MoveManager::MoveManager()
          │   │   │   └─ Initialize with board reference
          │   │   │
          │   │   └─ Register callbacks for all labels
          │   │       └─ pieces[x][y]->clicked.connect(...)
          │   │
          │   └─ BoardDialog::initHook()
          │       └─ Post-initialization setup
          │
          ├─ Display board
          └─ Game ready for user input
```

---

### Sequence 2: Player Makes Move (Offline)

```
User clicks piece at (2, 0) [selected piece]
  │
  └─ FinalCut detects mouse event
      │
      └─ pieces[2][0]->clicked signal
          │
          └─ BoardDialog::clickedCallback()
              │
              ├─ Determine coordinates: (2, 0)
              ├─ Check: is source or dest?
              │   └─ First click → is source
              │
              └─ MoveManager::setSourcePoint(Point(2, 0))
                  │
                  ├─ source = Point(2, 0)
                  └─ decorateTargetedPieces(true)
                      │
                      └─ Update UI: highlight piece at (2, 0)
                          └─ pieces[2][0]->setBackgroundColor(FOCUS_COLOR)
                              
User clicks destination at (2, 2) [destination]
  │
  └─ FinalCut detects mouse event
      │
      └─ pieces[2][2]->clicked signal
          │
          └─ BoardDialog::clickedCallback()
              │
              ├─ Determine coordinates: (2, 2)
              ├─ Check: is source or dest?
              │   └─ Second click → is dest
              │
              └─ MoveManager::setDestPoint(Point(2, 2))
                  │
                  ├─ dest = Point(2, 2)
                  │
                  └─ MoveManager::calculatePossibleMoves(false)
                      │   (false = offline, don't notify network)
                      │
                      ├─ IChessman* piece = board->getChessman(source)
                      │
                      ├─ Rule::create(board)
                      │   .at(source)
                      │   .forChessman(piece)
                      │   .build()
                      │   └─ Rule applies shape + target validation
                      │
                      ├─ possibleMoves = valid moves from Rule
                      │
                      ├─ decoratePotentialPieces(true)
                      │   └─ Highlight all possibleMoves in UI
                      │
                      └─ return possibleMoves
                              
              ├─ Validate: is (2, 2) in possibleMoves?
              │   └─ Yes, it's valid
              │
              └─ MoveManager::movePiece(false)
                  │   (false = offline, don't notify network)
                  │
                  ├─ Verify (2, 2) in possibleMoves
                  │   └─ Yes, proceed
                  │
                  ├─ IChessman* capturedPiece = board->getChessman(dest)
                  │   └─ nullptr (no capture in this example)
                  │
                  ├─ board->move(Point(2, 0), Point(2, 2))
                  │   │
                  │   ├─ IChessman* piece = map[2][0]
                  │   ├─ map[2][2] = piece
                  │   ├─ map[2][0] = nullptr
                  │   └─ Update internal state
                  │
                  ├─ Update UI:
                  │   ├─ pieces[2][0]->setText("")
                  │   ├─ pieces[2][2]->setText("SOLDIER")
                  │   ├─ decorateTargetedPieces(false)
                  │   └─ decoratePotentialPieces(false)
                  │
                  ├─ Check game over
                  │   ├─ Umpire::checkMate(opponent)
                  │   └─ If general captured: end game
                  │
                  ├─ Switch turns
                  │   ├─ currentTeam = BLACK
                  │   └─ Update UI turn indicator
                  │
                  └─ return true
                  
Move complete, waiting for Black's move
```

---

### Sequence 3: Online Move - Player 1 (Server)

```
[SERVER] User (Red) makes move at (2, 0) → (2, 2)
  │
  └─ (same as offline sequence until MoveManager::movePiece)
      │
      └─ MoveManager::movePiece(true)
          │   (true = online, notify network)
          │
          ├─ board->move(source, dest)
          │
          ├─ Update local UI
          │
          └─ Transfer::sendMsg(MOV, source, dest)
              │
              └─ Create JSON message:
                  {
                    "op": "MOV",
                    "from": {"x": 2, "y": 0},
                    "to": {"x": 2, "y": 2}
                  }
              │
              └─ ConnectionBase::send(json)
                  │
                  ├─ Serialize JSON to string
                  │
                  └─ Server::_send(string)
                      │
                      └─ WebSocket++: Send to Client
                          │
                          (network transmission)
                          │
[CLIENT] Receives WebSocket message
  │
  └─ ConnectionBase::onMessage()
      │
      ├─ Extract message payload
      │
      └─ Parse JSON
          │
          └─ Call mCallback(json)
              │   (mCallback = Transfer::dispatchMsg)
              │
              └─ Transfer::dispatchMsg(json)
                  │
                  ├─ Extract "op" field: "MOV"
                  ├─ Parse coordinates: from(2,0) to(2,2)
                  │
                  └─ Call mMovCallback(from, to)
                      │   (mMovCallback = MoveManager::movePieceTransferCb)
                      │
                      └─ MoveManager::movePieceTransferCb(from, to)
                          │
                          ├─ board->move(from, to)
                          │
                          ├─ Update UI locally
                          │
                          ├─ Switch turns
                          │   └─ Now it's Client's (Black) turn
                          │
                          └─ Ready for Black's move
```

---

### Sequence 4: Check Detection

```
Player 1 moves piece that would expose own General to attack
  │
  └─ MoveManager::movePiece()
      │
      ├─ Before executing: Umpire::preCheckMate(from, to)
      │   │
      │   ├─ Determine moving player's team
      │   │
      │   ├─ Simulate move:
      │   │   ├─ temp_piece = board->map[from]
      │   │   ├─ board->map[to] = temp_piece
      │   │   ├─ board->map[from] = nullptr
      │   │   └─ Update general location if moved
      │   │
      │   ├─ Find general location
      │   │
      │   ├─ Check if any opponent piece can attack general
      │   │   FOR each opponent piece at (x, y):
      │   │       opponent_moves = board->getPossibleMoves(x, y)
      │   │       IF general_location in opponent_moves:
      │   │           RETURN false (move leaves general in check)
      │   │
      │   ├─ Restore board to original state
      │   │
      │   └─ RETURN true if safe, false if check
      │
      ├─ IF preCheckMate returned false:
      │   ├─ REJECT move
      │   ├─ Display error message
      │   └─ return false
      │
      └─ IF preCheckMate returned true:
          └─ Execute move normally
```

---

## Callback System

### Event Callbacks (FinalCut)

```cpp
// UI Label clicked
pieces[x][y]->clicked.connect([this, x, y]() {
    BoardDialog::clickedCallback();
    // Triggered by mouse click on piece
});

// Custom callbacks registered by MoveManager
void addCallback(ILabel* label, std::string event) {
    if (event == "clicked") {
        label->clicked.connect(
            [this, label]() { BoardDialog::clickedCallback(); }
        );
    }
}
```

### Network Callbacks

```cpp
// ConnectionBase sets up WebSocket++ callbacks
ConnectionBase::run() {
    endpoint.set_open_handler(
        bind(&ConnectionBase::onOpen, this, _1)
    );
    endpoint.set_message_handler(
        bind(&ConnectionBase::onMessage, this, _1, _2)
    );
    endpoint.set_close_handler(
        bind(&ConnectionBase::onClose, this, _1)
    );
}

// Transfer sets up move/selection callbacks
Transfer::setCallback(
    [](Point* from, Point* to) {
        MoveManager::movePieceTransferCb(from, to);
    },
    [](Point* from) {
        MoveManager::selPieceTransferCb(from);
    }
);

// When message received: onMessage → dispatchMsg → callbacks invoked
```

### Lambda Callbacks

The codebase uses C++11 lambdas for callbacks:

```cpp
// Button click callback
ok_button.clicked.connect([this]() {
    ConfigDialog::okCallback();
    // this = ConfigDialog instance
});

// Piece click callback (stored in pieces array)
pieces[2][0]->clicked.connect([this, x=2, y=0]() {
    // x, y captured by value
    // this captured by reference
    BoardDialog::clickedCallback();
});
```

---

## Data Flow Diagrams

### Offline Move Data Flow

```
User Input
    │
    ├─→ FinalCut Event Queue
    │
    ├─→ pieces[2][0]->clicked signal
    │
    ├─→ BoardDialog::clickedCallback()
    │
    ├─→ MoveManager::setSourcePoint(Point(2, 0))
    │
    ├─→ MoveManager::calculatePossibleMoves()
    │   │
    │   ├─→ Board::getChessman()
    │   │
    │   ├─→ IChessman::getPossibleMoves(board)
    │   │
    │   ├─→ Rule::create()...build()
    │   │
    │   └─→ vector<Point*> possibleMoves
    │
    ├─→ UI Update (highlight moves)
    │   │
    │   └─→ pieces[2][2]->setBackgroundColor(POTENTIAL)
    │
    ├─→ [User clicks destination]
    │
    ├─→ pieces[2][2]->clicked signal
    │
    ├─→ MoveManager::setDestPoint(Point(2, 2))
    │
    ├─→ MoveManager::movePiece(false)
    │   │
    │   ├─→ Board::move(from, to)
    │   │
    │   └─→ Update internal map[10][9]
    │
    └─→ UI Update (redraw board)
        │
        └─→ BoardDialog updates all piece labels
```

### Online Move Data Flow

```
[SERVER]
User Input → BoardDialog → MoveManager
                              ├─→ Board::move()
                              │
                              └─→ Transfer::sendMsg()
                                  ├─→ JSON create
                                  └─→ ConnectionBase::send()
                                      └─→ Server::_send()
                                          └─→ WebSocket++
                                              │
                                    [NETWORK]
                                              │
[CLIENT]                                      │
                                              ↓
                                     WebSocket++ receives
                                              │
                                     ConnectionBase::onMessage()
                                              │
                                     Transfer::dispatchMsg()
                                              │
                                     MoveManager::movePieceTransferCb()
                                              │
                                     Board::move()
                                              │
                                     BoardDialog updates UI
```

### State Transition Diagram

```
[OFFLINE]
    ↑
    │ Select Offline
    │
MainDialog
    ↓
IntroDialog [90s animations]
    │ [Any key pressed]
    ↓
ConfigDialog
    ├─ Mode Selection
    │   ├─ Offline
    │   └─ Online
    │       ├─ Server → Wait for connection
    │       └─ Client → Input IP and connect
    │
    │ [Next button]
    ↓
BoardDialog
    ├─ Board::getInstance() + setup()
    ├─ MoveManager created
    └─ Game starts

[GAME STATE]
    Waiting for Player 1 move
        ↓
    Player 1 clicks piece → Highlight moves
        ↓
    Player 1 clicks destination → Execute move
        ↓
    Board updates
        ↓
    Waiting for Player 2 move
        ↓
    [Repeat until game over]
        ↓
    General captured
        ↓
    Game Over (MVP)
```

---

## Summary

This document provides comprehensive function call sequences and data flows for the Chinese Chess project:

✅ **Core Classes**: Board, Chessman, Rule, Umpire, MoveManager, ConnectionBase, Transfer
✅ **Function Flows**: Startup, Move execution (offline/online), Check detection
✅ **Callbacks**: FinalCut UI events, Network messages, Lambda functions
✅ **Data Flows**: User input → game logic → UI update, Network message handling
✅ **State Machines**: Game states, Connection states, Move validation states

The architecture demonstrates professional C++ development with clear separation of concerns and well-defined interfaces between components.
