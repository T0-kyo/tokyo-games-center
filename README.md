<div align="center">

```

████████╗ ██████╗ ██╗  ██╗██╗   ██╗ ██████╗     ██████╗  █████╗ ███╗   ███╗███████╗███████╗
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
![Status](https://img.shields.io/badge/Status-InProgress-brightgreen?style=for-the-badge)

</div>

<!--- Add gameplay GIF or video here --->

---

## ◈ Overview

Tokyo Games Center is a desktop game suite featuring 13 Tic Tac Toe variants — each with its own rules, board layout, and logic. The project was built entirely from scratch in C++ using SFML for rendering, including a custom game engine, a stack-based state machine, and a full set of hand-crafted sprites and UI assets. It started as a college assignment and grew into something bigger.

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

### Windows

A prebuilt executable will be included with all required dependencies.

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
| 🏗️ **Lead Developer** — Architecture, Engine, Logic & States | Alhussain Haitham · [`T0-kyo`](https://github.com/T0-kyo) |
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
