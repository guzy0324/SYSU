//Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
//Date        : Fri Jul  2 09:32:33 2021
//Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
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

  wire F;
  wire I0;
  wire I1;
  wire I2;
  wire I3;
  wire M;
  wire O0;
  wire O1;
  wire O2;
  wire O3;

  design_1 design_1_i
       (.F(F),
        .I0(I0),
        .I1(I1),
        .I2(I2),
        .I3(I3),
        .M(M),
        .O0(O0),
        .O1(O1),
        .O2(O2),
        .O3(O3));
endmodule
