// Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2015.4 (win64) Build 1412921 Wed Nov 18 09:43:45 MST 2015
// Date        : Fri Nov 08 23:10:50 2019
// Host        : DESKTOP-7HN2EN2 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/guzy0/calculator/calculator.srcs/sources_1/ip/display_0/display_0_stub.v
// Design      : display_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "display,Vivado 2015.4" *)
module display_0(clk, data, sm_wei, sm_duan)
/* synthesis syn_black_box black_box_pad_pin="clk,data[15:0],sm_wei[3:0],sm_duan[6:0]" */;
  input clk;
  input [15:0]data;
  output [3:0]sm_wei;
  output [6:0]sm_duan;
endmodule
