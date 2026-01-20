module eq_sub_recognition(
    input [15:0] in,
    input [15:0] weight,
    output reg recognition
);

  wire [15:0] inaw;
  wire [15:0] inco;

  assign inaw = in & weight;
  assign inco = ( ((~in) & (~inaw) ) | ( in & inaw ) );
  
  always@(*) begin
    if (&inco) begin 
      recognition = 1;
    end else begin
      recognition = 0;
    end
  end
endmodule