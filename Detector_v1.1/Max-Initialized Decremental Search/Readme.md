#  📉 Max-Initialized Decremental Search (MIDS)

MIDS is a blind, state-unaware threshold correction algorithm that 
guarantees convergence through exhaustive decremental search.

On receiving an error signal, MIDS does not evaluate the current 
output state or reason about the desired state. Instead it follows 
a fixed procedure: reset the threshold to its maximum value (15) 
and begin decrementing by 1 each clock cycle until the output 
reverses and correction is achieved.

The core insight is that starting from maximum coverage guarantees 
the search will encounter the correction boundary regardless of 
where it lies. No decision logic, no state comparison, just a 
bounded search from ceiling to correction.

**Complexity:** O(N) - worst case 15 clock cycles if correction 
occurs at threshold 0.

**Hardware:** Minimal - a decrementer and a cell pointer. 
No incrementer, no thinking module, no state awareness required.

**Tradeoff:** Simplicity and minimal area at the cost of 
correction speed.

## 🎯 Convergence Proof:
Decision Flipping Space(DFS):
For a given M, the Decision Flipping Space is defined as:

```
System Activation Function: R(M, θ) = 1 if M > θ, else 0
Threshold Range: θ ∈ {0, ..., 15}

Decision Flipping Space(DFS):
For a given M, the Decision Flipping Space is defined as:

DFS⁺(M) = M - 1 = threshold value that flips output to recognition
DFS⁻(M) = M = threshold value that flips output to non-recognition

DFS existence for valid M
For all M ∈ {1, 2, ..., 15}:
DFS⁺(M) = M - 1 ∈ {0, 1, ..., 14} ⊆ {0, ..., 15} 
DFS⁻(M) = M ∈ {1, 2, ..., 15} ⊆ {0, ..., 15}

MIDS operates as:
θₙ₊₁ = θₙ - 1
This generates a strictly decreasing sequence:
15→14→⋯→0

Since:
θ traverses all values in [15→0] and DFS⁺(M), DFS⁻(M) ⊆ {0, ..., 15}
MIDS is guaranteed to hit the required flipping threshold in finite steps

```

- Since a valid decision-flipping threshold always exists for all valid M, and MIDS monotonically traverses the entire threshold space, the algorithm is guaranteed to reach a flipping point in finite time. Therefore, MIDS always converges.
- Worst-case convergence occurs when the flipping threshold is at θ = 0, yielding O(N) complexity where N is the threshold range.

- `Edge cases excluded by design`:
  - M = 0: Non-recognition always. No meaningful flip desired.
  - M = 16: Recognition always. No meaningful flip desired.
  - In both cases, no decision boundary exists within the threshold space, hence no correction is possible or required.
