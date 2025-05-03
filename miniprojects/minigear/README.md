# 🎮 MiniGear

This project is an emulator for the Master System/Game Gear written in C. The goal is to emulate the CPU, PPU, and basic sound hardware of the system. This is a learning project to better understand hardware emulation at a low level.

---

## 🧪 How to Build

### Dependencies:
- **GCC or Clang**
- **SDL2** (on Windows, install via MSYS2: `pacman -S mingw-w64-ucrt-x86_64-SDL2`)
- **CMake** (optional if you prefer CMake for larger projects)

```bash
cd minigear/
make
./minigear-test.exe

## 🧠 Features

    CPU: Emulates the Zilog Z80 CPU (currently minimal instruction set support).

    Graphics: Basic PPU rendering to SDL2 (no advanced video modes yet).

    Audio: Minimal audio support via SDL2 mixer (sound effects in the future).

## 🛠️ Goals

    Learn low-level emulator development and memory mapping.

    Experiment with CPU/PPU cycles and basic audio emulation.

    Implement a framework for future game compatibility.

## 📦 License

MIT License. Feel free to modify and use for personal projects.