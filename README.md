Tokyo Games Center

A modular desktop game suite built using C++ and SFML, featuring multiple Tic Tac Toe variants powered by a custom-built mini game engine.

---

Overview

Tokyo Games Center is a personal project that evolved from a college assignment into a scalable system.

At its core, it includes a custom engine built from scratch, designed around a state machine and manager-based architecture to support multiple games within a unified framework.

---

Features

- 12+ Tic Tac Toe variants with different rules and board layouts
- Custom-built state-driven game engine
- Stack-based state machine for managing application flow
- Template-based design for reusable board and player logic
- Asset management system for efficient resource handling
- Basic AI opponent (random-based, extendable)

---

Architecture

The system is based on:

- Custom mini game engine
- Stack-based state machine
- Manager pattern (GameManager, InputManager, AssetManager)
- Separation between game logic and UI

For more details, see the documentation in the "Documentation/" directory.

---

Build and Run

Linux

Requirements:

- SFML 3
- C++ compiler (g++)
- Make

git clone https://github.com/T0-kyo/tokyo-games-center.git
cd tokyo-games-center
make && ./Game

Windows

A prebuilt executable is provided with the required dependencies.

---

Documentation

Additional documentation, including architecture details, diagrams, and screenshots, is available in the "Documentation/" directory.

---

The Team
Lead Developer: Alhussain Haitham(T0-kyo) — Architecture, Game Loop, Logic and States Implementation.

Assets and UI Design: Ahmed Youssef.

Technical Support: Ali Mohamed and Ahmed Youssef.

---

License

This project originated as a college assignment and was later expanded into a professional personal project.

All rights reserved.
