//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
//Date        : Wed May 26 21:13:14 2021
//Host        : catalin-vm running 64-bit Linux Mint 20.1
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
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
