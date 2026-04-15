🧠 Architecture & Design

📌 Overview

Tokyo Games Center was originally developed as part of a college Object-Oriented Programming assignment and later expanded into a full personal project.

The main goal of the project was to apply OOP principles in a practical environment while building a scalable and interactive system. Over time, the project evolved into a custom mini game engine capable of handling multiple games through a unified architecture.

---

🔄 State Machine Design

The core of the system is built around a state-based architecture, which is the standard approach when working with SFML applications.

Each part of the application is represented as a separate state, such as:

- Splash Screen
- Main Menu
- Game Selection
- Gameplay
- Pause
- Game Over

These states are managed using a stack-based State Machine, where:

- New states are pushed onto the stack
- Old states are popped when no longer needed
- Replacing a state is done by popping then pushing a new one

💡 Why State Machine?

Without this system:

- Input handling would become extremely complex
- Multiple screens would overlap in a single loop
- Code would become tightly coupled and difficult to maintain

By isolating each screen into its own state, the system becomes:

- Easier to manage
- More modular
- Easier to extend

---

🛡️ Input Shield

During development, an issue was encountered where mouse clicks were registered multiple times due to how fast input is processed.

This caused unintended behavior when switching between states (e.g., accidental double clicks).

To solve this, an Input Shield mechanism was introduced:

- A short delay (~0.2 seconds) is applied during state transitions
- Input is temporarily blocked during this period

This ensures:

- No accidental interactions
- Stable and predictable state transitions

---

🗂️ Manager-Based Architecture

The system uses a manager pattern to separate responsibilities and reduce coupling.

🎮 Game Manager

- Acts as the core engine
- Controls the main game loop:
  - Processing state changes
  - Handling input
  - Updating logic
  - Rendering

---

🎹 Input Manager

- Centralizes all input handling
- Ensures consistent behavior across all states and games
- Prevents duplication of input logic

---

📦 Asset Manager

- Handles loading and storing:
  - Textures
  - Fonts
  - Audio

💡 Why Asset Manager?

Loading assets directly from disk during runtime would:

- Be extremely inefficient
- Cause performance issues (especially if done repeatedly per frame)

Instead:

- Assets are loaded once and stored in memory (using maps)
- They are accessed directly when needed

This significantly improves performance and avoids unnecessary disk operations.

---

🎮 Game System Design

All games are organized within the Game Center module.

Each game consists of two main parts:

- Game Logic → Pure logic (independent of UI)
- Game State → Handles rendering and user interaction

This separation allows:

- Logic to be reused or tested independently
- UI to act as a layer on top of the logic

---

🧩 Template-Based Design

To support multiple game variations, the project uses a template-based approach for core components such as:

- Boards
- Players

Each game:

- Inherits from base classes
- Overrides behavior to match its specific rules

💡 Benefit

This ensures:

- All games follow a consistent structure
- Code reuse across different game modes
- Easy creation of new variations without rewriting core logic

---

⚡ Performance Considerations

The game uses a fixed time-step loop to ensure:

- Consistent gameplay speed across different machines
- Stable behavior regardless of hardware performance

This decision was especially important since the project was developed across multiple devices.

---

🔮 Scalability

The system is designed to be easily extensible.

➕ Adding a New Game

To introduce a new game:

1. Implement the game logic
2. Create a new state that inherits from the base State class
3. Override required methods (Input, Update, Draw)
4. Register the game in:
   - Main Menu
   - Mode Selection
   - Game Over flow

No modifications are required in the core engine.

---

⚔️ Challenges & Lessons Learned

🧠 Engine Design

The most challenging part was designing the manager system and overall engine architecture, as it required understanding how game engines are structured from scratch.

---

🎮 State Integration

Treating each game as a state while maintaining clean input and rendering logic required careful design.

---

♟️ Complex Game Logic

Implementing advanced variants such as Ultimate Tic Tac Toe introduced additional complexity in managing nested boards and rules.

---

📌 Conclusion

This project demonstrates the practical application of:

- Object-Oriented Programming
- System design and architecture
- Real-time application development

It evolved from a simple assignment into a fully structured, extensible mini game engine, capable of supporting multiple games under a unified system.
