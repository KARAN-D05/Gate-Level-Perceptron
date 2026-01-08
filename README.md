# 🔍 Gate Level Perceptron
- This project explores pattern recognition at logic-gate level.

- It began as an attempt to build **`perceptron-like system`** for recognizing patterns, but early versions evolved into a strictly logical pattern relation anlyzer using strict boolean logic.

- Subsequent versions will transition from rigid equivalence checks to popcount-based scoring and threshold decisions, moving the architecture toward a true perceptron and, eventually self learning behaviour.

<div align="center">
    <img src="Detector_v0.2/Images/equivalence.png" 
         alt="Pattern Detector Output" 
         width="1000">
    <p>Detector_v0.2 detects Equivalence✅ </p>
</div>


## 🧱 Versions Built
- **Version 0**: A pattern relation analyzer that classifies how an input pattern relates to a stored pattern, enforces rule based recognition rather than learning.
  - [Detector_v0.0](Detector_v0.0) -> Recognizes the pattern and sub-patterns if they are inside the boundary set up by weights-grid.
  - [Detector v0.1](Detector_v0.1) -> Recognizes the pattern and super-patterns if they are outside the boundary set up by weights-grid.
  - [Detector v0.2](Detector_v0.2) -> Classifies the input as a sub-pattern, super-pattern, anti-pattern or equivalence precisely through a 2-POV logical analysis.

## 🔜 Future Versions
- Popcount based judgement instead of perfect equivalence check.

 ## 🛠️Current Development:
 - Population Counter Developed and operation verified
 - Working on a Comparator for Measuring the Pop-count(M) to compare with the threshold(θ) to make decisions
