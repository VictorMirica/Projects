//Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2021.1 (lin64) Build 3247384 Thu Jun 10 19:36:07 MDT 2021
//Date        : Mon Mar 14 16:57:29 2022
//Host        : admin1-ThinkPad-Edge-E530 running 64-bit Zorin OS 16
//Command     : generate_target design_3.bd
//Design      : design_3
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_3,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_3,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=3,numReposBlks=3,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_3.hwdef" *) 
module design_3
   (A,
    B,
    C,
    D,
    clk_0);
  input [0:0]A;
  input [0:0]B;
  input [0:0]C;
  output [0:0]D;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_0, CLK_DOMAIN design_3_clk_0, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk_0;

  wire [0:0]A_1;
  wire [0:0]B_1;
  wire [0:0]C_1;
  wire clk_0_1;
  wire [0:0]util_vector_logic_0_Res;
  wire [0:0]util_vector_logic_1_Res;

  assign A_1 = A[0];
  assign B_1 = B[0];
  assign C_1 = C[0];
  assign D[0] = util_vector_logic_1_Res;
  assign clk_0_1 = clk_0;
  design_3_ila_0_0 ila_0
       (.clk(clk_0_1),
        .probe0(util_vector_logic_1_Res));
  design_3_util_vector_logic_0_0 util_vector_logic_0
       (.Op1(A_1),
        .Op2(B_1),
        .Res(util_vector_logic_0_Res));
  design_3_util_vector_logic_1_0 util_vector_logic_1
       (.Op1(util_vector_logic_0_Res),
        .Op2(C_1),
        .Res(util_vector_logic_1_Res));
endmodule
