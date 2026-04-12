// ============================================================================
//  eq_sub_recognition — Gate-Level Pattern Detector (v0.0)
// ============================================================================

module eq_sub_recognition(
    input [15:0] in,        // 4*4 Input Grid     
    input [15:0] weight,    // 4*4 Weights Grid 
    output reg recognition  // Output (Recognition/No Recognition)
);

  wire [15:0] inaw;        
  wire [15:0] inco;        

  assign inaw = in & weight;  // 16 Wires carrying result of (INrc ^ WEIGHTrc), for rc=00,01,02,03,10,....,33

  assign inco = ( ((~in) & (~inaw) ) | ( in & inaw ) ); // 16 Wires carrying XNOR/Equivalence Checks for (IN XNOR inaw), for rc=00,01,02,03,.....,33

  always@(*) begin
    if (&inco) begin  // If all the pixels between in and inaw match we get recognition 
      recognition = 1;
    end else begin  
      recognition = 0;
    end
  end

endmodule
