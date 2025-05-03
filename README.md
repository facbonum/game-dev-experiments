# 🎮 Game Dev Experiments

This repository is a structured collection of small C programming experiments and mini-projects focused on real-time game development, emulator building, and low-level systems programming.

The goal is to **learn by building**, focusing on:
- SDL2 rendering and audio
- Retro-style graphics and logic
- Save/load mechanics and memory manipulation
- Timed action gameplay and puzzle prototypes
- Emulator development (e.g., Sega Master System/Game Gear)

---

## 📁 Project Structure

```text
game-dev-experiments/
├── README.md
├── Makefile              # Optional: master Makefile to build all/selected projects
├── snippets/             # One-file test programs
│   ├── main.c            # Each folder has its own Makefile
│   └── ...
├── miniprojects/         # Larger experiments with multiple .c/.h files
│   ├── pong-clone/
│   │   ├── src/
│   │   ├── include/
│   │   └── Makefile
│   ├── minigear_emulator/
│   │   ├── src/
│   │   ├── include/
│   │   └── Makefile
├── libs/                 # Reusable libraries/helpers
├── assets/               # Fonts, sprites, etc.
└── build/                # (Optional) Compiled .exe outputs
```

---

## 🚀 Building Projects

### 🧪 One-File Snippets

```bash
cd snippets/save-load/
make
./save-load-test.exe
```

### 🎮 Mini Projects (Multi-file)

```bash
cd miniprojects/pong-clone/
make
./pong-clone-test.exe
```

> SDL2 must be installed. On Windows + MSYS2:  
> `pacman -S mingw-w64-ucrt-x86_64-SDL2`

---

## 📦 Dependencies

All projects require:
- **GCC or Clang** (MinGW preferred on Windows)
- **SDL2**
- Optionally: SDL2_ttf, SDL2_image for some future tests

---

## 🧠 Goals

- Build a personal toolbox of game programming ideas
- Learn efficient C through real constraints (e.g., memory size, speed)
- Implement emulator CPU/PPU/sound logic from scratch
- Practice clean build structures and Makefiles

---

## 📚 License

MIT License. Feel free to use these experiments as a base or reference.
