// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Sat Jun 26 12:03:59 2021
// Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Users/guzy0/Desktop/dbg/dc/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_sysu_74LS283_0_0/design_1_sysu_74LS283_0_0_sim_netlist.v
// Design      : design_1_sysu_74LS283_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_sysu_74LS283_0_0,sysu_74LS283,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sysu_74LS283,Vivado 2017.4" *) 
(* NotValidForBitStream *)
module design_1_sysu_74LS283_0_0
   (A3,
    A2,
    A1,
    A0,
    B3,
    B2,
    B1,
    B0,
    Ci,
    S3,
    S2,
    S1,
    S0,
    Co);
  input A3;
  input A2;
  input A1;
  input A0;
  input B3;
  input B2;
  input B1;
  input B0;
  input Ci;
  output S3;
  output S2;
  output S1;
  output S0;
  output Co;

  wire A0;
  wire A1;
  wire A2;
  wire A3;
  wire B0;
  wire B1;
  wire B2;
  wire B3;
  wire Ci;
  wire Co;
  wire S0;
  wire S1;
  wire S2;
  wire S3;
  wire \inst/C2__3 ;

  LUT5 #(
    .INIT(32'hFEEAA880)) 
    Co_INST_0
       (.I0(B3),
        .I1(A2),
        .I2(\inst/C2__3 ),
        .I3(B2),
        .I4(A3),
        .O(Co));
  LUT3 #(
    .INIT(8'h96)) 
    S0_INST_0
       (.I0(A0),
        .I1(B0),
        .I2(Ci),
        .O(S0));
  LUT5 #(
    .INIT(32'h99969666)) 
    S1_INST_0
       (.I0(A1),
        .I1(B1),
        .I2(B0),
        .I3(Ci),
        .I4(A0),
        .O(S1));
  LUT3 #(
    .INIT(8'h96)) 
    S2_INST_0
       (.I0(A2),
        .I1(B2),
        .I2(\inst/C2__3 ),
        .O(S2));
  LUT5 #(
    .INIT(32'h99969666)) 
    S3_INST_0
       (.I0(A3),
        .I1(B3),
        .I2(B2),
        .I3(\inst/C2__3 ),
        .I4(A2),
        .O(S3));
  LUT5 #(
    .INIT(32'hFEEAA880)) 
    S3_INST_0_i_1
       (.I0(B1),
        .I1(A0),
        .I2(Ci),
        .I3(B0),
        .I4(A1),
        .O(\inst/C2__3 ));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
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

endmodule
`endif
