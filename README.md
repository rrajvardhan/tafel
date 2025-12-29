# tafel

A whiteboard application built with **C++** and **Qt**.

## Overview

* Desktop whiteboard application written in C++
* Built using Qt Widgets
* Canvas-based freehand drawing
* Color palette and stroke controls
* Minimal, distraction-free UI

## A Quick Look

<img width="1914" height="1074" alt="2025-12-29-094054_hyprshot" src="https://github.com/user-attachments/assets/785fdf45-d684-48d3-a172-5de008f6fa67" />

## Build Instructions

### Linux

You’ll need the following dependencies installed:

* Qt 6 (Widgets module)
* CMake
* A C++17 compatible compiler
* Make / Ninja (or equivalent build tool)

Install Qt and build tools using your package manager (`pacman`, `apt`, `dnf`, etc).

> Package names may vary by distro. On some systems, Qt is split across multiple packages.

```bash
sudo pacman -S qt6-base qt6-tools cmake make
```

Then clone, build, and run:

```bash

git clone https://github.com/rrajvardhan/tafel
cd tafel
mkdir build && cd build
cmake ..
make
./main

```

> If CMake can’t find a dependency, you may need to manually specify include/library paths or adjust your environment variables.

### Windows (Untested, but expected to work.)

You’ll need the following dependencies installed:

* Qt 6 (Widgets and Qt Creator)
* A C++17 compatible compiler
* CMake
* MinGW
* Git

> Follow the **standard Qt installation process** (Qt Creator + MinGW toolchain).

```bash
git clone https://github.com/rrajvardhan/tafel

```

1. Open **Qt Creator**
2. Go to **File → Open File or Project**
3. Select `CMakeLists.txt` in the `tafel/` directory
4. Choose **Desktop Qt 6.x MinGW 64-bit**
5. Click **Configure Project**
6. Press **Ctrl + B** to build
7. Press **Ctrl + R** to run

> To bundle the application, use Qt’s standard deployment tool `windeployqt`.
