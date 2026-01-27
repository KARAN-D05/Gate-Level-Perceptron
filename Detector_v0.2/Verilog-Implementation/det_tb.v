`include "det.v"

module testbench;

  reg [15:0] in;
  reg [15:0] weight;
  wire sub;
  wire super;
  wire anti;
  wire eq;
  wire recognition_sub;
  wire recognition_super;

  sub_super_multi_pov dut(
    .in(in),
    .weight(weight),
    .sub(sub),
    .super(super),
    .anti(anti),
    .eq(eq),
    .recognition_sub(recognition_sub),
    .recognition_super(recognition_super)
  );

   initial begin 

      $monitor("t = %0t | in = %b | weight = %b | recognition_sub = %b | recognition_super = %b | sub = %b | super = %b | anti = %b | eq = %b", $time, in, weight, recognition_sub, recognition_super, sub, super, anti, eq);
      $dumpfile("sim.vcd");
      $dumpvars(0, testbench);

      in = 16'hFFFF;
      weight = 16'hFFFF;
      #10;

      in = 16'h0FFF;
      weight = 16'hFFFF;
      #10;

      in = 16'hFFFF;
      weight = 16'hFF0F;
      #10;

      in = 16'h000F;
      weight = 16'hF000;
      #10;

      $finish;
      $display("Simulation Complete!");

  end

endmodule