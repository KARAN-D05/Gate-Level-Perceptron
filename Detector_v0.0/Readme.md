# 🕵️‍♂️ Detector-V0.0
A primitive and configurable pattern detector made using logic gates to implement weight array and decision making.
Pattern Detector Output

Detector recognizes alphabet T

## 🔲Input Grid
A 4×4 Grid used to input the pattern which is visible through the LED Grid.
Arc is the Input grid element, where 4≤r≤0 and 4≤c≤0.
A-W Link exists between each individual element of input grid to the element of weight grid, Arc-Wrc.

## #️⃣Weight Grid
A 4×4 Grid used to configure the machine for detection of a particular pattern.
Uses AND Gates with the the inputs along with a binary weight pin.
It acts as a filter, and only allows the input to the output side only if the corresponding weight is 1/High and don't allow the rest.
Wrc is the weight grid element, where 4≤r≤0 and 4≤c≤0.

## ➡️Output Grid
A 4×4 grid that shows output, that is equal to Orc = Arc × Wrc.

## 🧠Decision Maker
A 4×4 grid made up of XNOR gates that checks for exact equivalence between input pattern and the output pattern
Equivalence Check = (A00 ⊙ O00) ∧ (A01 ⊙ O01) ∧ ... ∧ (A44 ⊙ O44)
If Equivalence Check -> 1; Pattern recognized
If Equivalence Check -> 0; Pattern not recognized
Input Recognized if the input pattern Arc ⊆ Wrc.
Input Not Recognized if the input pattern Arc ⊈ Wrc.
Pattern Detector Output

Detector don't recognizes alphabet I

## ⚠️Limitations
It also recognizes the sub-patterns or the garbage patterns of the Weight grid.
Looks for perfect equivalence.
My attempt at a perceptron ended up as a binary pixel filter and comparator. **Basically v0.0 is a machine the George Orwell's 1984 Thought Police would approve of 😂**.
