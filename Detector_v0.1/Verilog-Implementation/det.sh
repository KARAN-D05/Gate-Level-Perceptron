module eq_super_recognition(
    input [15:0] in,
    input [15:0] weight,
    output reg recognition
);

  wire [15:0] inaw;
  wire [15:0] wco;

  assign inaw = in & weight;
  assign wco = ( ((~inaw)&(~weight)) | (inaw & weight) );

  always@(*) begin
    if (&wco) begin 
        recognition = 1;
    end else begin
        recognition = 0;
    end
  end
endmodule
