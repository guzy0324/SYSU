-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
-- Date        : Sun Jun 27 11:28:42 2021
-- Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_sysu_74LS32_0_0_stub.vhdl
-- Design      : design_1_sysu_74LS32_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7s50csga324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    A1 : in STD_LOGIC;
    B1 : in STD_LOGIC;
    A2 : in STD_LOGIC;
    B2 : in STD_LOGIC;
    A3 : in STD_LOGIC;
    B3 : in STD_LOGIC;
    A4 : in STD_LOGIC;
    B4 : in STD_LOGIC;
    Y1 : out STD_LOGIC;
    Y2 : out STD_LOGIC;
    Y3 : out STD_LOGIC;
    Y4 : out STD_LOGIC
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "A1,B1,A2,B2,A3,B3,A4,B4,Y1,Y2,Y3,Y4";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "four_2_input_or_gate,Vivado 2017.4";
begin
end;
