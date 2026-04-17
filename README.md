Tokyo Games Center

"C++" (https://img.shields.io/badge/C++-17-blue)
"SFML" (https://img.shields.io/badge/SFML-3-green)
"Status" (https://img.shields.io/badge/Status-Completed-brightgreen)

A modular desktop game suite built using C++ and SFML, featuring multiple Tic Tac Toe variants powered by a custom-built mini game engine.

---

Overview

Tokyo Games Center started as a college assignment and evolved into a scalable personal project.

At its core, the project includes a custom engine built from scratch, designed around a state machine and manager-based architecture to support multiple games within a unified framework.

---

Preview

<!-- Replace with your GIF or video -->"Preview" (Documentation/images/preview.gif)

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

The system is built on:

- Custom mini game engine
- Stack-based state machine
- Manager pattern (GameManager, InputManager, AssetManager)
- Separation between game logic and UI

For more details, see the documentation in the "Documentation/" directory.

---

Installation

Linux

Requirements

- SFML 3
- C++ compiler (g++)
- Make

git clone https://github.com/T0-kyo/tokyo-games-center.git
cd tokyo-games-center
make && ./Game

---

Windows

A prebuilt executable is provided with the required dependencies.
Download, extract, and run the executable.

---

Documentation

Detailed documentation, including architecture, diagrams, and screenshots, is available in the "Documentation/" directory.

---

Team

- Alhussain Haitham (T0-kyo)
  Architecture, Game Engine, Game Loop, Logic and State Implementation

- Ahmed Youssef
  Assets and UI Design

- Ali Mohamed
  Technical Support

---

License

This project originated as a college assignment and was later expanded into a personal project.

All rights reserved.
