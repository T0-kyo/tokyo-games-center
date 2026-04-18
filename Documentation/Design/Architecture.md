<div align="center">

# ◈ Architecture & Design

*Tokyo Games Center — Technical Overview*

</div>

---

## Origin

Tokyo Games Center started as a college OOP assignment and grew into a personal project. What began as a simple exercise turned into a full modular system — a lightweight game engine capable of running multiple game variants under one unified framework.

---

## ◈ State Machine

The entire application flow is driven by a **stack-based state machine**. Every screen — main menu, gameplay, pause, game over — is an independent state sitting on a stack.

```
┌─────────────────────────────────┐
│         State Stack             │
│                                 │
│  ┌───────────────────────────┐  │
│  │       GameOverState       │  │  ← active (top)
│  ├───────────────────────────┤  │
│  │         GameState         │  │
│  ├───────────────────────────┤  │
│  │     ModeSelectionState    │  │
│  ├───────────────────────────┤  │
│  │       MainMenuState       │  │  ← always at the bottom
│  └───────────────────────────┘  │
└─────────────────────────────────┘
```

- **Push** — adds a new active state on top
- **Pop** — removes the current state, returning to the one beneath
- **Replace** — pop then push, used for one-way transitions

Each state is fully self-contained. This isolates logic, simplifies input handling, and keeps the codebase easy to maintain.

---

## ◈ Manager System

Three managers handle all cross-cutting responsibilities, each with a single clear role:

| Manager | Responsibility |
|---------|---------------|
| `GameManager` | Owns the main loop — processes state changes, dispatches input, updates, and renders |
| `InputManager` | Centralizes all mouse and keyboard input, providing consistent behavior across every state |
| `AssetManager` | Loads textures, fonts, and audio once from disk and caches them in memory maps for reuse |

All three share a single `GameData` struct passed around as a `shared_ptr`, so every state accesses the same managers without duplication.

### Input Shield

During state transitions, a brief input delay is applied to prevent accidental double-clicks or ghost inputs from carrying over into the next state.

---

## ◈ Game System Design

Every game in the center follows the same two-layer structure:

```
┌──────────────────────────────────────┐
│              Game State              │
│     (rendering · input · UI)         │
└─────────────────┬────────────────────┘
                  │ uses
┌─────────────────▼────────────────────┐
│             Game Logic               │
│   (rules · win conditions · moves)   │
└──────────────────────────────────────┘
```

The logic layer has no knowledge of SFML or the UI. The state layer has no knowledge of the rules. This clean boundary makes each layer independently testable and easy to swap out.

---

## ◈ Template-Based Structure

Core components are built as generic base classes and extended per game:

```cpp
Board<T>    →  TTT4x4_Board, Ultimate_Board, NumericalTTT_Board ...
Player<T>   →  shared across all games
Move<T>     →  shared across all games
```

The type parameter `T` means boards can hold `char`, `int`, or any other symbol type — Numerical TTT uses `int`, every other game uses `char`. Each game overrides only what it needs, keeping shared behavior in one place.

---

## ◈ Performance

The game loop runs on a **fixed timestep** — logic updates at a constant rate regardless of frame rate or hardware speed. This guarantees consistent gameplay behavior across different machines.

---

## ◈ Scalability

Adding a new game requires three steps and zero changes to the core engine:

```
1.  Implement game logic   →  extend Board<T>, override rules
2.  Create a game state    →  extend State, connect to logic
3.  Register the game      →  add button to MainMenuState
                           →  add route in ModeSelectionState
                           →  add case in GameOverState
```

The engine does not need to be touched. New variants slot in through the existing interfaces.

---

## ◈ Challenges

**Architecture from scratch** — designing the manager system and state machine without a reference or framework required planning every interaction between components upfront before any game logic was written.

**Input across state transitions** — keeping input clean when switching states, especially with mouse events that span multiple frames, needed the Input Shield mechanism to handle reliably.

**Ultimate Tic Tac Toe** — managing nine independent 3×3 boards simultaneously, each with its own state and grid position, was the most complex UI and rendering challenge in the project.

---

<div align="center">

## ◈ Conclusion

The project demonstrates the application of Object-Oriented Programming, Problem Solving and system design principles in a real-time environment. It provides a scalable foundation for extending the game center with additional variants by plugging into existing interfaces, not rewriting the engine while maintaining a clean and organized structure.

</div>
