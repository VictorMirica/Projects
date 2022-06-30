// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Tue Mar 29 18:53:32 2022
// Host        : DESKTOP-620LK0K running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/student/Desktop/Emanuel/project3/project3.gen/sources_1/bd/design_1/ip/design_1_divizor_ceas_0_0/design_1_divizor_ceas_0_0_stub.v
// Design      : design_1_divizor_ceas_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "divizor_ceas,Vivado 2021.2" *)
module design_1_divizor_ceas_0_0(clk_in, reset, clk_out_led, clk_out_seg)
/* synthesis syn_black_box black_box_pad_pin="clk_in,reset,clk_out_led,clk_out_seg" */;
  input clk_in;
  input reset;
  output clk_out_led;
  output clk_out_seg;
endmodule
