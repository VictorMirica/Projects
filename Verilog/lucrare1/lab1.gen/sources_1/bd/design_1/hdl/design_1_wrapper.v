//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.1 (lin64) Build 3247384 Thu Jun 10 19:36:07 MDT 2021
//Date        : Mon Mar  7 16:38:10 2022
//Host        : admin1-ThinkPad-Edge-E530 running 64-bit Zorin OS 16
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (D,
    clk_0);
  output [0:0]D;
  input clk_0;

  wire [0:0]D;
  wire clk_0;

  design_1 design_1_i
       (.D(D),
        .clk_0(clk_0));
endmodule
