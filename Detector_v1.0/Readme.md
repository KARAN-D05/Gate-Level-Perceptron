# ⚖️ POP-Count Based Detector-V1.0
- It recognizes the pattern if the number of `Matched Pixels` are greater than the set `Threshold`

## 🧠 Working Principle
- It calculates the total number of matched pixels using a Population-counter.
   - **👥 Population Counter:**

  <p align="center">
     <img src="images/Population Counter.png" alt="Population Counter" width="1200">
 
      - It is a module made up of 60 Half-adders, that counts total number of it's inputs that are 1.
      - It is based on principle of succesively adding bits of same Weight until we have compressed that set of bits with same weight W into a single bit of weight W.
      - A half adder has two outputs, SUM and CARRY, if weight of output of SUM is W then weight of output of CARRY is 2W
  





