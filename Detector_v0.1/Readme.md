# 🕵️‍♂️ Detector-V0.1
- Solves the sub-pattern recognition problem of the [Detector_v0.0](../Detector_v0.0), instead recognizes the exact pattern or the super-patterns.

<p align="center">
  <img src="Images/Sub-pattern Disrecognition.png" alt="Pattern Detector_v0.1 Output" width="1000">
</p>

<p align="center">
  Detector does not recognizes sub-pattern
</p>

## 🧠Decision Maker
- This version checks equivalence between Weight Grid W<sub>rc</sub> and Output Grid O<sub>rc</sub> as opposed to between Input Grid A<sub>rc</sub> and Ouptut Grid O<sub>rc</sub> in Detector_v0.0.
- This Sets a lower bound below which pattern cannot be recognized.
- Mathematical Behaviour:-
    - Input **Recognized**
        - O<sub>rc</sub> = W<sub>rc</sub>
        - O<sub>rc</sub> ⊆ A<sub>rc</sub>
        - W<sub>rc</sub> ⊆ A<sub>rc</sub>
       
    - Input **not recognized**
       - O<sub>rc</sub> ≠ W<sub>rc</sub>
       - O<sub>rc</sub> ⊈ A<sub>rc</sub>
       - W<sub>rc</sub> ⊈ A<sub>rc</sub>
       
<p align="center">
  <img src="Images/Pattern Recognition.png" alt="Pattern Detector_v0.1 Output" width="1000">
</p>

<p align="center">
  Detector recognizes pattern
</p>
