module sub_super_multi_pov(
    input [15:0] in,
    input [15:0] weight,
    output reg sub,
    output reg super,
    output reg eq,
    output reg anti,
    output reg recognition_sub,
    output reg recognition_super
);

  initial sub = 0;
  initial super = 0;
  initial eq = 0;
  initial anti = 0;
  
  wire [15:0] inaw;
  wire [15:0] inco;
  wire [15:0] wco;
  
  assign inaw = in & weight;
  assign inco = ( ((~in) & (~inaw) ) | ( in & inaw ) );
  
  always@(*) begin
    if (&inco) begin 
      recognition_sub = 1;
    end else begin
      recognition_sub = 0;
    end
  end

  assign wco = ( ((~inaw)&(~weight)) | (inaw & weight) );

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