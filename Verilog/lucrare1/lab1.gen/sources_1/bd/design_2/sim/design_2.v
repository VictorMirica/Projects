//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.1 (lin64) Build 3247384 Thu Jun 10 19:36:07 MDT 2021
//Date        : Mon Mar  7 17:31:14 2022
//Host        : admin1-ThinkPad-Edge-E530 running 64-bit Zorin OS 16
//Command     : generate_target design_2.bd
//Design      : design_2
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_2,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_2,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=2,numReposBlks=2,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_2.hwdef" *) 
module design_2
   (A,
    B,
    C,
    D);
  input [0:0]A;
  input [0:0]B;
  input [0:0]C;
  output [0:0]D;

  wire [0:0]A_1;
  wire [0:0]B_1;
  wire [0:0]C_1;
  wire [0:0]util_vector_logic_0_Res;
  wire [0:0]util_vector_logic_1_Res;

  assign A_1 = A[0];
  assign B_1 = B[0];
  assign C_1 = C[0];
  assign D[0] = util_vector_logic_1_Res;
  design_2_util_vector_logic_0_0 util_vector_logic_0
       (.Op1(A_1),
        .Op2(B_1),
        .Res(util_vector_logic_0_Res));
  design_2_util_vector_logic_1_0 util_vector_logic_1
       (.Op1(util_vector_logic_0_Res),
        .Op2(C_1),
        .Res(util_vector_logic_1_Res));
endmodule
