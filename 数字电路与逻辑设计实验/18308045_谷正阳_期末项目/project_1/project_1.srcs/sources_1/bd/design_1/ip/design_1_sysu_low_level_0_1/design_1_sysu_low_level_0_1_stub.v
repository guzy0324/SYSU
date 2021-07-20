// Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
// Date        : Sat Jun 26 12:03:58 2021
// Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub -rename_top design_1_sysu_low_level_0_1 -prefix
//               design_1_sysu_low_level_0_1_ design_1_sysu_low_level_1_0_stub.v
// Design      : design_1_sysu_low_level_1_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7s50csga324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "sysu_low_level,Vivado 2017.4" *)
module design_1_sysu_low_level_0_1(low)
/* synthesis syn_black_box black_box_pad_pin="low" */;
  output low;
endmodule
