## Programming The Memory

- Press Error_In to start the down counter sequence and manually 
  pulse the clock for each address which is visible via threshold 
  pointer.

- Make Clear Success Flag pin and Clear Convergence Detectors Pin 
  high to prevent correction detectors from firing while 
  programming the threshold memory.

- Make MEM_P_EN and E0W1 pins high to connect the data pins 
  (D1 D2 D4 D8) to the memory cell bus and to allow write 
  operation in memory cells.

- For MIDS algorithm store same data in the cell as the address 
  of the cell. Eg 15 in cell pointed by address 15.

- Manually pulse the clock once to get to next address. Eg 15 → 14.

- Do same for all addresses from 15 down to 0 and then turn the 
  pins MEM_P_EN and E0W1 low.

- Press the pin M_L_RST to reset the down counter. 
  Not M_RST - it resets the threshold memory.

- Make Clear Success Flag pin and Clear Convergence Detectors 
  Pin low.

---

## Using the System

- Enter an input and reference pattern on the respective grids 
  and turn on the clock.

- Load any threshold(θ) using T-Pins T8 T4 T2 T1 manually by 
  pressing M_TL.

- Population Counter inside the Super_System module counts the 
  number of matched pixels(M) between the input and the reference.

- Based on the system activation function, R(M, θ) = 1 if M > θ, 
  else 0 - the system computes the output as either 0 or 1.

- If the system output requires correction - press Error_In and 
  the system will autonomously start a correction sequence, 
  altering its decision boundary to flip its output.

- After successful correction the Correction indicator goes high 
  and the system hands control of the threshold back to the user.

- The correction sequence is automatically rearmed for successive 
  correction cycles.

- For successive correction clear the Success Flag and the system 
  is ready for the next adaptation cycle.

---

## System Indicators

| Indicator | State | Meaning |
|---|---|---|
| RECOGNITION | HIGH | M > θ, pattern recognized |
| RECOGNITION | LOW | M ≤ θ, pattern not recognized |
| CORRECTION | HIGH | Correction sequence completed successfully |
| Hazard Detected | HIGH | Timing glitch detected during correction traversal |
| Hazard Nullified | HIGH | Glitch suppressed, traversal continuing correctly |

---

## Hazard Detection and Suppression

The system includes an autonomous hazard detection and suppression 
mechanism that protects the correction sequence from timing glitches.

**Normal Operation Signature:**

The correction sequence uses two convergence detectors - one fires 
on a 0→1 output transition, the other on a 1→0 transition. During 
correct operation, only one detector fires per correction cycle, 
corresponding to the direction of the output flip.

**Glitch Signature:**

A timing glitch during threshold traversal causes the output signal 
to momentarily spike producing a 1→0→1 or 0→1→0 transition 
within a single clock cycle. This fires both convergence detectors 
simultaneously, which is structurally impossible under normal 
operation.

**Detection Criterion:**

Both detectors firing simultaneously = glitch. This condition is 
unambiguous and cannot occur during correct correction behavior.

**Suppression Mechanism:**

On detecting both detectors active simultaneously, the system 
resets both detectors and its own detection state, then continues 
the traversal from the current threshold position. No user 
intervention required. The Hazard Detected and Hazard Nullified 
indicators will light briefly during this event - this is expected 
behavior, not a system failure.

**Result:**

The correction sequence reaches the correct flipping threshold 
despite the glitch. The system self-recovers without corrupting 
its traversal state.

---

## Edge Cases and System Boundaries

**M = 0 (No pixel match):**
Output is always non-recognition. No corrective decision boundary 
exists. Correction to recognition is not possible or meaningful.

**M = 16 (Perfect equivalence):**
Output is always recognition as threshold maximum is 15 and 
M > θ is always satisfied. No corrective decision boundary exists. 
Correction to non-recognition requires θ ≥ 16 which is outside 
the threshold space. System will not converge - this is correct 
behavior by design.

**Valid correction range: M ∈ {1, 2, ..., 15}**
For all values in this range, Decision Flipping Spaces exist 
within the threshold range and MIDS is guaranteed to converge.
