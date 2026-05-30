# 🔁 Gate-Level Cybernetic Classifier

- `Progress:`Implemented a feedback-driven adaptive learning binary-classifier that based on error input autonomously alter its decision boundary by implementing [Max-Initialized Decremental Search](Detector_v1.1/Max-Initialized%20Decremental%20Search) (MIDS) and resets the control loop for repeated adaptive cycles.

<p align="center">
  <img src="Detector_v1.1/Max-Initialized%20Decremental%20Search/Videos/Cybernetic%20Feedback%20Driven%20Adaptive%20Learning-16Hz.gif" alt="Adaptive Learning Demonstration" width="1500">
</p>

<p align="center">
   <sub></b> 🤖 Adaptive learning system implementing MIDS algorithm
</p>

## ⚙️ Implementation Stack
![Verilog](https://img.shields.io/badge/Verilog-FFEA00?style=for-the-badge&logoColor=black)
![Logisim Circuits](https://img.shields.io/badge/Logisim%20Circuits-00C853?style=for-the-badge)

## 📈 Planned Progression
- **Stage 0 (v0.x)**: Strict Boolean pattern relation analyzer. No learning, no noise tolerance, decision boundaries fixed by structural wiring.
- **Stage 1 (v1.0)**: Popcount based similarity and a variable threshold to alter the decision boundary. Introduces noise tolerance and ability to change the decision output without structural changes.
- **Stage 2 (v1.1)**: Cybernetic Feedback-driven adaptive learning. System alters its decision boundary based on external feedback to correct its decision output.
   - [MIDS Algorithm](Detector_v1.1/Max-Initialized%20Decremental%20Search)  **`⟵ DEVELOPED`**
   - [SATU Algorithm ](Detector_v1.1/State%20Aware%20Threshold%20Update) 

## 🧱 Versions Built
- **`Version 0`**: A pattern relation analyzer that classifies how an input pattern relates to a stored pattern, enforces rule based recognition rather than learning.
  - [Detector_v0.0](Detector_v0.0) -> Recognizes the exact pattern and sub-patterns if they are inside the boundary set up by weights-grid.
  - [Detector v0.1](Detector_v0.1) -> Recognizes the exact pattern and super-patterns if they are outside the boundary set up by weights-grid.
  - [Detector v0.2](Detector_v0.2) -> Classifies the input as a sub-pattern, super-pattern, anti-pattern or equivalence precisely through a 2-POV logical analysis.

- **`Version 1`**: Pop-count based judgement against a variable Threshold instead of perfect equivalence check and cybernetic feedback-driven adaptive learning. 
  - [Detector_v1.0](Detector_v1.0) -> Recognizes the pattern if total number of matched pixels are greater than the set threshold which can vary giving us ability to control the decision output.
  - [Detector_v1.1](Detector_v1.1) -> A feedback-driven adaptive system that autonomously adjusts its decision boundary to correct its output, using algorithms optimized for hardware constraints.
    
<p align="center">
  <img src="Detector_v1.0/images/Block-Diagram.png" alt="Block-Diagram" width="900">
</p>

<p align="center">
  <sub></b> 🧩 Block Diagram - Detector_v1.0 (Manually Alterable Decision Boundary)
</p>

## 🧠 Adaptive Learning Algorithms 
- [Max-Initialized Decremental Search (MIDS)](Detector_v1.1/Max-Initialized%20Decremental%20Search)
- [State Aware Threshold Update (SATU)](Detector_v1.1/State%20Aware%20Threshold%20Update)

| Property | MIDS | SATU |
|---|---|---|
| Correction Speed | O(N) | O(1) |
| State Awareness | None | Current & desired output |
| Direction | Always starts from max, decrements | Sets to M or M-1 as needed |
| Initialization Bias | Instant correction for false positives | None |
| Hardware Complexity | Low - decrementer only | Higher - decrementer + decision logic |
| Guaranteed Convergence | Yes | Yes |

### 🎯 Convergence Proofs
- [MIDS Convergence Proof](https://github.com/KARAN-D05/Gate-Level-Perceptron/tree/main/Detector_v1.1/Max-Initialized%20Decremental%20Search#-convergence-proof)
- [SATU Convergence Proof](https://github.com/KARAN-D05/Gate-Level-Perceptron/tree/main/Detector_v1.1/State%20Aware%20Threshold%20Update#-convergence-proof)

<p align="center">
  <img src="Detector_v1.1/images/Speed_Complexity.png" alt="Correction Speeds" width="700">
</p>

<p align="center">
   <sub></b> ⏱️ Correction Speed Complexity Comparison
</p>

## 💻 Verilog Implementation

### 🎯 Strict Boolean Matching
- [Detector_v0.0](Detector_v0.0/Verilog-Implementation)

<div align="center">
    <img src="Detector_v0.0/Verilog-Implementation/images/Waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
     <sub></b> <p> Equivalence & Sub-Pattern Recognition 🔹 </p>
</div>

- [Detector_v0.1](Detector_v0.1/Verilog-Implementation)

<div align="center">
    <img src="Detector_v0.1/Verilog-Implementation/images/waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
    <sub></b> <p> Equivalence & Super-Pattern Recognition 🟦 </p>
</div>

- [Detector_v0.2](Detector_v0.2/Verilog-Implementation)

<div align="center">
    <img src="Detector_v0.2/Verilog-Implementation/images/waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
   <sub></b> <p> Equivalence & Super & Sub & Anti-Pattern Recognition 🔹🟦 </p>
</div>

### 🔄 Popcount-Based Adaptive Learning

- [Detector_v1.0](Detector_v1.0/Verilog-Implementation)

<div align="center">
    <img src="Detector_v1.0/Verilog-Implementation/images/waveform.png" 
         alt="Pattern Detector Output" 
         width="1500">
    <sub></b> <p> Manually Alterable Decision Boundary ⚖️ </p>
</div>

## 🛠️Current Development:
- Stage 2 in progress - MIDS: Developed ✓ | SATU: In Development

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

## 📜License
- Source code and HDL files are licensed under the MIT License.
- Documentation, diagrams, images, and PDFs are licensed under Creative Commons Attribution 4.0 (CC BY 4.0).
