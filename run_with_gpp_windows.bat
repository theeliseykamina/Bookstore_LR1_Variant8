@echo off
cd /d "%~dp0"
where g++ >nul 2>nul
if errorlevel 1 (
  echo g++ is not in PATH. Run Bookstore_LR1.cbp in Code::Blocks with MinGW.
  pause
  exit /b 1
)
if not exist build mkdir build
g++ -std=c++17 -Wall -Wextra src\Base.cpp src\Book.cpp src\Textbook.cpp src\Stationery.cpp src\Keeper.cpp src\Input.cpp src\main.cpp -o build\bookstore.exe
if errorlevel 1 (
  echo Compilation failed.
  pause
  exit /b 1
)
build\bookstore.exe
pause
