# 🕵️‍♂️ Detector-V0.0
- A configurable pattern detection machine built entirely from logic gates. It uses a weight array to filter the input pattern and a decision-making stage to check recognition. 

<p align="center">
  <img src="Images/Pattern-Recognition-2.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector recognize alphabet T
</p>


## 🔲Input Grid
- A 4×4 Grid used to input the pattern which is visible through the LED Grid.
  - A<sub>rc</sub> is the Input grid element, where 0&le;r&le;3 and 0&le;c&le;3.
  - A-W Link exists between each individual element of input grid to the corresponding element of weight grid, A<sub>rc</sub>-W<sub>rc</sub>.

## #️⃣Weight Grid
- A 4×4 Grid used to configure the machine for detection of a particular pattern.
  - Uses AND Gates with the the inputs along with a binary weight pin.
  - It acts as a filter, and only allows the input to the output side only if the corresponding weight is 1/High and don't allow the rest.
  - W<sub>rc</sub> is the weight grid element, where 0&le;r&le;3 and 0&le;c&le;3.

## ➡️Output Grid
- A 4×4 grid that shows output, that is equal to O<sub>rc</sub> = A<sub>rc</sub> ∧ W<sub>rc</sub>.

## 🧠Decision Maker
- A 4×4 grid made up of XNOR gates that checks for exact equivalence between input pattern and the output pattern.
- This sets an upper bound above which pattern cannot be recognized.
- Equivalence Check = (A<sub>00</sub> ⊙ O<sub>00</sub>) ∧ (A<sub>01</sub> ⊙ O<sub>01</sub>) ∧ ... ∧ (A<sub>33</sub> ⊙ O<sub>33</sub>)
   - If Equivalence Check -> 1; Pattern recognized
   - If Equivalence Check -> 0; Pattern not recognized
- Input **Recognized** if the input pattern A<sub>rc</sub> &subseteq; W<sub>rc</sub>.
- Input **Not Recognized** if the input pattern A<sub>rc</sub> &nsubseteq; W<sub>rc</sub>.

<p align="center">
  <img src="Images/super-pattern-disrecognition.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector does not recognize super-pattern
</p>

<p align="center">
  <img src="Images/Sub-pattern recognition.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector recognizes Sub-pattern
</p>

## ⚠️Limitations
- Looks for perfect equivalence between input and filtered output.
- No way to change its decision output without changing its structural wiring.
- No scoring or noise tolerance - expects clean inputs.
- My attempt at a perceptron ended up as a binary pixel filter + comparator. **Basically v0.0 is a machine the George Orwell's 1984 Thought Police would approve of 😂**.

## 🔮Next Version 
- Reverses the Mathematical behaviour of current version(A<sub>rc</sub> &subseteq; W<sub>rc</sub>) for recognition to A<sub>rc</sub> ⊇ W<sub>rc</sub>.
- Recognizes Equivalence and Super-Patterns.
- [Check this out](https://github.com/KARAN-D05/Gate-Level-Perceptron/tree/main/Detector_v0.1)
