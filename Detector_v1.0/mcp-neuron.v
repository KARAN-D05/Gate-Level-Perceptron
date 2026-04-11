module neuronode(input x,
                 input y,
                 input[1:0] Threshold,
                 output reg fire);

   wire [1:0] sum;
   assign sum = x + y; 

  always@(*) begin
    if ( sum >= Threshold ) begin
        fire = 1'b1; 
    end else begin
        fire = 1'b0; 
    end
  end       

endmodule
