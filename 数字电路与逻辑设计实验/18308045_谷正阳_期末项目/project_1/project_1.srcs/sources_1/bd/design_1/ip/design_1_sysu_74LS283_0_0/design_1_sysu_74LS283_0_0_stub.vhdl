-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
-- Date        : Sat Jun 26 12:03:59 2021
-- Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/guzy0/Desktop/dbg/dc/project_1/project_1.srcs/sources_1/bd/design_1/ip/design_1_sysu_74LS283_0_0/design_1_sysu_74LS283_0_0_stub.vhdl
-- Design      : design_1_sysu_74LS283_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7s50csga324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_sysu_74LS283_0_0 is
  Port ( 
    A3 : in STD_LOGIC;
    A2 : in STD_LOGIC;
    A1 : in STD_LOGIC;
    A0 : in STD_LOGIC;
    B3 : in STD_LOGIC;
    B2 : in STD_LOGIC;
    B1 : in STD_LOGIC;
    B0 : in STD_LOGIC;
    Ci : in STD_LOGIC;
    S3 : out STD_LOGIC;
    S2 : out STD_LOGIC;
    S1 : out STD_LOGIC;
    S0 : out STD_LOGIC;
    Co : out STD_LOGIC
  );

end design_1_sysu_74LS283_0_0;

architecture stub of design_1_sysu_74LS283_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "A3,A2,A1,A0,B3,B2,B1,B0,Ci,S3,S2,S1,S0,Co";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "sysu_74LS283,Vivado 2017.4";
begin
end;
