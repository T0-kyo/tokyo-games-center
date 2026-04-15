Tokyo Games Center

A modular desktop game suite built using C++ and SFML, featuring multiple Tic Tac Toe variants and a custom state-driven architecture.

Overview

Tokyo Games Center is a personal project that evolved from a college assignment into a scalable mini game engine. It is designed to support multiple games through a unified system using a state machine and manager-based architecture.

Features

- 12+ Tic Tac Toe variants with different rules and board layouts
- State-based system for managing menus, gameplay, and transitions
- Template-based design for reusable board and player logic
- Asset management system for efficient resource handling
- Basic AI opponent (random-based, extendable)

Architecture

The project is built around:

- A stack-based state machine
- Manager pattern (GameManager, InputManager, AssetManager)
- Separation between game logic and UI

Further details are available in the "Documentation/" folder.

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

Documentation

Additional documentation, including architecture details, diagrams, and screenshots, can be found in the "docs/" directory.

License

This project originated as a college assignment and was later expanded into a personal project.

All rights reserved.