# Hydrogen Compiler

A custom compiler for the **Hydrogen programming language** built from scratch.

## Objective
Design and implement a compiler that:
- Supports **variable declarations** (`let`)
- Supports **arithmetic operations** (`+`, `-`, `*`, `/`)
- Handles **print statements** (`print`)
- Generates **NASM assembly code** targeting Windows 64-bit
- Produces a final executable using NASM + GCC

## Tech Stack
- **C++** (compiler implementation)
- **NASM assembler** (assembly generation)
- **MinGW GCC** (linking to produce `.exe`)
- **Visual Studio Code** (development)
- **Batch scripting** (`build.bat` for automation)

## ⚙ Project Architecture
```
Hydrogen source (.hy)
   ↓
Tokenizer → Parser → Code Generator
   ↓
NASM → .obj → GCC linker → .exe
```

## How to Build & Run
```bash
# Build manually
g++ src/main.cpp -o hydro.exe
hydro.exe your_program.hy

# Or if using build.bat
build.bat
```
✅ Make sure **NASM** and **GCC (MinGW)** are installed and added to PATH.

## 📝 Example Hydrogen Code
```hydrogen
let a = 5 + 3
print a
```
➡ Compiles and produces output via `out.exe`.

## Future Scope
- Add control structures (if-else, loops)
- Functions and procedures
- More data types (string, float)
- IDE or GUI for Hydrogen

## 📂 Project Structure
```
hydrogen-compiler/
 ├── src/
 │    ├── main.cpp
 │    ├── tokenizer.hpp
 │    ├── parser.hpp
 │    ├── one.l.cpp
 ├── build.bat      # Build automation script
 ├── README.md      # Project info
 ├── .gitignore     # Ignore unnecessary files
```

## 🔗 Tools Used
- [NASM](https://www.nasm.us/)
- [MinGW](http://www.mingw.org/)

## 💡 License
This project is for educational use as part of academic coursework.
