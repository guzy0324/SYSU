//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
//Date        : Fri Jul  2 09:32:33 2021
//Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=7,numReposBlks=7,numNonXlnxBlks=3,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
   (F,
    I0,
    I1,
    I2,
    I3,
    M,
    O0,
    O1,
    O2,
    O3);
  output F;
  input I0;
  input I1;
  input I2;
  input I3;
  input M;
  output O0;
  output O1;
  output O2;
  output O3;

  wire A1_0_1;
  wire A2_0_1;
  wire A3_0_1;
  wire I0_1;
  wire Net;
  wire sysu_74LS04_0_Y1;
  wire sysu_74LS08_0_Y1;
  wire sysu_74LS08_0_Y2;
  wire sysu_74LS08_0_Y3;
  wire sysu_74LS08_0_Y4;
  wire sysu_74LS283_0_S0;
  wire sysu_74LS283_0_S1;
  wire sysu_74LS283_0_S2;
  wire sysu_74LS283_0_S3;
  wire sysu_74LS32_0_Y1;
  wire sysu_74LS32_0_Y2;
  wire sysu_74LS32_0_Y3;
  wire sysu_74LS86_0_Y1;
  wire sysu_74LS86_0_Y2;
  wire sysu_74LS86_0_Y3;
  wire sysu_74LS86_0_Y4;
  wire sysu_high_level_0_high;
  wire sysu_low_level_0_low;

  assign A1_0_1 = I1;
  assign A2_0_1 = I2;
  assign A3_0_1 = I3;
  assign F = sysu_74LS32_0_Y3;
  assign I0_1 = I0;
  assign Net = M;
  assign O0 = sysu_74LS283_0_S0;
  assign O1 = sysu_74LS283_0_S1;
  assign O2 = sysu_74LS283_0_S2;
  assign O3 = sysu_74LS283_0_S3;
  design_1_sysu_74LS04_0_0 sysu_74LS04_0
       (.A1(Net),
        .A2(1'b0),
        .A3(1'b0),
        .A4(1'b0),
        .A5(1'b0),
        .A6(1'b0),
        .Y1(sysu_74LS04_0_Y1));
  design_1_sysu_74LS08_0_0 sysu_74LS08_0
       (.A1(A3_0_1),
        .A2(sysu_74LS32_0_Y2),
        .A3(sysu_74LS08_0_Y1),
        .A4(Net),
        .B1(sysu_74LS32_0_Y1),
        .B2(sysu_74LS283_0_S3),
        .B3(sysu_74LS04_0_Y1),
        .B4(sysu_74LS08_0_Y2),
        .Y1(sysu_74LS08_0_Y1),
        .Y2(sysu_74LS08_0_Y2),
        .Y3(sysu_74LS08_0_Y3),
        .Y4(sysu_74LS08_0_Y4));
  design_1_sysu_74LS283_0_0 sysu_74LS283_0
       (.A0(I0_1),
        .A1(A1_0_1),
        .A2(A2_0_1),
        .A3(A3_0_1),
        .B0(sysu_74LS86_0_Y4),
        .B1(sysu_74LS86_0_Y3),
        .B2(sysu_74LS86_0_Y2),
        .B3(sysu_74LS86_0_Y1),
        .Ci(Net),
        .S0(sysu_74LS283_0_S0),
        .S1(sysu_74LS283_0_S1),
        .S2(sysu_74LS283_0_S2),
        .S3(sysu_74LS283_0_S3));
  design_1_sysu_74LS32_0_0 sysu_74LS32_0
       (.A1(A2_0_1),
        .A2(sysu_74LS283_0_S1),
        .A3(sysu_74LS08_0_Y3),
        .A4(1'b0),
        .B1(A1_0_1),
        .B2(sysu_74LS283_0_S2),
        .B3(sysu_74LS08_0_Y4),
        .B4(1'b0),
        .Y1(sysu_74LS32_0_Y1),
        .Y2(sysu_74LS32_0_Y2),
        .Y3(sysu_74LS32_0_Y3));
  design_1_sysu_74LS86_0_0 sysu_74LS86_0
       (.A1(sysu_low_level_0_low),
        .A2(sysu_high_level_0_high),
        .A3(sysu_low_level_0_low),
        .A4(sysu_high_level_0_high),
        .B1(Net),
        .B2(Net),
        .B3(Net),
        .B4(Net),
        .Y1(sysu_74LS86_0_Y1),
        .Y2(sysu_74LS86_0_Y2),
        .Y3(sysu_74LS86_0_Y3),
        .Y4(sysu_74LS86_0_Y4));
  design_1_sysu_high_level_0_1 sysu_high_level_0
       (.high(sysu_high_level_0_high));
  design_1_sysu_low_level_0_1 sysu_low_level_0
       (.low(sysu_low_level_0_low));
endmodule
