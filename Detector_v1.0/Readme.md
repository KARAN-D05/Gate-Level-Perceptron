# 📊 POP-Count Based Detector-V1.0
- It recognizes the pattern if the number of `Matched Pixels (M)` are greater than the set `Threshold(θ)`
- Unlike the perfect equivalence check we have set a threshold above which the pattern is recognized and the threshold can vary

## 🧬 The McCulloch-Pitts Artificial Neuron
- A simple computational model of a biological neuron
- `Biological neuron:`
   - receives inputs via its tree-like projections called dendrites
   - The cell body then performs computation on these inputs
   - Based on results of the computation, it may send an electrical signal through the axon toward axon-terminals which in turn communicate it to other neurons
   - This forms a biological neural network
- `MCP Neuron:`
   - Warren McCulloch and Walter Pitts proposed a simple logical model of a neuron
   - It sums the inputs say A and B where A,B ∈ {0,1}: M = A + B
   - It has a threshold θ, if:
      - M ≥ θ -> Neuron Fires, Output = 1
      - M < θ -> Neuron Doesn't Fires, Output = 0
   - Based on the value of θ, we can implement any logic gate like AND, OR
   - For AND gate θ = 2, so the neuron will only output 1 if both the inputs are 1. ( 1(A) + 1(B) ≥ 2(θ) ), similarly for OR gate θ = 1
- The POP-Count based Detector's subsystem consisting of Pop-counter, Threshold pins, Decision-Maker is isomorphic to the MCP Neuron
   - 16 Inputs from XNOR grid to pop-counter is biologically equivalent to the Dendrites
   - The POP-Counter is biologically equivalent to the Cell Body
   - Decision-Maker is biologically equivalent to whether an electrical signal is sent or not based on the threshold
   - The Output LED is biologically equivalent to the axon
- Even though my machine fires/recognizes if M is strictly greater than θ, for ensuring more confidence during pattern recognition

## 👥 Population Counter
- It calculates the total number of matched pixels (M)
- It is a module made up of 64 Half-adders, that counts total number of it's inputs that are 1
- It is based on principle of successively adding bits of same Weight until we have compressed that set of bits with same weight W into a single bit of weight W
- A half adder has two outputs, SUM and CARRY, if weight of output of SUM is W then weight of output of CARRY is 2W
- It can also be implemented using full-adders which will lead to same compression employing less number of full-adders than half-adders
 
  - **Logical Implementation:**
        <p>➤ 8 Half-adders divides the 16 inputs into 8 SUM bits of weight 1 and 8 CARRY bits of weight 2 </p> 
        <p>➤ Then we use 4 half-adders to further divide 8 SUM bits of weight 1 into 4 SUM bits and 4 CARRY bits </p>
        <p>➤ As we keep dividing the SUM bits of weight 1 until we are left with a single bit of Weight 1 </p>
        <p>➤ Similarly for bits of weight 2 and succesive weights we repeat the same steps until we reach the single bit of that weight </p>
        <p>➤ If inputs A and B of half adder are of weight W (8), then the SUM bit will be of same weight W (8), and CARRY bit will be of twice the weight 2W (16) of that of the input </p>

<p align="center">
  <img src="images/Population Counter.png" width="1500">
</p>

<p align="center">
 Wallace Tree Based Population Counter - Parallel Reduction of Multiple Bits
</p>

## 🏛️ Decision-Maker
- It is the brain of the machine, it decides if the input pattern is recognized or not.
- For pattern recognition the total number of matched pixels(M) should be strictly greater than the threshold(θ)
   - `Pattern Recognized: M > θ`
   - `Pattern Not Recognized: M ≤ θ`
- Threshold can be set using the T-pins or the Threshold pins, threshold range from 0(0000) - 15 (1111)
- It is essentially a Priority-Encoded Magnitude Comparator that goes high if M is greater than θ
 - **Setting the Threshold(θ):** Use T-pins/Threshold pins to set the threshold as required: (T8 T4 T2 T1), eg:1001 sets the threshold to 9
 - Threshold is not fixed, thus giving us the ability to adjust it accordingly
  
<p align="center">
  <img src="images/Recognition.png" alt="Recognition" width="900">
</p>

<p align="center">
  θ = 7 & M = 8, M > θ: hence Pattern is recognized
</p>

<p align="center">
  <img src="images/Non-Recognition.png" alt="Non-Recognition" width="900">
</p>

<p align="center">
  θ = 9 & M = 8, M ≤ θ: hence Pattern is not recognized
</p>

## ⚖️ XNOR Equivalence Grid
- It is a 4×4 grid made up of 16 XNOR logic gates, each gate performs: A<sub>rc</sub> ⊙ O<sub>rc</sub>​
- A<sub>rc</sub> -> Input Grid
- O<sub>rc</sub> -> Reference Grid
- XNOR gate goes high if both of its inputs are equal hence a pixel match.
- Outputs of the grid are fed into the population counter, which counts the total number of matched pixels.

## 💡One Step Closer to Self-Learning Machines.....
- Instead of perfect equivalence check here we judge based on the score or the number of matched pixels, comparing them to a threshold.
- It is a proof of Concept for self learning machines, in which they can based on feedback adjust their threshold values automatically until they identify the correct threshold for recognition.



