# 🕵️‍♂️ Detector-V0.1
- Solves the sub-pattern recognition problem of the [Detector_v0.0](../Detector_v0.0), instead recognizes the exact pattern or the super-patterns.

<p align="center">
  <img src="Images/Sub-pattern Disrecognition.png" alt="Pattern Detector_v0.1 Output" width="1000">
</p>

<p align="center">
  Detector does not recognizes sub-pattern
</p>

## 🔲Input Grid
- A 4×4 Grid used to input the pattern which is visible through the LED Grid.
  - A<sub>rc</sub> is the Input grid element, where 3&le;r&le;0 and 3&le;c&le;0.
  - A-W Link exists between each individual element of input grid to the element of weight grid, A<sub>rc</sub>-W<sub>rc</sub>.

## #️⃣Weight Grid
- A 4×4 Grid used to configure the machine for detection of a particular pattern.
  - Uses AND Gates with the the inputs along with a binary weight pin.
  - It acts as a filter, and only allows the input to the output side only if the corresponding weight is 1/High and don't allow the rest.
  - W<sub>rc</sub> is the weight grid element, where 3&le;r&le;0 and 3&le;c&le;0.

## ➡️Output Grid
- A 4×4 grid that shows output, that is equal to O<sub>rc</sub> = A<sub>rc</sub> ∧ W<sub>rc</sub>.

## 🧠Decision Maker
- This version checks equivalence between Weight Grid W<sub>rc</sub> and Output Grid O<sub>rc</sub> as opposed to between Input Grid A<sub>rc</sub> and Ouptut Grid O<sub>rc</sub> in Detector_v0.0.
- This Sets a lower bound below which pattern cannot be recognized.
- Equivalence Check = (A<sub>00</sub> ⊙ O<sub>00</sub>) ∧ (A<sub>01</sub> ⊙ O<sub>01</sub>) ∧ ... ∧ (A<sub>33</sub> ⊙ O<sub>33</sub>)
   - If Equivalence Check -> 1; Pattern recognized
   - If Equivalence Check -> 0; Pattern not recognized
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

