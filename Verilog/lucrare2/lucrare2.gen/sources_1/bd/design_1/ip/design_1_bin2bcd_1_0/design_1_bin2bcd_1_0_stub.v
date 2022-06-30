// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Tue Mar 29 18:53:32 2022
// Host        : DESKTOP-620LK0K running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/student/Desktop/Emanuel/project3/project3.gen/sources_1/bd/design_1/ip/design_1_bin2bcd_1_0/design_1_bin2bcd_1_0_stub.v
// Design      : design_1_bin2bcd_1_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "bin2bcd,Vivado 2021.2" *)
module design_1_bin2bcd_1_0(valoare_bin, BCD0, BCD1)
/* synthesis syn_black_box black_box_pad_pin="valoare_bin[5:0],BCD0[3:0],BCD1[3:0]" */;
  input [5:0]valoare_bin;
  output [3:0]BCD0;
  output [3:0]BCD1;
endmodule
