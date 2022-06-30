//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
//Date        : Sun Apr 10 17:17:23 2022
//Host        : DESKTOP-D952KFM running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (An_0,
    DP_0,
    Seg_0,
    clk_in_0,
    clk_out_led_0,
    pauza_0,
    reset_0);
  output [7:0]An_0;
  output DP_0;
  output [0:6]Seg_0;
  input clk_in_0;
  output clk_out_led_0;
  input pauza_0;
  input reset_0;

  wire [7:0]An_0;
  wire DP_0;
  wire [0:6]Seg_0;
  wire clk_in_0;
  wire clk_out_led_0;
  wire pauza_0;
  wire reset_0;

  design_1 design_1_i
       (.An_0(An_0),
        .DP_0(DP_0),
        .Seg_0(Seg_0),
        .clk_in_0(clk_in_0),
        .clk_out_led_0(clk_out_led_0),
        .pauza_0(pauza_0),
        .reset_0(reset_0));
endmodule
