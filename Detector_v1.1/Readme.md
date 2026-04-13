# 🔄 Feedback-Driven Adaptive Learning 
- Introduces feedback-driven adaptation on top of popcount based judgement system with alterable decision boundary.
- Automatic threshold adjustment based on feedback which would allow the detector to gradually converge towards an appropriate threshold to correct the recognition output.
- It would form basis of simple self-learning adaptive system that would be capable of altering its decision boundaries.

## 🧠 Adaptive Learning Algorithms 
- [Max-Initialized Decremental Search (MIDS)](Max-Initialized Decremental Search)
- [State Aware Thrshold Update (SATU)](State Aware Threshold Update)

| Property | MIDS | SATU |
|---|---|---|
| Correction Speed | O(N) | O(1) |
| State Awareness | None | Current & desired output |
| Direction | Always starts from max, decrements | Increments or decrements as needed |
| Hardware Complexity | Low - decrementer only | Higher - incrementer + decrementer + decision logic |
| Area | Minimal | Larger |
| Guaranteed Convergence | Yes | Yes |
