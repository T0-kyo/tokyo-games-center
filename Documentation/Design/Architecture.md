Architecture & Design

Overview

Tokyo Games Center was initially developed as a college assignment focused on Object-Oriented Programming and later expanded into a personal project. The system evolved into a modular, state-driven architecture that functions as a lightweight game engine capable of supporting multiple game variants.

---

State Machine

The application is built around a stack-based state machine. Each screen or mode is represented as an independent state (e.g., main menu, gameplay, pause, game over).

States are managed using push and pop operations:

- New states are pushed onto the stack
- Inactive states are removed by popping
- State replacement is handled through pop-then-push

This design isolates logic per state, simplifies input handling, and improves maintainability.

---

Input Handling

An Input Manager centralizes all input processing to ensure consistent behavior across the application.

To address unintended multiple input triggers during transitions, an Input Shield mechanism is used. A short delay is applied when switching states, temporarily disabling input to prevent duplicate or accidental mouse clicks.

---

Manager System

The system uses a manager-based structure to separate responsibilities:

- GameManager: Controls the main loop, including state processing, input handling, updates, and rendering.
- InputManager: Standardizes mouse and keyboard input across all states.
- AssetManager: Loads and stores textures, fonts, and audio in memory using maps for efficient reuse.

The Asset Manager avoids repeated disk access by caching resources, improving performance and stability.

---

Game System Design

Each game consists of:

- A logic layer containing the core rules and mechanics
- A state layer responsible for rendering and user interaction

This separation allows the logic to remain independent of the UI, making the system easier to extend and maintain.

---

Template-Based Structure

Core components such as boards and players are implemented using base classes and extended by individual games.

Each game inherits from these base structures and overrides behavior to match its specific rules. This approach ensures consistency while allowing flexibility across different game variants.

---

Performance

The application uses a fixed time-step loop to maintain consistent behavior across different hardware. This ensures stable gameplay and uniform performance regardless of system differences.

---

Scalability

The architecture is designed to support easy extension.

To add a new game:

1. Implement the game logic
2. Create a new state derived from the base state class and connect it to the logic
3. Integrate it into the MainMenu, ModeSelection state and the GameOver state

This process does not require modification of the core engine.

---

Challenges

Designing the manager system and overall architecture from scratch was the primary challenge, requiring careful planning of responsibilities and interactions between components.

Handling game states as independent units while maintaining clean input and rendering logic also required careful structuring.

Additionally, implementing complex variants such as Ultimate Tic Tac Toe introduced challenges in managing more advanced State UI and mulitple small boards at once.

---

Conclusion

The project demonstrates the application of Object-Oriented Programming and system design principles in a real-time environment. It provides a scalable foundation for extending the game center with additional variants while maintaining a clean and organized structure.