# 🔍 Gate Level Perceptron
- This project explores pattern recognition at logic-gate level.
  
- It began as an attempt to build **`perceptron-like system`** for recognizing patterns, but early versions evolved into a strictly logical pattern relation analyzer using strict boolean logic.
  
- Subsequent versions transitioned from rigid equivalence checks to popcount-based scoring and threshold decisions, moving the architecture towards self learning behaviour.

<p align="center">
  <img src="Detector_v1.0/images/Block-Diagram.png" alt="Block Diagram" width="1500">
</p>

<p align="center">
  🧩 Block-Diagram - Detector_v1.0 
</p>

## ⚙️ Implementation Stack
![Verilog](https://img.shields.io/badge/Verilog-FFEA00?style=for-the-badge&logoColor=black)
![Logisim Circuits](https://img.shields.io/badge/Logisim%20Circuits-00C853?style=for-the-badge)

## 🧱 Versions Built
- **`Version 0`**: A pattern relation analyzer that classifies how an input pattern relates to a stored pattern, enforces rule based recognition rather than learning.
  - [Detector_v0.0](Detector_v0.0) -> Recognizes the pattern and sub-patterns if they are inside the boundary set up by weights-grid.
  - [Detector v0.1](Detector_v0.1) -> Recognizes the pattern and super-patterns if they are outside the boundary set up by weights-grid.
  - [Detector v0.2](Detector_v0.2) -> Classifies the input as a sub-pattern, super-pattern, anti-pattern or equivalence precisely through a 2-POV logical analysis.

- **`Version 1`**: Pop-count based judgement against a variable Threshold instead of perfect equivalence check, takes us one step closer to self-learning adaptive machines.
  - [Detector_v1.0](Detector_v1.0) -> Recognizes the pattern if total number of matched pixels are greater than the set threshold. 

<p align="center">
  <img src="Detector_v1.0/images/Recognition.png" alt="Recognition" width="900">
</p>

<p align="center">
  θ = 7 & M = 8, M > θ: hence Pattern is recognized ✅
</p>

<p align="center">
  <img src="Detector_v1.0/images/Non-Recognition.png" alt="Non-Recognition" width="900">
</p>

<p align="center">
  θ = 9 & M = 8, M ≤ θ: hence Pattern is not recognized ❌
</p>

## 💻 Verilog Implementation
- [Detector_v0.0](Detector_v0.0/Verilog-Implementation)

<div align="center">
    <img src="Detector_v0.0/Verilog-Implementation/images/Waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
    <p> Equivalence & Sub-Pattern Recognition 🔹 </p>
</div>

- [Detector_v0.1](Detector_v0.1/Verilog-Implementation)

<div align="center">
    <img src="Detector_v0.1/Verilog-Implementation/images/waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
    <p> Equivalence & Super-Pattern Recognition 🟦 </p>
</div>

- [Detector_v0.2](Detector_v0.2/Verilog-Implementation)

<div align="center">
    <img src="Detector_v0.2/Verilog-Implementation/images/waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
    <p> Equivalence & Super & Sub & Anti-Pattern Recognition 🔹🟦 </p>
</div>

## 🛠️Current Development:
 - Population Counter Developed and operation verified ✓
 - Comparator Developed for comparing the Pop-count(M) with the threshold(θ) to make decisions ✓
 - Pop-Count based pattern detector developed and tested ✓
 - Detector Version 0 series implemented in Verilog ✓

## 🔜 Future Versions
- Feedback-driven adaptation on top of the existing popcount-based judgement mechanism.
- Automatic threshold adjustment based on feedback which would allow the detector to gradually converge towards an appropriate threshold.
- It would form basis of simple self-learning adaptive system. 

## ⬇️ Download This Repository

### 🪟 Windows
Download → [download_repos.bat](./download_repos.bat)
``` 
Double-click it and pick the repo(s) you want.
```

### 🐧 Linux / macOS
Download → [download_repos.sh](./download_repos.sh)
```
bash

chmod +x download_repos.sh
./download_repos.sh
```

> Always downloads the latest version.

## 🛠️ Toolchain & Repo Utilities - Built to make navigating and interacting with this repo easier

This project includes a built-in reference manual for the detector architecture that can be queried directly from your terminal. View full manual: [detector-manual](https://github.com/KARAN-D05/Gate-Level-Perceptron/tree/main/detector-manual)

**Linux / Mac:**
```bash
curl -O https://raw.githubusercontent.com/KARAN-D05/Gate-Level-Perceptron/main/detector-manual/run-detector-manual.sh
chmod +x run-detector-manual.sh
./run-detector-manual.sh
```

**Windows:**
```powershell
Invoke-WebRequest -Uri "https://raw.githubusercontent.com/KARAN-D05/Gate-Level-Perceptron/main/detector-manual/run-detector-manual.ps1" -OutFile "run-detector-manual.ps1"
powershell -ExecutionPolicy Bypass -File run-detector-manual.ps1
```

### 🔧 portmap - Verilog Port Extractor

`portmap` is a lightweight CLI tool that extracts port definitions (`input`, `output`, `inout`) from Verilog modules and presents them in a clean table or Markdown format.

#### 🔗 Source
https://github.com/KARAN-D05/portmap-HDL/blob/main/portmap.nim

#### 📦 Release (Download Binary)
https://github.com/KARAN-D05/portmap-HDL/releases/tag/v1.0.0

#### 🚀 Usage
```bash
portmap file.v
portmap file.v --md
```

### 🧰 Repo Filetree Generator
[Filetree](https://github.com/KARAN-D05/portmap-HDL/tree/main/utils) - A repository file tree generator that prints a visual directory tree with file-type icons and a file count breakdown by extension (`.v`, `.circ`, `.md`, `.py` and more).
  
**Utils (Portmap + Filetree)- Fetched automatically as a utils package alongside any repo download - includes portmap binaries, filetree, and source code via [download_repos.bat](download_repos.bat) / [download_repos.sh](download_repos.sh).**

## 📜License
- Source code and HDL files are licensed under the MIT License.
- Documentation, diagrams, images, and PDFs are licensed under Creative Commons Attribution 4.0 (CC BY 4.0).
