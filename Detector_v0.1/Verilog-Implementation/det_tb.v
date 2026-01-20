`include "det.v"

module testbench;

  reg [15:0] in_t;
  reg [15:0] weight_t;
  wire recognition_t;

  eq_super_recognition dut(
    .in(in_t),
    .weight(weight_t),
    .recognition(recognition_t)
  );

  initial begin

    $monitor("t = %0t | in_t = %b | weight_t = %b | recognition_t = %b", $time, in_t, weight_t, recognition_t);
    $dumpfile("Sim.vcd");
    $dumpvars(0, testbench);

    in_t = 16'b1110010001000100;
    weight_t = 16'b1110010001000100;
    #10;
    
    in_t = 16'b0100010001000100;
    weight_t = 16'b1110010001000100;
    #10;

    in_t = 16'b1111110001000100;
    weight_t = 16'b1110010001000100;
    #10;

    in_t = 16'b1111111111111111;
    weight_t = 16'b1110010001000100;
    #10;

    in_t = 16'b1111110001000100;
    weight_t = 16'b1111111111111111;
    #10;

    
    in_t = 16'b1111111111111111;
    weight_t = 16'b1111111111111111;
    #10;

    $finish;
    $display("Simulation Complete!");
  
  end
endmodule