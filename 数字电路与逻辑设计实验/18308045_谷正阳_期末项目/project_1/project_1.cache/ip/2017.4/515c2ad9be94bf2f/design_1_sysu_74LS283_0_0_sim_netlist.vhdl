-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
-- Date        : Sat Jun 26 12:03:58 2021
-- Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_sysu_74LS283_0_0_sim_netlist.vhdl
-- Design      : design_1_sysu_74LS283_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7s50csga324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
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
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "design_1_sysu_74LS283_0_0,sysu_74LS283,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "sysu_74LS283,Vivado 2017.4";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  signal \inst/C2__3\ : STD_LOGIC;
begin
Co_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEEAA880"
    )
        port map (
      I0 => B3,
      I1 => A2,
      I2 => \inst/C2__3\,
      I3 => B2,
      I4 => A3,
      O => Co
    );
S0_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => A0,
      I1 => B0,
      I2 => Ci,
      O => S0
    );
S1_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"99969666"
    )
        port map (
      I0 => A1,
      I1 => B1,
      I2 => B0,
      I3 => Ci,
      I4 => A0,
      O => S1
    );
S2_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"96"
    )
        port map (
      I0 => A2,
      I1 => B2,
      I2 => \inst/C2__3\,
      O => S2
    );
S3_INST_0: unisim.vcomponents.LUT5
    generic map(
      INIT => X"99969666"
    )
        port map (
      I0 => A3,
      I1 => B3,
      I2 => B2,
      I3 => \inst/C2__3\,
      I4 => A2,
      O => S3
    );
S3_INST_0_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FEEAA880"
    )
        port map (
      I0 => B1,
      I1 => A0,
      I2 => Ci,
      I3 => B0,
      I4 => A1,
      O => \inst/C2__3\
    );
end STRUCTURE;
