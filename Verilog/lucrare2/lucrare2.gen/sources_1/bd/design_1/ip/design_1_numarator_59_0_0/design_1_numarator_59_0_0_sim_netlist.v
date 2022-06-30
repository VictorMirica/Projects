// Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
// Date        : Sun Apr 10 17:18:44 2022
// Host        : DESKTOP-D952KFM running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               h:/2sem2/CN/lucrare2/lucrare2.gen/sources_1/bd/design_1/ip/design_1_numarator_59_0_0/design_1_numarator_59_0_0_sim_netlist.v
// Design      : design_1_numarator_59_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_numarator_59_0_0,numarator_59,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "module_ref" *) 
(* X_CORE_INFO = "numarator_59,Vivado 2021.2" *) 
(* NotValidForBitStream *)
module design_1_numarator_59_0_0
   (clk_out_led,
    reset,
    pauza,
    carry_out,
    valoare_bin);
  input clk_out_led;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 reset RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME reset, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input reset;
  input pauza;
  output carry_out;
  output [5:0]valoare_bin;

  wire carry_out;
  wire clk_out_led;
  wire pauza;
  wire reset;
  wire [5:0]valoare_bin;

  design_1_numarator_59_0_0_numarator_59 inst
       (.carry_out(carry_out),
        .clk_out_led(clk_out_led),
        .pauza(pauza),
        .reset(reset),
        .valoare_bin(valoare_bin));
endmodule

(* ORIG_REF_NAME = "numarator_59" *) 
module design_1_numarator_59_0_0_numarator_59
   (carry_out,
    valoare_bin,
    reset,
    pauza,
    clk_out_led);
  output carry_out;
  output [5:0]valoare_bin;
  input reset;
  input pauza;
  input clk_out_led;

  wire carry_out;
  wire carry_out_i_1_n_0;
  wire carry_out_i_2_n_0;
  wire clk_out_led;
  wire [5:0]p_0_in;
  wire pauza;
  wire reset;
  wire [5:0]valoare_bin;
  wire \valoare_bin[5]_i_1_n_0 ;
  wire \valoare_bin[5]_i_2_n_0 ;

  LUT4 #(
    .INIT(16'hA808)) 
    carry_out_i_1
       (.I0(reset),
        .I1(carry_out_i_2_n_0),
        .I2(pauza),
        .I3(carry_out),
        .O(carry_out_i_1_n_0));
  LUT6 #(
    .INIT(64'h0080000000000000)) 
    carry_out_i_2
       (.I0(valoare_bin[3]),
        .I1(valoare_bin[1]),
        .I2(valoare_bin[0]),
        .I3(valoare_bin[2]),
        .I4(valoare_bin[4]),
        .I5(valoare_bin[5]),
        .O(carry_out_i_2_n_0));
  FDRE carry_out_reg
       (.C(clk_out_led),
        .CE(1'b1),
        .D(carry_out_i_1_n_0),
        .Q(carry_out),
        .R(1'b0));
  LUT1 #(
    .INIT(2'h1)) 
    \valoare_bin[0]_i_1 
       (.I0(valoare_bin[0]),
        .O(p_0_in[0]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \valoare_bin[1]_i_1 
       (.I0(valoare_bin[0]),
        .I1(valoare_bin[1]),
        .O(p_0_in[1]));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h78)) 
    \valoare_bin[2]_i_1 
       (.I0(valoare_bin[0]),
        .I1(valoare_bin[1]),
        .I2(valoare_bin[2]),
        .O(p_0_in[2]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'h7F80)) 
    \valoare_bin[3]_i_1 
       (.I0(valoare_bin[1]),
        .I1(valoare_bin[0]),
        .I2(valoare_bin[2]),
        .I3(valoare_bin[3]),
        .O(p_0_in[3]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h7FFF8000)) 
    \valoare_bin[4]_i_1 
       (.I0(valoare_bin[2]),
        .I1(valoare_bin[0]),
        .I2(valoare_bin[1]),
        .I3(valoare_bin[3]),
        .I4(valoare_bin[4]),
        .O(p_0_in[4]));
  LUT3 #(
    .INIT(8'h4F)) 
    \valoare_bin[5]_i_1 
       (.I0(pauza),
        .I1(carry_out_i_2_n_0),
        .I2(reset),
        .O(\valoare_bin[5]_i_1_n_0 ));
  LUT1 #(
    .INIT(2'h1)) 
    \valoare_bin[5]_i_2 
       (.I0(pauza),
        .O(\valoare_bin[5]_i_2_n_0 ));
  LUT6 #(
    .INIT(64'h7FFFFFFF80000000)) 
    \valoare_bin[5]_i_3 
       (.I0(valoare_bin[3]),
        .I1(valoare_bin[1]),
        .I2(valoare_bin[0]),
        .I3(valoare_bin[2]),
        .I4(valoare_bin[4]),
        .I5(valoare_bin[5]),
        .O(p_0_in[5]));
  FDRE \valoare_bin_reg[0] 
       (.C(clk_out_led),
        .CE(\valoare_bin[5]_i_2_n_0 ),
        .D(p_0_in[0]),
        .Q(valoare_bin[0]),
        .R(\valoare_bin[5]_i_1_n_0 ));
  FDRE \valoare_bin_reg[1] 
       (.C(clk_out_led),
        .CE(\valoare_bin[5]_i_2_n_0 ),
        .D(p_0_in[1]),
        .Q(valoare_bin[1]),
        .R(\valoare_bin[5]_i_1_n_0 ));
  FDRE \valoare_bin_reg[2] 
       (.C(clk_out_led),
        .CE(\valoare_bin[5]_i_2_n_0 ),
        .D(p_0_in[2]),
        .Q(valoare_bin[2]),
        .R(\valoare_bin[5]_i_1_n_0 ));
  FDRE \valoare_bin_reg[3] 
       (.C(clk_out_led),
        .CE(\valoare_bin[5]_i_2_n_0 ),
        .D(p_0_in[3]),
        .Q(valoare_bin[3]),
        .R(\valoare_bin[5]_i_1_n_0 ));
  FDRE \valoare_bin_reg[4] 
       (.C(clk_out_led),
        .CE(\valoare_bin[5]_i_2_n_0 ),
        .D(p_0_in[4]),
        .Q(valoare_bin[4]),
        .R(\valoare_bin[5]_i_1_n_0 ));
  FDRE \valoare_bin_reg[5] 
       (.C(clk_out_led),
        .CE(\valoare_bin[5]_i_2_n_0 ),
        .D(p_0_in[5]),
        .Q(valoare_bin[5]),
        .R(\valoare_bin[5]_i_1_n_0 ));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
