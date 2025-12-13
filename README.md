# 🔍 Gate Level Perceptron
- A 4×4 configurable digital logic circuit for **pattern recognition**.
- This is my attempt to understand how machines can detect patterns on a 4×4 binary grid correctly and precisely from the bottom up from logic gates.

<div align="center">
    <img src="Detector_v0.2/Images/equivalence.png" 
         alt="Pattern Detector Output" 
         width="1000">
    <p>Detector_v0.2 detects Equivalence✅ </p>
</div>


## 🧱 Versions Built
- Version 0: A pattern relation analyzer that classifies how an input pattern relates to a stored pattern, enforces logical analysis rather than learning.
  - [Detector_v0.0](Detector_v0.0) -> Recognizes the pattern and sub-patterns if they are inside the boundary set up by weights-grid.
  - [Detector v0.1](Detector_v0.1) -> Recognizes the pattern and super-patterns if they are outside the boundary set up by weights-grid.
  - [Detector v0.2](Detector_v0.2) -> Classifies the sub-pattern, super-pattern, anti-pattern and equivalence precisely through a 2-POV logical analysis.

## 🔜 Future Versions
- Popcount based judgement instead of perfect equivalence check.
