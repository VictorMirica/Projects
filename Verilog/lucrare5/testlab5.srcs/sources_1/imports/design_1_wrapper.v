
`timescale 1 ps / 1 ps

module design_1_wrapper
   (clear_0,
    clk_0,
    load_0,
    number1_0,
    number2_0,
    op_0,
    result_0);
  input clear_0;
  input clk_0;
  input load_0;
  input [32:0]number1_0;
  input [32:0]number2_0;
  input op_0;
  output [31:0]result_0;

  wire clear_0;
  wire clk_0;
  wire load_0;
  wire [32:0]number1_0;
  wire [32:0]number2_0;
  wire op_0;
  wire [31:0]result_0;

  design_1 design_1_i
       (.clear_0(clear_0),
        .clk_0(clk_0),
        .load_0(load_0),
        .number1_0(number1_0),
        .number2_0(number2_0),
        .op_0(op_0),
        .result_0(result_0));
endmodule
