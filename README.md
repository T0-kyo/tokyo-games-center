🎮 Tokyo Games Center 🚀

A high-performance, modular game suite built from the ground up using C++ and SFML.
This project serves as a deep exploration of Object-Oriented Programming (OOP), custom engine architecture, and real-time state management.

---

📌 Project Overview

Tokyo Games Center is more than just a collection of games — it is a custom-built mini game engine designed for scalability, performance, and clean architecture.

The project focuses on building everything from scratch, including:

- A full state-driven system
- Custom game management architecture
- Reusable and extensible game logic
- Unique Custom Sprites

---

🚀 Features

🎲 Diverse Game Library

- Includes 12+ Tic Tac Toe variants
- Ranging from:
  - Classic boards (3x3, 4x4, etc.)
  - Connect 4
  - Unique-style boards
  - Advanced variations (e.g. Ultimate Tic Tac Toe)

---

🧠 AI Opponent

- Currently uses a random-based AI
- Planned upgrade to easy–medium intelligent AI

---

🧩 Flexible Board System

- Multiple board sizes and layouts
- Each game can define its own structure while sharing core logic

---

📖 Built-in Rule System

- Every game includes a dedicated rulebook
- Explains:
  - Controls (mouse / keyboard)
  - Game rules
  - Win / lose / draw conditions

---

🎨 Custom UI & Assets

- All assets are designed manually from scratch
- No external asset packs used

---

🔊 Audio & Visual Feedback

- Button click sounds
- Intro audio
- Subtle UI animations for enhanced experience

---

⚡ Optimized Performance

- Runs at a stable 60 FPS
- Uses a fixed time-step game loop for consistency across devices

---

🧱 System Architecture

The project follows a Manager-Pattern + State Machine architecture, effectively acting as a mini game engine.

🧠 Core Systems

- State Machine
  - Handles all game states:
    
    - Splash Screen
    - Main Menu
    - Pause
    - Game Over
    - etc..
  
  - Includes an Input Shield system to prevent accidental input during transitions

---

- Game Manager
  
  - Coordinates core systems and shared data
  - Acts as the backbone of the engine
  - Contains Game Loop

- Input Manager
  
  - Standardizes mouse and keyboard handling across all states

- Asset Manager
  
  - Centralized system for:
    - Textures
    - Fonts
    - Audio
  - Prevents redundant loading and improves performance

---

🎮 Game Center Module

- Contains all game implementations
- Each game:
  - Has its own logic and UI
  - Runs as an independent state
- Built using a template-based system:
  - Reusable Board and Player logic
  - Allows easy creation of new game variants

---

🎮 Gameplay

🖱️ Navigation

- Fully controlled using the mouse

🎯 Controls

- Mouse: Primary gameplay interaction
- Keyboard: Used in specific modes (e.g. numerical input)


---

🏁 Game Flow

1. Launch → Splash Screen
2. Navigate to Game Center
3. Select a game
4. Choose mode:
   - Player vs Player
   - Player vs Computer
5. Play the game
6. Game Over screen:
   - Replay
   - Return to Main Menu

---

⚙️ Tech Stack

- Language: C++
- Graphics Library: SFML (Version 3)
- Architecture: Custom State-Based Game Engine

---

🛠️ Installation & Running

  Will be made a downloadable file.

---

📸 Screenshots

«Screenshots will be added here»

---

⭐ Highlights

- 🧠 Built a mini game engine from scratch
- 🧩 Highly modular and extensible architecture
- 🎮 Supports multiple game variants on shared logic
- 🎨 All assets designed manually
- ⚡ Focus on performance and clean design


---

👨‍💻 Team

- Lead Developer: Alhussain Haitham (T0-kyo)
  
  - Architecture, Engine Design, Game Logic, States Implementation

- Assets & UI Design: Ahmed Youssef

- Technical Support:
  
  - Ali Mohamed
  - Ahmed Youssef

---

📄 License

This project originated as a college assignment and was significantly expanded into a personal project, focusing on custom engine architecture and game development.

All rights reserved.
