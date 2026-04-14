## 🎯 Convergence Proof

**System Activation Function:**
\[
R(M, \theta) =
\begin{cases}
1 & \text{if } M > \theta \\
0 & \text{otherwise}
\end{cases}
\]

**Threshold Range:**  
\[
\theta \in \{0, \dots, 15\}
\]

---

### Decision Flipping Space (DFS)

For a given \( M \), define:

\[
DFS^+(M) = M - 1
\]
→ threshold that flips output to recognition  

\[
DFS^-(M) = M
\]
→ threshold that flips output to non-recognition  

---

### DFS Existence

For all \( M \in \{1, 2, ..., 15\} \):

\[
DFS^+(M) = M - 1 \in \{0, ..., 14\} \subseteq \{0, ..., 15\}
\]

\[
DFS^-(M) = M \in \{1, ..., 15\} \subseteq \{0, ..., 15\}
\]

⇒ Valid decision-flipping thresholds always exist within the threshold range.

---

### MIDS Update Rule

\[
\theta_{n+1} = \theta_n - 1
\]

Starting from:
\[
\theta = 15
\]

This generates a strictly decreasing sequence:

\[
15 \rightarrow 14 \rightarrow \cdots \rightarrow 0
\]

---

### Convergence Argument

- \( \theta \) traverses all values in \( \{0, ..., 15\} \) monotonically  
- \( DFS^+(M), DFS^-(M) \subseteq \{0, ..., 15\} \)

⇒ MIDS is guaranteed to reach a valid decision-flipping threshold in finite steps.

---

### Conclusion

- Since a valid decision-flipping threshold exists for all valid \( M \), and MIDS monotonically traverses the entire threshold space, the algorithm is guaranteed to reach a flipping point in finite time.  
- Therefore, **MIDS always converges**.

---

### Complexity

Worst-case convergence occurs when the flipping threshold is at \( \theta = 0 \), yielding:

\[
O(N)
\]

where \( N \) is the threshold range.

---

### Edge Cases

- \( M = 0 \) → always non-recognition  
- \( M = 16 \) → always recognition  

In both cases, no decision boundary exists within the threshold space, hence no correction is possible or required.
