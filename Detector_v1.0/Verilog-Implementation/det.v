module popcount (
  input [15:0] in,       // 4*4 Input Grid
  input [15:0] ref,      // 4*4 reference grid
  input [3:0] thresh,    // decision-making parameter
  output reg recognition // Recognition Output
);

 wire [15:0] incref; // in COMPARE ref
 reg [4:0] count;
 integer i;

 assign incref = ( ((~in)&(~ref)) | (in & ref) ); // incref = in XNOR ref

 always @(*) begin
  count = 0;
  for (i = 0; i < 16; i = i + 1) begin
    count = count + incref[i]; // sum total number of matched pixels
  end
 end

 always @(*) begin
  if (count > thresh) begin
    recognition = 1;
  end else begin
    recognition = 0;
  end
 end

endmodule
