# 👁️ State-Aware Threshold Update (SATU)

SATU is a state-aware threshold correction algorithm that achieves 
correction in a single clock cycle by reasoning about the current 
and desired output state before acting.

On receiving an error signal, SATU does not reset to maximum. 
Instead it points directly to the cell equivalent to the current 
matched pixel count. A dedicated thinking module then evaluates 
the current output against the desired output and decides whether 
to stay or decrement the threshold by one step.

The result is immediate boundary correction, one step - stay or
decrement is always sufficient to reverse the output and 
achieve correction.

**Complexity:** O(1) - correction always achieved in a single 
clock cycle regardless of current threshold position.

**Hardware:** A decrementer, a cell pointer, 
and a thinking module that decides step based on current 
and desired state. Higher area and logical complexity than MIDS.

**Tradeoff:** Maximum correction speed at the cost of additional 
hardware complexity and silicon area.

## 🎛️ Initialization Bias
SATU has no initialization bias, as it directly computes the required threshold from M: θ=M (non-recognition) or θ=M−1 (recognition).

Both recognition and non-recognition are achieved in constant time O(1), independent of any starting state.

Suitable when balanced and immediate correction is required, without preference toward false positives or false negatives.

## 🧠 Design Insight: Eliminating the Incrementer via Strict Inequality

### The Strict Inequality Advantage

The system's activation function is defined as:

R(M, θ) = 1  if M > θ  
R(M, θ) = 0  otherwise

This strict inequality introduces an asymmetry in how the decision boundary is crossed.

### Correction Logic Analysis

| Desired Output Transition | Required Condition | Direct Hardware Action |
| :--- | :--- | :--- |
| **Non-Recognition → Recognition** | M > θ must become true | Set θ ← M - 1 (decrement) |
| **Recognition → Non-Recognition** | M > θ must become false | Set θ ← M (direct load) |

### Why No Incrementer Is Needed

- **To enable recognition:** The threshold must be strictly less than the match count M.  
  The largest integer satisfying this is M - 1. This requires a **single decrement**.

- **To disable recognition:** The threshold must be greater than or equal to M.  
  Setting θ = M satisfies this exactly. This corresponds to a **direct load** of M into the threshold register, requiring no arithmetic operation.

- At no point does the threshold need to be increased beyond the current match count M to achieve a correct decision.  
  Therefore, **an incrementer is unnecessary**.

### Hardware Implications

| Component | Before Optimization | After Optimization |
| :--- | :--- | :--- |
| Arithmetic Units | Incrementer + Decrementer | **Decrementer only** |
| Data Path | MUX selects Inc / Dec / Hold | MUX selects Load(M) / Load(M - 1) |
| Control FSM | Determine direction (up/down) | Determine desired output state |

**Result:** Reduced gate count and simplified control logic with no loss of functionality.

### Conclusion

The choice of a strict inequality in the activation function encodes an asymmetry that aligns precisely with minimal hardware requirements.

SATU achieves single-cycle adaptation using only a decrementer and a load path demonstrating a direct alignment between mathematical structure and circuit-level efficiency.
