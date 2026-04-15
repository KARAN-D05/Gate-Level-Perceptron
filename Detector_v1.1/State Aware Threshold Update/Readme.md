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
decremen is always sufficient to reverse the output and 
achieve correction.

**Complexity:** O(1) - correction always achieved in a single 
clock cycle regardless of current threshold position.

**Hardware:** A decrementer, a cell pointer, 
and a thinking module that decides step based on current 
and desired state. Higher area and logical complexity than MIDS.

**Tradeoff:** Maximum correction speed at the cost of additional 
hardware complexity and silicon area.
