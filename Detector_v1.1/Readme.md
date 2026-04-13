# 🔄 Feedback-Driven Adaptive Learning 
- Introduces feedback-driven adaptation on top of [Detector_v1.0](../Detector_v1.0), a popcount based judgement system with manually alterable decision boundary.
- Automatic threshold adjustment based on error signal which would allow the detector to gradually converge towards an appropriate threshold to correct the recognition output.
- It would form basis of a cybernetic self-learning adaptive system that would be capable of altering its decision boundaries.

## 🧠 Adaptive Learning Algorithms 
- [Max-Initialized Decremental Search (MIDS)](Max-Initialized%20Decremental%20Search)
- [State Aware Threshold Update (SATU)](State%20Aware%20Threshold%20Update)

| Property | MIDS | SATU |
|---|---|---|
| Correction Speed | O(N) | O(1) |
| State Awareness | None | Current & desired output |
| Direction | Always starts from max, decrements | Increments or decrements as needed |
| Hardware Complexity | Low - decrementer only | Higher - incrementer + decrementer + decision logic |
| Area | Minimal | Larger |
| Guaranteed Convergence | Yes | Yes |

## ⏱️ Correction Speed Complexity Comparison

<p align="center">
  <img src="images/Speed_Complexity.png" alt="Speed-Complexity" width="600">
</p>
