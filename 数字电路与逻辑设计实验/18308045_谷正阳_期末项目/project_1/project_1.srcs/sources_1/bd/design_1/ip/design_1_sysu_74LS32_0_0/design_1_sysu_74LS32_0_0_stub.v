// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Sun Jun 27 11:28:42 2021
// Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/guzy0/Desktop/dbg/dc/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_sysu_74LS32_0_0/design_1_sysu_74LS32_0_0_stub.v
// Design      : design_1_sysu_74LS32_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "four_2_input_or_gate,Vivado 2017.4" *)
module design_1_sysu_74LS32_0_0(A1, B1, A2, B2, A3, B3, A4, B4, Y1, Y2, Y3, Y4)
/* synthesis syn_black_box black_box_pad_pin="A1,B1,A2,B2,A3,B3,A4,B4,Y1,Y2,Y3,Y4" */;
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
endmodule
