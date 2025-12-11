# ✨ Detector-V0.0
- A primitive and configurable pattern detector made using logic gates to implement weight array and decision making.

<p align="center">
  <img src="Images/Pattern-Recognition-2.png" alt="Pattern Detector Output" width="1000">
</p>

<p align="center">
  Detector recognizes alphabet T
</p>


## Input Grid
- A 4×4 Grid used to input the pattern which is visible through the LED Grid.
- A<sub>rc</sub> is the Input grid element, where 4&le;r&le;0 and 4&le;c&le;0
- A-W Link exists between each individual element of input grid to the element of weight grid, A<sub>rc</sub>-W<sub>rc</sub>.

## Weight Grid
- A 4×4 Grid used to configure the machine for detection of a particular pattern.
- It acts as a filter, and only allows the input to the output side only if the corresponding weight is 1/High and don't allow the rest.
- W<sub>rc</sub> is the weight grid element, where 4&le;r&le;0 and 4&le;c&le;0

## Output Grid
- A 4×4 grid that shows output, that is equal to O<sub>rc</sub> = A<sub>rc</sub> × W<sub>rc</sub>
