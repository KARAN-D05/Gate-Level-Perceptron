# detector-manual

A built-in reference manual for the Gate Level Perceptron
project. Query the full detector architecture, components
and version history directly from your terminal.

---

## Run on Linux / Mac (Bash)

**Step 1 - Download the script**
```bash
curl -O https://raw.githubusercontent.com/KARAN-D05/Assembler/main/detector-manual/run-detector-manual.sh
```

**Step 2 - Give it permission to execute**
```bash
chmod +x run-detector-manual.sh
```

**Step 3 - Run it**
```bash
./run-detector-manual.sh
```

---

## Run on Windows (PowerShell)

**Step 1 - Download the script**
```powershell
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/KARAN-D05/Assembler/main/detector-manual/run-detector-manual.ps1" -OutFile "run-detector-manual.ps1"
```

**Step 2 - Run it**
```powershell
powershell -ExecutionPolicy Bypass -File run-detector-manual.ps1
```

---

## Requirements

GCC must be installed. Check if you have it:
```
gcc --version
```

If not installed:

| OS            | Command / Link                                            |
|---------------|-----------------------------------------------------------|
| Ubuntu/Debian | `sudo apt install gcc`                                    |
| Mac           | `xcode-select --install`                                  |
| Windows       | https://www.mingw-w64.org then add `C:\MinGW\bin` to PATH |

---

## After First Run

Once compiled you do not need the script again.
Just run the binary directly:

**Linux / Mac:**
```bash
./detector-manual
```

**Windows:**
```powershell
.\detector-manual.exe
```

---

## Usage

Once the program is running, type the version you want:

| Command | Description                                      |
|---------|--------------------------------------------------|
| V0.0    | Binary pixel filter, sub-pattern recognition     |
| V0.1    | Fixes V0.0, super-pattern recognition            |
| V0.2    | Four-way classifier using both POVs              |
| V1.0    | POP-Count based, MCP Neuron isomorphic           |
| all     | Show all versions at once                        |
| search  | Search for a specific component or term          |
| exit    | Quit the program                                 |

You can also search directly from the terminal:
```bash
./detector-manual --search threshold
./detector-manual --search XNOR
./detector-manual --search neuron
```

---

## Files

| File                       | Description                        |
|----------------------------|------------------------------------|
| `detector-manual.c`        | Source code of the manual          |
| `run-detector-manual.sh`   | Bash script for Linux / Mac        |
| `run-detector-manual.ps1`  | PowerShell script for Windows      |

---

*Part of the Gate Level Perceptron project by KARAN-D05*
