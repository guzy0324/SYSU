// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Sun Jun 27 16:13:25 2021
// Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_sysu_74LS197_0_0_sim_netlist.v
// Design      : design_1_sysu_74LS197_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_1_sysu_74LS197_0_0,sysu_74LS197,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* X_CORE_INFO = "sysu_74LS197,Vivado 2017.4" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (P0,
    P1,
    P2,
    P3,
    MR,
    PL,
    CP0,
    CP1,
    Q0,
    Q1,
    Q2,
    Q3);
  input P0;
  input P1;
  input P2;
  input P3;
  input MR;
  input PL;
  input CP0;
  input CP1;
  output Q0;
  output Q1;
  output Q2;
  output Q3;

  wire CP0;
  wire CP1;
  wire MR;
  wire P0;
  wire P1;
  wire P2;
  wire P3;
  wire PL;
  wire Q0;
  wire Q1;
  wire Q2;
  wire Q3;

  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sysu_74LS197 inst
       (.CP0(CP0),
        .CP1(CP1),
        .MR(MR),
        .P0(P0),
        .P1(P1),
        .P2(P2),
        .P3(P3),
        .PL(PL),
        .Q0(Q0),
        .Q1(Q1),
        .Q2(Q2),
        .Q3(Q3));
endmodule

module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sysu_74LS197
   (Q0,
    Q3,
    Q2,
    Q1,
    CP0,
    CP1,
    MR,
    P0,
    PL,
    P1,
    P2,
    P3);
  output Q0;
  output Q3;
  output Q2;
  output Q1;
  input CP0;
  input CP1;
  input MR;
  input P0;
  input PL;
  input P1;
  input P2;
  input P3;

  wire CP0;
  wire CP1;
  wire MR;
  wire P0;
  wire P1;
  wire P2;
  wire P3;
  wire PL;
  wire Q0;
  wire Q0_C_i_1_n_0;
  wire Q0_reg_C_n_0;
  wire Q0_reg_LDC_i_1_n_0;
  wire Q0_reg_LDC_i_2_n_0;
  wire Q0_reg_LDC_n_0;
  wire Q0_reg_P_n_0;
  wire Q1;
  wire Q2;
  wire Q3;
  wire \oct_cnt[0]_C_i_1_n_0 ;
  wire \oct_cnt[1]_C_i_1_n_0 ;
  wire \oct_cnt[2]_C_i_1_n_0 ;
  wire \oct_cnt_reg[0]_C_n_0 ;
  wire \oct_cnt_reg[0]_LDC_i_1_n_0 ;
  wire \oct_cnt_reg[0]_LDC_i_2_n_0 ;
  wire \oct_cnt_reg[0]_LDC_n_0 ;
  wire \oct_cnt_reg[0]_P_n_0 ;
  wire \oct_cnt_reg[1]_C_n_0 ;
  wire \oct_cnt_reg[1]_LDC_i_1_n_0 ;
  wire \oct_cnt_reg[1]_LDC_i_2_n_0 ;
  wire \oct_cnt_reg[1]_LDC_n_0 ;
  wire \oct_cnt_reg[1]_P_n_0 ;
  wire \oct_cnt_reg[2]_C_n_0 ;
  wire \oct_cnt_reg[2]_LDC_i_1_n_0 ;
  wire \oct_cnt_reg[2]_LDC_i_2_n_0 ;
  wire \oct_cnt_reg[2]_LDC_n_0 ;
  wire \oct_cnt_reg[2]_P_n_0 ;

  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'h1D)) 
    Q0_C_i_1
       (.I0(Q0_reg_C_n_0),
        .I1(Q0_reg_LDC_n_0),
        .I2(Q0_reg_P_n_0),
        .O(Q0_C_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair2" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Q0_INST_0
       (.I0(Q0_reg_P_n_0),
        .I1(Q0_reg_LDC_n_0),
        .I2(Q0_reg_C_n_0),
        .O(Q0));
  FDCE #(
    .IS_C_INVERTED(1'b1)) 
    Q0_reg_C
       (.C(CP0),
        .CE(1'b1),
        .CLR(Q0_reg_LDC_i_2_n_0),
        .D(Q0_C_i_1_n_0),
        .Q(Q0_reg_C_n_0));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    Q0_reg_LDC
       (.CLR(Q0_reg_LDC_i_2_n_0),
        .D(1'b1),
        .G(Q0_reg_LDC_i_1_n_0),
        .GE(1'b1),
        .Q(Q0_reg_LDC_n_0));
  LUT3 #(
    .INIT(8'h08)) 
    Q0_reg_LDC_i_1
       (.I0(MR),
        .I1(P0),
        .I2(PL),
        .O(Q0_reg_LDC_i_1_n_0));
  LUT3 #(
    .INIT(8'h57)) 
    Q0_reg_LDC_i_2
       (.I0(MR),
        .I1(P0),
        .I2(PL),
        .O(Q0_reg_LDC_i_2_n_0));
  FDPE #(
    .IS_C_INVERTED(1'b1)) 
    Q0_reg_P
       (.C(CP0),
        .CE(1'b1),
        .D(Q0_C_i_1_n_0),
        .PRE(Q0_reg_LDC_i_1_n_0),
        .Q(Q0_reg_P_n_0));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Q1_INST_0
       (.I0(\oct_cnt_reg[0]_P_n_0 ),
        .I1(\oct_cnt_reg[0]_LDC_n_0 ),
        .I2(\oct_cnt_reg[0]_C_n_0 ),
        .O(Q1));
  LUT3 #(
    .INIT(8'hB8)) 
    Q2_INST_0
       (.I0(\oct_cnt_reg[1]_P_n_0 ),
        .I1(\oct_cnt_reg[1]_LDC_n_0 ),
        .I2(\oct_cnt_reg[1]_C_n_0 ),
        .O(Q2));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'hB8)) 
    Q3_INST_0
       (.I0(\oct_cnt_reg[2]_P_n_0 ),
        .I1(\oct_cnt_reg[2]_LDC_n_0 ),
        .I2(\oct_cnt_reg[2]_C_n_0 ),
        .O(Q3));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT3 #(
    .INIT(8'h1D)) 
    \oct_cnt[0]_C_i_1 
       (.I0(\oct_cnt_reg[0]_C_n_0 ),
        .I1(\oct_cnt_reg[0]_LDC_n_0 ),
        .I2(\oct_cnt_reg[0]_P_n_0 ),
        .O(\oct_cnt[0]_C_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h1D1D1DE2E2E21DE2)) 
    \oct_cnt[1]_C_i_1 
       (.I0(\oct_cnt_reg[0]_C_n_0 ),
        .I1(\oct_cnt_reg[0]_LDC_n_0 ),
        .I2(\oct_cnt_reg[0]_P_n_0 ),
        .I3(\oct_cnt_reg[1]_C_n_0 ),
        .I4(\oct_cnt_reg[1]_LDC_n_0 ),
        .I5(\oct_cnt_reg[1]_P_n_0 ),
        .O(\oct_cnt[1]_C_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'h77788878)) 
    \oct_cnt[2]_C_i_1 
       (.I0(Q1),
        .I1(Q2),
        .I2(\oct_cnt_reg[2]_C_n_0 ),
        .I3(\oct_cnt_reg[2]_LDC_n_0 ),
        .I4(\oct_cnt_reg[2]_P_n_0 ),
        .O(\oct_cnt[2]_C_i_1_n_0 ));
  FDCE #(
    .IS_C_INVERTED(1'b1)) 
    \oct_cnt_reg[0]_C 
       (.C(CP1),
        .CE(1'b1),
        .CLR(\oct_cnt_reg[0]_LDC_i_2_n_0 ),
        .D(\oct_cnt[0]_C_i_1_n_0 ),
        .Q(\oct_cnt_reg[0]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \oct_cnt_reg[0]_LDC 
       (.CLR(\oct_cnt_reg[0]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\oct_cnt_reg[0]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\oct_cnt_reg[0]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \oct_cnt_reg[0]_LDC_i_1 
       (.I0(MR),
        .I1(P1),
        .I2(PL),
        .O(\oct_cnt_reg[0]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \oct_cnt_reg[0]_LDC_i_2 
       (.I0(MR),
        .I1(P1),
        .I2(PL),
        .O(\oct_cnt_reg[0]_LDC_i_2_n_0 ));
  FDPE #(
    .IS_C_INVERTED(1'b1)) 
    \oct_cnt_reg[0]_P 
       (.C(CP1),
        .CE(1'b1),
        .D(\oct_cnt[0]_C_i_1_n_0 ),
        .PRE(\oct_cnt_reg[0]_LDC_i_1_n_0 ),
        .Q(\oct_cnt_reg[0]_P_n_0 ));
  FDCE #(
    .IS_C_INVERTED(1'b1)) 
    \oct_cnt_reg[1]_C 
       (.C(CP1),
        .CE(1'b1),
        .CLR(\oct_cnt_reg[1]_LDC_i_2_n_0 ),
        .D(\oct_cnt[1]_C_i_1_n_0 ),
        .Q(\oct_cnt_reg[1]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \oct_cnt_reg[1]_LDC 
       (.CLR(\oct_cnt_reg[1]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\oct_cnt_reg[1]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\oct_cnt_reg[1]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \oct_cnt_reg[1]_LDC_i_1 
       (.I0(MR),
        .I1(P2),
        .I2(PL),
        .O(\oct_cnt_reg[1]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \oct_cnt_reg[1]_LDC_i_2 
       (.I0(MR),
        .I1(P2),
        .I2(PL),
        .O(\oct_cnt_reg[1]_LDC_i_2_n_0 ));
  FDPE #(
    .IS_C_INVERTED(1'b1)) 
    \oct_cnt_reg[1]_P 
       (.C(CP1),
        .CE(1'b1),
        .D(\oct_cnt[1]_C_i_1_n_0 ),
        .PRE(\oct_cnt_reg[1]_LDC_i_1_n_0 ),
        .Q(\oct_cnt_reg[1]_P_n_0 ));
  FDCE #(
    .IS_C_INVERTED(1'b1)) 
    \oct_cnt_reg[2]_C 
       (.C(CP1),
        .CE(1'b1),
        .CLR(\oct_cnt_reg[2]_LDC_i_2_n_0 ),
        .D(\oct_cnt[2]_C_i_1_n_0 ),
        .Q(\oct_cnt_reg[2]_C_n_0 ));
  (* XILINX_LEGACY_PRIM = "LDC" *) 
  LDCE #(
    .INIT(1'b0)) 
    \oct_cnt_reg[2]_LDC 
       (.CLR(\oct_cnt_reg[2]_LDC_i_2_n_0 ),
        .D(1'b1),
        .G(\oct_cnt_reg[2]_LDC_i_1_n_0 ),
        .GE(1'b1),
        .Q(\oct_cnt_reg[2]_LDC_n_0 ));
  LUT3 #(
    .INIT(8'h08)) 
    \oct_cnt_reg[2]_LDC_i_1 
       (.I0(MR),
        .I1(P3),
        .I2(PL),
        .O(\oct_cnt_reg[2]_LDC_i_1_n_0 ));
  LUT3 #(
    .INIT(8'h57)) 
    \oct_cnt_reg[2]_LDC_i_2 
       (.I0(MR),
        .I1(P3),
        .I2(PL),
        .O(\oct_cnt_reg[2]_LDC_i_2_n_0 ));
  FDPE #(
    .IS_C_INVERTED(1'b1)) 
    \oct_cnt_reg[2]_P 
       (.C(CP1),
        .CE(1'b1),
        .D(\oct_cnt[2]_C_i_1_n_0 ),
        .PRE(\oct_cnt_reg[2]_LDC_i_1_n_0 ),
        .Q(\oct_cnt_reg[2]_P_n_0 ));
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
