`include "det.v"

module testbench;

  reg [15:0] in;
  reg [15:0] ref;
  reg [3:0] thresh;
  wire recognition;

  popcount dut(
    .in(in),
    .ref(ref),
    .thresh(thresh),
    .recognition(recognition)
  );

   initial begin 

      $monitor("t = %0t | in = %b | ref = %b | thresh = %b | recognition = %b ", $time, in, ref, thresh, recognition);
      $dumpfile("sim.vcd");
      $dumpvars(0, testbench);

      // M=8, θ=12 , θ > M -> Recognition=0
      in = 16'hE44E;
      ref = 16'h7227;
      thresh = 4'hC;
      #10;

      // Same test case with different threshold
      // M=8, θ=7 , θ < M -> Recognition=1
      in = 16'hE44E;
      ref = 16'h7227;
      thresh = 4'h7;
      #10;

      // M=0, θ=0(MIN) , θ = M -> Recognition=0
      in = 16'h0000;
      ref = 16'hFFFF;
      thresh = 4'h0;
      #10;

     // M=16, θ=15(MAX) , θ < M -> Recognition=1
      in = 16'hFFFF;
      ref = 16'hFFFF;
      thresh = 4'hF;
      #10;

      // M=15, θ=13 , θ < M -> Recognition=1
      in = 16'hE444;
      ref = 16'hF444;
      thresh = 4'hD;
      #10;

      // M=15, θ=14 , θ < M -> Recognition=1
      in = 16'hE444;
      ref = 16'hF444;
      thresh = 4'hE;
      #10;

      $display("Simulation Complete!");
      $finish;

  end

endmodule
