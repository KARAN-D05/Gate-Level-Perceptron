# 🕵️‍♂️ Detector-V0.1
- Solves the sub-pattern recognition problem of the [Detector_v0.0](../Detector_v0.0) 

<p align="center">
  <img src="Images/Sub-pattern Disrecognition.png" alt="Pattern Detector_v0.1 Output" width="1000">
</p>

<p align="center">
  Detector does not recognizes sub-pattern
</p>

## 🧠Decision Maker
- This version checks equivalence between Weight Grid W<sub>rc</sub> and Output Grid O<sub>rc</sub> as opposed to between Input Grid A<sub>rc</sub> and Ouptut Grid O<sub>rc</sub> in Detector_v0.0.
- This takes the allowed weight pattern as a law as opposed to as a limit.
- Mathematical Behaviour:-
    - Input **Recognized** if O<sub>rc</sub> = W<sub>rc</sub>
    - Input **not recognized** if O<sub>rc</sub> &neq; W<sub>rc</sub>

<p align="center">
  <img src="Images/Pattern Recognition.png" alt="Pattern Detector_v0.1 Output" width="1000">
</p>

<p align="center">
  Detector recognizes pattern
</p>
