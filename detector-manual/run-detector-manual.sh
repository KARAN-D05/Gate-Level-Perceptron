#!/bin/bash

echo "+--------------------------------------------------+"
echo "|       detector-manual - Bash Installer           |"
echo "+--------------------------------------------------+"

echo ""
echo "Checking for GCC..."
if ! command -v gcc &> /dev/null; then
    echo "[ERROR] GCC not found!"
    echo "  Ubuntu/Debian -> sudo apt install gcc"
    echo "  Mac           -> xcode-select --install"
    exit 1
fi
echo "[OK] GCC found: $(gcc --version | head -1)"

echo ""
echo "Checking for curl..."
if ! command -v curl &> /dev/null; then
    echo "[ERROR] curl not found!"
    echo "  Ubuntu/Debian -> sudo apt install curl"
    exit 1
fi
echo "[OK] curl found."

echo ""
echo "Downloading detector-manual.c from GitHub..."
curl -fsSL -o detector-manual.c \
    https://raw.githubusercontent.com/KARAN-D05/Assembler/main/detector-manual/detector-manual.c

if [ $? -ne 0 ]; then
    echo "[ERROR] Download failed. Check your internet connection."
    exit 1
fi
echo "[OK] Download complete."

echo ""
echo "Compiling..."
gcc detector-manual.c -o detector-manual

if [ $? -ne 0 ]; then
    echo "[ERROR] Compilation failed."
    exit 1
fi
echo "[OK] Compilation successful."

echo ""
echo "Launching detector-manual..."
echo "+--------------------------------------------------+"
echo ""
./detector-manual
