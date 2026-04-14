// ======================================================================================================
//  Popcount based decision-making + manually alterable decision boundary using variable threshold (v1.0)
// ======================================================================================================

module popcount (
  input [15:0] in,       // 4*4 Input Grid
  input [15:0] ref,      // 4*4 reference grid
  input [3:0] thresh,    // decision-making parameter, can be varied to alter system decision boundary
  output reg recognition // Recognition Output
);

 wire [15:0] incref; // in COMPARE ref
 reg [4:0] count; // Matched Pixels
 integer i;

// XNOR-Equivalence Grid
  assign incref = ( ((~in) & (~ref)) | (in & ref) ); // incref = in XNOR ref

// Population Counter
 always @(*) begin
  count = 0;
  for (i = 0; i < 16; i = i + 1) begin
    count = count + incref[i]; // sum total number of matched pixels to compare against the variable threshold
  end
 end

// System Activation Function
// M > θ -> OUT=1
// M < θ -> OUT=0
// M = θ -> OUT=0
 always @(*) begin
   if (count > thresh) begin  // If matched pixels are strictly greater than threshold the system recognizes the pattern else no recognition
    recognition = 1;
  end else begin
    recognition = 0;
  end
 end

endmodule
