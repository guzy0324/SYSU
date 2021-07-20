-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
-- Date        : Sat Jun 26 12:03:58 2021
-- Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top design_1_sysu_high_level_0_1 -prefix
--               design_1_sysu_high_level_0_1_ design_1_sysu_high_level_1_0_sim_netlist.vhdl
-- Design      : design_1_sysu_high_level_1_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7s50csga324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_sysu_high_level_0_1 is
  port (
    high : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of design_1_sysu_high_level_0_1 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of design_1_sysu_high_level_0_1 : entity is "design_1_sysu_high_level_1_0,sysu_high_level,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of design_1_sysu_high_level_0_1 : entity is "yes";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of design_1_sysu_high_level_0_1 : entity is "sysu_high_level,Vivado 2017.4";
end design_1_sysu_high_level_0_1;

architecture STRUCTURE of design_1_sysu_high_level_0_1 is
  signal \<const1>\ : STD_LOGIC;
begin
  high <= \<const1>\;
VCC: unisim.vcomponents.VCC
     port map (
      P => \<const1>\
    );
end STRUCTURE;
