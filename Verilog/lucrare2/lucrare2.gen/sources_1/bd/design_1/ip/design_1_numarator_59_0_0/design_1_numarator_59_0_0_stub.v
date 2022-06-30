// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Sun Apr 10 17:18:44 2022
// Host        : DESKTOP-D952KFM running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               h:/2sem2/CN/lucrare2/lucrare2.gen/sources_1/bd/design_1/ip/design_1_numarator_59_0_0/design_1_numarator_59_0_0_stub.v
// Design      : design_1_numarator_59_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "numarator_59,Vivado 2021.2" *)
module design_1_numarator_59_0_0(clk_out_led, reset, pauza, carry_out, 
  valoare_bin)
/* synthesis syn_black_box black_box_pad_pin="clk_out_led,reset,pauza,carry_out,valoare_bin[5:0]" */;
  input clk_out_led;
  input reset;
  input pauza;
  output carry_out;
  output [5:0]valoare_bin;
endmodule