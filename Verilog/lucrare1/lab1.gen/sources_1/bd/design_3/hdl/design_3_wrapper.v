//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.1 (lin64) Build 3247384 Thu Jun 10 19:36:07 MDT 2021
//Date        : Mon Mar 14 16:57:29 2022
//Host        : admin1-ThinkPad-Edge-E530 running 64-bit Zorin OS 16
//Command     : generate_target design_3_wrapper.bd
//Design      : design_3_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_3_wrapper
   (A,
    B,
    C,
    D,
    clk_0);
  input [0:0]A;
  input [0:0]B;
  input [0:0]C;
  output [0:0]D;
  input clk_0;

  wire [0:0]A;
  wire [0:0]B;
  wire [0:0]C;
  wire [0:0]D;
  wire clk_0;

  design_3 design_3_i
       (.A(A),
        .B(B),
        .C(C),
        .D(D),
        .clk_0(clk_0));
endmodule
