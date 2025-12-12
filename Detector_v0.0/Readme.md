# 🕵️‍♂️ Detector-V0.0
- A primitive and configurable pattern detector made using logic gates to implement weight array and decision making.

<p align="center">
  <img src="Images/Pattern-Recognition-2.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector recognizes alphabet T
</p>


## 🔲Input Grid
- A 4×4 Grid used to input the pattern which is visible through the LED Grid.
- A<sub>rc</sub> is the Input grid element, where 4&le;r&le;0 and 4&le;c&le;0.
- A-W Link exists between each individual element of input grid to the element of weight grid, A<sub>rc</sub>-W<sub>rc</sub>.

## #️⃣Weight Grid
- A 4×4 Grid used to configure the machine for detection of a particular pattern.
- Uses AND Gates with the the inputs along with a binary weight pin.
- It acts as a filter, and only allows the input to the output side only if the corresponding weight is 1/High and don't allow the rest.
- W<sub>rc</sub> is the weight grid element, where 4&le;r&le;0 and 4&le;c&le;0.

## ➡️Output Grid
- A 4×4 grid that shows output, that is equal to O<sub>rc</sub> = A<sub>rc</sub> × W<sub>rc</sub>.

## 🧠Decision Maker
- A 4×4 grid made up of XNOR gates that checks for exact equivalence between input pattern and the output pattern
- Equivalence Check = (A<sub>00</sub> ⊙ O<sub>00</sub>) ∧ (A<sub>01</sub> ⊙ O<sub>01</sub>) ∧ ... ∧ (A<sub>44</sub> ⊙ O<sub>44</sub>)
   - If Equivalence Check -> 1; Pattern recognized
   - If Equivalence Check -> 0; Pattern not recognized
- Input **Recognized** if the input pattern A<sub>rc</sub> &subseteq; W<sub>rc</sub>.
- Input **Not Recognized** if the input pattern A<sub>rc</sub> &nsubseteq; W<sub>rc</sub>.

<p align="center">
  <img src="Images/Pattern-Recognition-1.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector don't recognizes alphabet I
</p>

## ⚠️Limitations
- It also recognizes the sub-patterns or the garbage patterns of the Weight grid.
- Looks for perfect equivalence.
- I tried to make a self-learning unit inspired by Rosenblatt’s perceptron, but since my weights were binary instead of analog, it basically became a pixel filter 😂. Next version: popcount-based judgment system!
