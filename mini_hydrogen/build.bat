@echo off
echo Cleaning previous build...
del out.asm 2>nul
del out.obj 2>nul   
del out.exe 2>nul
del hydro.exe 2>nul

echo Compiling the compiler...
g++ main.cpp -o hydro.exe
if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b
)

echo Running the compiler on test.hy...
hydro.exe test.hy
if %errorlevel% neq 0 (
    echo Compiler run failed!
    pause
    exit /b
)

echo Assembling and linking output...
"C:\Users\dell\Downloads\nasm-2.16rc12-win64\nasm-2.16rc12\nasm.exe" -fwin64 out.asm -o out.obj
g++ out.obj -o out.exe
if %errorlevel% neq 0 (
    echo Linking failed!
    pause
    exit /b
)

echo ===== RUNNING COMPILED PROGRAM =====
out.exe

echo ===== PROGRAM ENDED =====
pause
