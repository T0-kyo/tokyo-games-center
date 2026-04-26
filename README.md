<div align="center">

```

 ████████╗ ██████╗ ██╗  ██╗██╗   ██╗ ██████╗      ██████╗  █████╗ ███╗   ███╗███████╗███████╗
 ╚══██╔══╝██╔═══██╗██║ ██╔╝╚██╗ ██╔╝██╔═══██╗    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝██╔════╝
    ██║   ██║   ██║█████╔╝  ╚████╔╝ ██║   ██║    ██║  ███╗███████║██╔████╔██║█████╗  ███████╗
    ██║   ██║   ██║██╔═██╗   ╚██╔╝  ██║   ██║    ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  ╚════██║
    ██║   ╚██████╔╝██║  ██╗   ██║   ╚██████╔╝    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗███████║
    ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝    ╚═════╝      ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝╚══════╝
```

<br/>

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-3.0-8CC445?style=for-the-badge&logo=sfml&logoColor=white)

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Windows](https://img.shields.io/badge/Windows-0078D4?style=for-the-badge&logo=windows&logoColor=white)
![Release](https://img.shields.io/badge/Release-v1.0.1-brightgreen?style=for-the-badge)

</div>

<div align="center">

[![Tokyo Games Center — Gameplay Demo](https://img.youtube.com/vi/Ir6dkl1ylP8/maxresdefault.jpg)](https://www.youtube.com/watch?v=Ir6dkl1ylP8)

</div>
---

## ◈ Overview

Tokyo Games Center is a desktop game suite featuring 13 Tic Tac Toe variants — each with its own rules, board layout, and logic. The project was built entirely from scratch in C++ using SFML for rendering, including a custom game engine, a stack-based state machine, and a full set of hand-crafted sprites and UI assets. It started as a college assignment and grew into something bigger.
(checkout the Release section)

---

## ◈ Game Variants

-  **Numerical TTT** · **Word TTT** · **SUS**
-  **Memory TTT** · **Misère TTT**  · **Infinity TTT**
-  **4×4 TTT** · **5×5 TTT**  · **Ultimate TTT** · **Obstacles TTT**
-  **Diamond TTT** · **Pyramid TTT** · **Four In A Row**

---

## ◈ Architecture

- **Stack-based state machine** — push/pop states across menus, gameplay, pause, and game over
- **Manager pattern** — `InputManager`, `AssetManager`, and `GameData` share state via `shared_ptr`
- **Template-based game logic** — `Board<T>`, `Player<T>`, `Move<T>` support any symbol type
- **Decoupled design** — board logic is fully separated from SFML rendering and UI
- **Basic AI opponent** — random-based, extendable

For full details, see the `Documentation/` directory which includes UML class diagrams and state flow diagrams.

---

## ◈ Build & Run

### Linux

**Requirements:** SFML 3 (MUST BE VERSION 3.0) · g++ · Make

```bash
git clone https://github.com/T0-kyo/tokyo-games-center.git
cd tokyo-games-center
mkdir build && cd build
cmake -S .. -B . -G "Unix Makefiles"
make && ./Game
```
(or chckout the latest Release to start playing)

### Windows

A prebuilt executable is provided for convenience. No installation required.

Download TokyoGames.zip from the latest Release.

Extract the contents to a folder of your choice.

Run the game via bin/Game.exe.

Note: Do not move the .exe out of the bin folder, as it requires the .dll files and the Assets folder (located one level up) to function correctly.

---

## ◈ Documentation

```
Documentation/
├── UML-Diagrams/      ← Class diagram and state flow diagram
├── Design/            ← Architecture and design details
└── Screenshots/       ← Gameplay screenshots
```

---

## ◈ The Team

<div align="center">

| Role | Name |
|------|------|
| 🏗️ **Lead Developer** — Architecture, Engine, Logic & States | Al-Hussain Haitham · [`T0-kyo`](https://github.com/T0-kyo) |
| 🎨 **Assets & UI Design** | Ahmed Youssef |
| 🔧 **Technical Support** | Ali Mohamed & Ahmed Youssef |

</div>

---

## ◈ License

This project originated as a college assignment and was later expanded into a personal project.

**MIT License.**

---

<div align="center">

*Built with C++ · Powered by SFML*

</div>
