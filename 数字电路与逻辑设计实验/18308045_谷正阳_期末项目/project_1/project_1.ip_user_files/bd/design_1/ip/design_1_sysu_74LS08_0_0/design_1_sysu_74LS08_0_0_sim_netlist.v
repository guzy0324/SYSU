// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Sun Jun 27 11:28:42 2021
// Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Users/guzy0/Desktop/dbg/dc/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_sysu_74LS08_0_0/design_1_sysu_74LS08_0_0_sim_netlist.v
// Design      : design_1_sysu_74LS08_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_sysu_74LS08_0_0,sysu_74LS08,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sysu_74LS08,Vivado 2017.4" *) 
(* NotValidForBitStream *)
module design_1_sysu_74LS08_0_0
   (A1,
    B1,
    A2,
    B2,
    A3,
    B3,
    A4,
    B4,
    Y1,
    Y2,
    Y3,
    Y4);
  input A1;
  input B1;
  input A2;
  input B2;
  input A3;
  input B3;
  input A4;
  input B4;
  output Y1;
  output Y2;
  output Y3;
  output Y4;

  wire A1;
  wire A2;
  wire A3;
  wire A4;
  wire B1;
  wire B2;
  wire B3;
  wire B4;
  wire Y1;
  wire Y2;
  wire Y3;
  wire Y4;

  LUT2 #(
    .INIT(4'h8)) 
    Y1_INST_0
       (.I0(A1),
        .I1(B1),
        .O(Y1));
  LUT2 #(
    .INIT(4'h8)) 
    Y2_INST_0
       (.I0(A2),
        .I1(B2),
        .O(Y2));
  LUT2 #(
    .INIT(4'h8)) 
    Y3_INST_0
       (.I0(A3),
        .I1(B3),
        .O(Y3));
  LUT2 #(
    .INIT(4'h8)) 
    Y4_INST_0
       (.I0(A4),
        .I1(B4),
        .O(Y4));
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
