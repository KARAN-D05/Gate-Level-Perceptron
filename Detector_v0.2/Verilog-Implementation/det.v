// =============================================================================
//  eq_sub_super_anti_recognition — Gate-Level Pattern Detector (v0.2)
// ============================================================================-

module sub_super_multi_pov(
    input [15:0] in,              // 4*4 Input Grid
    input [15:0] weight,          // 4*4 Weight Grid
    output reg sub,               // Input ⊂ Weight
    output reg super,             // Input ⊃ Weight
    output reg eq,                // Input = Weight
    output reg anti,              // (Input ⊄ Weight)∧(Input ⊅ Weight)∧(Input ≠ Weight)
    output reg recognition_sub,   // 1 if (Input ⊂ Weight)∨(Input = Weight)
    output reg recognition_super  // 1 if (Input ⊃ Weight)∨(Input = Weight)
);

  initial sub = 0;
  initial super = 0;
  initial eq = 0;
  initial anti = 0;
  
  wire [15:0] inaw;  // in AND weights = out
  wire [15:0] inco;  // in COMPARE out
  wire [15:0] wco;   // weigts COMPARE out
  
  assign inaw = in & weight; // 16 Wires carrying result of (INrc ^ WEIGHTrc), for rc=00,01,02,03,10,....,33
    
  assign inco = ( ((~in) & (~inaw) ) | ( in & inaw ) ); // 16 Wires carrying XNOR/Equivalence Checks for (IN XNOR inaw), for rc=00,01,02,03,.....,33


// EQ-SUB RECOGNITION
  always@(*) begin
    if (&inco) begin 
      recognition_sub = 1;
    end else begin
      recognition_sub = 0;
    end
  end

    assign wco = ( ((~inaw)&(~weight)) | (inaw & weight) ); // 16 Wires carrying XNOR/Equivalence Checks for (weights XNOR inaw), for rc=00,01,02,03,.....,33


//EQ-SUPER RECOGNITION
  always@(*) begin
    if (&wco) begin 
        recognition_super = 1;
    end else begin
        recognition_super = 0;
    end
  end

  always@(*) begin

    eq = 0;
    sub = 0;
    super = 0;
    anti = 0;

// 2-POV LOGICAL ANALYSIS
    if(recognition_sub & recognition_super) begin 
        eq = 1;
    end else if (~recognition_sub & recognition_super) begin
        super = 1;
    end else if (recognition_sub & ~recognition_super) begin 
        sub = 1;
    end else begin 
        anti = 1;
    end
  end

endmodule
