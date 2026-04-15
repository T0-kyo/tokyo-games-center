Tokyo Games Center 🚀
A high-performance, modular game suite built from the ground up using C++ and SFML. This project serves as a comprehensive exploration of Object-Oriented Programming (OOP), custom engine architecture, and real-time state management.

Project Overview
Tokyo Games Center is more than just a collection of games; it is a custom-built game engine designed for extensibility and performance. Developed to strengthen core C++ skills, the project implements a robust architecture including:

Custom State Machine: Handles complex transitions, including a specialized Input Shield to prevent accidental clicks during state swaps.

Asset Management System: A centralized hub for textures, fonts, and audio buffers to optimize memory usage and avoid redundant disk I/O.

Template-Based Gameplay: Uses C++ templates for Boards and Players, allowing for dozens of Tic-Tac-Toe variants and board games to run on a unified logic core.

Features
Diverse Game Library: Includes 12+ game modes ranging from classic 4x4 Tic-Tac-Toe to specialized variants like Numerical TTT, Pyramid, and Ultimate Tic-Tac-Toe.

Futuristic Aesthetic: Immerses players in a Space-Futuristic theme with deep purples and sky-themed backgrounds.

Built-in Guide: Every game mode includes a dedicated rulebook accessible via the UI for seamless learning.

Optimized Performance: Runs at a locked 60 FPS with a fixed time-step loop for consistent gameplay across different hardware.

System Architecture
The project follows a Manager-Pattern architecture, ensuring that game data is decoupled from the rendering and input logic.

GameManager: Coordinates the main loop and shared GameData.

InputManager: Standardizes mouse and keyboard interaction across all states.

StateMachine: Manages the life cycle of game states (Init, Update, Draw, Pause, Resume).

Installation and Running
For Linux (Native)
Ensure you have the SFML development libraries installed (sudo apt install libsfml-dev).

Clone the repository:
git clone https://github.com/yourusername/tokyo-games-center.git
cd tokyo-games-center

Build and Run:
make && ./Game

For Windows
The project includes the necessary audio .dll files. Run the provided executable to start the Tokyo Games Center immediately without terminal configuration.

Controls
Menu Navigation: Mouse-controlled buttons.

Gameplay:

Mouse: Primary interaction for placing pieces.

Keyboard: Numerical input for specific modes like Numerical TTT.

The Team
Lead Developer: Alhussain Haitham — Architecture, Game Loop, and Logic Implementation.

Assets and UI Design: Ahmed Youssef.

Technical Support: Ali Mohamed and Ahmed Youssef.
