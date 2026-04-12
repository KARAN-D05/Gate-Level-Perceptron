sim:
	iverilog -o sim.out det.v det_tb.v && vvp sim.out

wave:
	gtkwave dump.vcd

clean:
	rm -f sim.out dump.vcd
