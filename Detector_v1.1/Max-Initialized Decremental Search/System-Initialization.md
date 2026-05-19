## Programming The Memory

- Press Error_In to start the down counter sequence and manually pulse the clock for each address which is visble via threshold pointer.

- Make Clear Success Flag pin and Clear Convergence Detectors Pin high to prevent correction detectors from firing while programming the threshold memory.

- Make MEM_P_EN and E0W1 pins high to connect the data pins (D1 D2 D4 D8) to the memory cell bus and to allow write operation in memory cells.

- For MIDS algorithm store same data in the cell as the address of the cell. Eg 15 in cell pointed by address 15.

- Manually pulse the clock once to get to next address. Eg 15 -> 14.

- Do same for all address from 15 down to 0 and then turn the pins MEM_P_EN and E0W1 low.

- Press the pin M_L_RST to reset the down counter. Not M_RST, it resets the memory cell.

- Make Clear Success Flag pin and Clear Convergence Detectors Pin low.

## Using the System

- Enter and input and reference pattern on the respective grids and turn on the clock.

- Load any threshold(θ) using T-Pins T8 T4 T2 T1 manually by pressing M_TL. 

- Population Counter inside the the Super_System module counts the number of matched pixels(M) between the input and the reference.

- Based on the system activation function, R(M, θ) = 1 if M > θ, else 0 - the system computes the output as either 0 or 1.

- If not satisfied by the system output - press the Error_In and it will automatically start a correction sequence and system will autonomously
  start altering its decision boundary to flip its output.

- After successful correction the correction led goes on and the system hands back the control of the threshold back to the user.

- The correction sequence is automatically rearmed for successive correction cycles.

- For successive correction clear the success flag and the system is ready for next adaptation.
