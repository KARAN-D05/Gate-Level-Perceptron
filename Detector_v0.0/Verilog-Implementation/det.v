// =============================================================================
//  eq_sub_recognition — Gate-Level Pattern Detector (v0.0)
// =============================================================================
//  A primitive, configurable pattern detection machine built entirely from
//  logic gates. Uses a 16-bit weight mask to filter a 16-bit input pattern
//  (representing a 4×4 grid) and a coincidence stage to check recognition.
//
//  HOW IT WORKS:
//  ─────────────
//  Input Grid   : 16-bit `in`     — flattened 4×4 pixel grid (A00..A33)
//  Weight Grid  : 16-bit `weight` — configured mask (W00..W33)
//                 Acts as a filter: only passes bits where weight=1.
//  Output Grid  : inaw = in & weight  — masked result (O00..O33)
//  Decision     : XNOR-style coincidence check across all 16 bits.
//                 Fires if input pattern ⊆ weight pattern (sub-pattern match).
//
//  RECOGNITION RULE:
//  ─────────────────
//  Recognized     if Arc ⊆ Wrc  (input is a sub-pattern of weight)
//  Not Recognized if Arc ⊈ Wrc  (input has bits outside the weight mask)
//
//  LIMITATIONS:
//  ────────────
//  - Also recognizes sub-patterns and garbage patterns of the weight grid.
//  - No scoring or noise tolerance — expects clean binary inputs.
//  - Does not reject super-patterns (input wider than weight).
//  - v0.0: essentially a binary pixel filter + comparator.
// =============================================================================

module eq_sub_recognition(
    input [15:0] in,        // input pattern  (flattened 4×4 grid, A00..A33)
    input [15:0] weight,    // weight mask    (flattened 4×4 grid, W00..W33)
    output reg recognition  // 1 if input matches weight pattern
);

  wire [15:0] inaw;  // in AND weight  — active bits where both agree
  wire [15:0] inco;  // coincidence    — 1 where in[i] == weight[i]

  // mask input against weight
  assign inaw = in & weight;

  // XNOR-style coincidence: bit is 1 when in[i] == weight[i]
  // if weight[i]=0 and in[i]=0 : (~in & ~inaw) catches it
  // if weight[i]=1 and in[i]=1 : (in & inaw)   catches it
  assign inco = ( ((~in) & (~inaw) ) | ( in & inaw ) );

  // recognition fires only when ALL 16 bits coincide
  always@(*) begin
    if (&inco) begin        // &inco = AND-reduce: 1 only if every bit is 1
      recognition = 1;
    end else begin
      recognition = 0;
    end
  end

endmodule
