//Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2020.2 (lin64) Build 3064766 Wed Nov 18 09:12:47 MST 2020
//Date        : Wed May 26 21:13:14 2021
//Host        : catalin-vm running 64-bit Linux Mint 20.1
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=20,numReposBlks=20,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=20,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
   (clear_0,
    clk_0,
    load_0,
    number1_0,
    number2_0,
    op_0,
    result_0);
  input clear_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_0, CLK_DOMAIN design_1_clk_0, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.000" *) input clk_0;
  input load_0;
  input [32:0]number1_0;
  input [32:0]number2_0;
  input op_0;
  output [31:0]result_0;

  wire [25:0]adun_scad_0_outt;
  wire [7:0]ajustare_0_outt;
  wire [7:0]alege_0_outt;
  wire [47:0]aliniere_0_outt;
  wire clear_0_1;
  wire clk_0_1;
  wire [15:0]compara_0_out1;
  wire [8:0]compara_0_out2;
  wire [56:0]concatenare_0_outt;
  wire [7:0]extragere_0_exp1;
  wire [7:0]extragere_0_exp2;
  wire [23:0]extragere_0_mant1;
  wire [23:0]extragere_0_mant2;
  wire load_0_1;
  wire [23:0]norm_0_out1;
  wire [8:0]norm_0_out2;
  wire [32:0]number1_0_1;
  wire [32:0]number2_0_1;
  wire op_0_1;
  wire [15:0]refacere_0_exponenti;
  wire [47:0]refacere_0_mantise;
  wire [15:0]registru16_0_outt;
  wire [15:0]registru16_1_outt;
  wire [23:0]registru24_0_out;
  wire [25:0]registru26_0_outt;
  wire [47:0]registru48_0_outt;
  wire [47:0]registru48_1_outt;
  wire [56:0]registru57_0_outt;
  wire [7:0]registru8_0_outt;
  wire [7:0]registru8_1_out;
  wire [7:0]registru8_2_out;
  wire [31:0]rezultatFinal_0_result;

  assign clear_0_1 = clear_0;
  assign clk_0_1 = clk_0;
  assign load_0_1 = load_0;
  assign number1_0_1 = number1_0[32:0];
  assign number2_0_1 = number2_0[32:0];
  assign op_0_1 = op_0;
  assign result_0[31:0] = rezultatFinal_0_result;
  design_1_adun_scad_0_0 adun_scad_0
       (.inn(registru48_1_outt),
        .op(op_0_1),
        .outt(adun_scad_0_outt));
  design_1_ajustare_0_0 ajustare_0
       (.exp(registru8_1_out),
        .inn(norm_0_out2),
        .outt(ajustare_0_outt));
  design_1_alege_0_0 alege_0
       (.inn(registru16_1_outt),
        .outt(alege_0_outt));
  design_1_aliniere_0_0 aliniere_0
       (.inn(registru57_0_outt),
        .outt(aliniere_0_outt));
  design_1_compara_0_0 compara_0
       (.inn(registru16_0_outt),
        .out1(compara_0_out1),
        .out2(compara_0_out2));
  design_1_concatenare_0_0 concatenare_0
       (.comp(compara_0_out2),
        .inn(registru48_0_outt),
        .outt(concatenare_0_outt));
  design_1_extragere_0_0 extragere_0
       (.exp1(extragere_0_exp1),
        .exp2(extragere_0_exp2),
        .mant1(extragere_0_mant1),
        .mant2(extragere_0_mant2),
        .number1(number1_0_1),
        .number2(number2_0_1));
  design_1_norm_0_0 norm_0
       (.inn(registru26_0_outt),
        .out1(norm_0_out1),
        .out2(norm_0_out2));
  design_1_refacere_0_0 refacere_0
       (.exp1(extragere_0_exp1),
        .exp2(extragere_0_exp2),
        .exponenti(refacere_0_exponenti),
        .mant1(extragere_0_mant1),
        .mant2(extragere_0_mant2),
        .mantise(refacere_0_mantise));
  design_1_registru16_0_0 registru16_0
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(refacere_0_exponenti),
        .load(load_0_1),
        .outt(registru16_0_outt));
  design_1_registru16_1_0 registru16_1
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(compara_0_out1),
        .load(load_0_1),
        .outt(registru16_1_outt));
  design_1_registru24_0_0 registru24_0
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(norm_0_out1),
        .load(load_0_1),
        .outt(registru24_0_out));
  design_1_registru26_0_0 registru26_0
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(adun_scad_0_outt),
        .load(load_0_1),
        .outt(registru26_0_outt));
  design_1_registru48_0_0 registru48_0
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(refacere_0_mantise),
        .load(load_0_1),
        .outt(registru48_0_outt));
  design_1_registru48_1_0 registru48_1
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(aliniere_0_outt),
        .load(load_0_1),
        .outt(registru48_1_outt));
  design_1_registru57_0_0 registru57_0
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(concatenare_0_outt),
        .load(load_0_1),
        .outt(registru57_0_outt));
  design_1_registru8_0_0 registru8_0
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(alege_0_outt),
        .load(load_0_1),
        .outt(registru8_0_outt));
  design_1_registru8_1_0 registru8_1
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(registru8_0_outt),
        .load(load_0_1),
        .outt(registru8_1_out));
  design_1_registru8_2_0 registru8_2
       (.clear(clear_0_1),
        .clk(clk_0_1),
        .inn(ajustare_0_outt),
        .load(load_0_1),
        .outt(registru8_2_out));
  design_1_rezultatFinal_0_0 rezultatFinal_0
       (.exponent(registru8_2_out),
        .mantisa(registru24_0_out),
        .result(rezultatFinal_0_result));
endmodule
