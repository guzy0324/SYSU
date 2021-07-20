-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
-- Date        : Sun Jun 27 16:13:25 2021
-- Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_sysu_74LS197_0_0_stub.vhdl
-- Design      : design_1_sysu_74LS197_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7s50csga324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    P0 : in STD_LOGIC;
    P1 : in STD_LOGIC;
    P2 : in STD_LOGIC;
    P3 : in STD_LOGIC;
    MR : in STD_LOGIC;
    PL : in STD_LOGIC;
    CP0 : in STD_LOGIC;
    CP1 : in STD_LOGIC;
    Q0 : out STD_LOGIC;
    Q1 : out STD_LOGIC;
    Q2 : out STD_LOGIC;
    Q3 : out STD_LOGIC
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "P0,P1,P2,P3,MR,PL,CP0,CP1,Q0,Q1,Q2,Q3";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "sysu_74LS197,Vivado 2017.4";
begin
end;
