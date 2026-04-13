module popcount (
  input [15:0] in,
  input [15:0] ref,
  input [3:0] thresh,
  output reg recognition
);

 wire [15:0] incref; 
 reg [4:0] count;
 integer i;

 assign incref = ( ((~in)&(~ref)) | (in & ref) );

 always @(*) begin
  count = 0;
  for (i = 0; i < 16; i = i + 1) begin
    count = count + incref[i];
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