-- Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2017.4 (win64) Build 2086221 Fri Dec 15 20:55:39 MST 2017
-- Date        : Sun Jun 27 16:13:25 2021
-- Host        : DESKTOP-B2V7J46 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_sysu_74LS197_0_0_sim_netlist.vhdl
-- Design      : design_1_sysu_74LS197_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7s50csga324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sysu_74LS197 is
  port (
    Q0 : out STD_LOGIC;
    Q3 : out STD_LOGIC;
    Q2 : out STD_LOGIC;
    Q1 : out STD_LOGIC;
    CP0 : in STD_LOGIC;
    CP1 : in STD_LOGIC;
    MR : in STD_LOGIC;
    P0 : in STD_LOGIC;
    PL : in STD_LOGIC;
    P1 : in STD_LOGIC;
    P2 : in STD_LOGIC;
    P3 : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sysu_74LS197;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sysu_74LS197 is
  signal Q0_C_i_1_n_0 : STD_LOGIC;
  signal Q0_reg_C_n_0 : STD_LOGIC;
  signal Q0_reg_LDC_i_1_n_0 : STD_LOGIC;
  signal Q0_reg_LDC_i_2_n_0 : STD_LOGIC;
  signal Q0_reg_LDC_n_0 : STD_LOGIC;
  signal Q0_reg_P_n_0 : STD_LOGIC;
  signal \^q1\ : STD_LOGIC;
  signal \^q2\ : STD_LOGIC;
  signal \oct_cnt[0]_C_i_1_n_0\ : STD_LOGIC;
  signal \oct_cnt[1]_C_i_1_n_0\ : STD_LOGIC;
  signal \oct_cnt[2]_C_i_1_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[0]_C_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[0]_LDC_i_1_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[0]_LDC_i_2_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[0]_LDC_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[0]_P_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[1]_C_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[1]_LDC_i_1_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[1]_LDC_i_2_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[1]_LDC_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[1]_P_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[2]_C_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[2]_LDC_i_1_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[2]_LDC_i_2_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[2]_LDC_n_0\ : STD_LOGIC;
  signal \oct_cnt_reg[2]_P_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of Q0_C_i_1 : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of Q0_INST_0 : label is "soft_lutpair2";
  attribute XILINX_LEGACY_PRIM : string;
  attribute XILINX_LEGACY_PRIM of Q0_reg_LDC : label is "LDC";
  attribute SOFT_HLUTNM of Q1_INST_0 : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of Q3_INST_0 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \oct_cnt[0]_C_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \oct_cnt[2]_C_i_1\ : label is "soft_lutpair0";
  attribute XILINX_LEGACY_PRIM of \oct_cnt_reg[0]_LDC\ : label is "LDC";
  attribute XILINX_LEGACY_PRIM of \oct_cnt_reg[1]_LDC\ : label is "LDC";
  attribute XILINX_LEGACY_PRIM of \oct_cnt_reg[2]_LDC\ : label is "LDC";
begin
  Q1 <= \^q1\;
  Q2 <= \^q2\;
Q0_C_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"1D"
    )
        port map (
      I0 => Q0_reg_C_n_0,
      I1 => Q0_reg_LDC_n_0,
      I2 => Q0_reg_P_n_0,
      O => Q0_C_i_1_n_0
    );
Q0_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => Q0_reg_P_n_0,
      I1 => Q0_reg_LDC_n_0,
      I2 => Q0_reg_C_n_0,
      O => Q0
    );
Q0_reg_C: unisim.vcomponents.FDCE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP0,
      CE => '1',
      CLR => Q0_reg_LDC_i_2_n_0,
      D => Q0_C_i_1_n_0,
      Q => Q0_reg_C_n_0
    );
Q0_reg_LDC: unisim.vcomponents.LDCE
    generic map(
      INIT => '0'
    )
        port map (
      CLR => Q0_reg_LDC_i_2_n_0,
      D => '1',
      G => Q0_reg_LDC_i_1_n_0,
      GE => '1',
      Q => Q0_reg_LDC_n_0
    );
Q0_reg_LDC_i_1: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => MR,
      I1 => P0,
      I2 => PL,
      O => Q0_reg_LDC_i_1_n_0
    );
Q0_reg_LDC_i_2: unisim.vcomponents.LUT3
    generic map(
      INIT => X"57"
    )
        port map (
      I0 => MR,
      I1 => P0,
      I2 => PL,
      O => Q0_reg_LDC_i_2_n_0
    );
Q0_reg_P: unisim.vcomponents.FDPE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP0,
      CE => '1',
      D => Q0_C_i_1_n_0,
      PRE => Q0_reg_LDC_i_1_n_0,
      Q => Q0_reg_P_n_0
    );
Q1_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \oct_cnt_reg[0]_P_n_0\,
      I1 => \oct_cnt_reg[0]_LDC_n_0\,
      I2 => \oct_cnt_reg[0]_C_n_0\,
      O => \^q1\
    );
Q2_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \oct_cnt_reg[1]_P_n_0\,
      I1 => \oct_cnt_reg[1]_LDC_n_0\,
      I2 => \oct_cnt_reg[1]_C_n_0\,
      O => \^q2\
    );
Q3_INST_0: unisim.vcomponents.LUT3
    generic map(
      INIT => X"B8"
    )
        port map (
      I0 => \oct_cnt_reg[2]_P_n_0\,
      I1 => \oct_cnt_reg[2]_LDC_n_0\,
      I2 => \oct_cnt_reg[2]_C_n_0\,
      O => Q3
    );
\oct_cnt[0]_C_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"1D"
    )
        port map (
      I0 => \oct_cnt_reg[0]_C_n_0\,
      I1 => \oct_cnt_reg[0]_LDC_n_0\,
      I2 => \oct_cnt_reg[0]_P_n_0\,
      O => \oct_cnt[0]_C_i_1_n_0\
    );
\oct_cnt[1]_C_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"1D1D1DE2E2E21DE2"
    )
        port map (
      I0 => \oct_cnt_reg[0]_C_n_0\,
      I1 => \oct_cnt_reg[0]_LDC_n_0\,
      I2 => \oct_cnt_reg[0]_P_n_0\,
      I3 => \oct_cnt_reg[1]_C_n_0\,
      I4 => \oct_cnt_reg[1]_LDC_n_0\,
      I5 => \oct_cnt_reg[1]_P_n_0\,
      O => \oct_cnt[1]_C_i_1_n_0\
    );
\oct_cnt[2]_C_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"77788878"
    )
        port map (
      I0 => \^q1\,
      I1 => \^q2\,
      I2 => \oct_cnt_reg[2]_C_n_0\,
      I3 => \oct_cnt_reg[2]_LDC_n_0\,
      I4 => \oct_cnt_reg[2]_P_n_0\,
      O => \oct_cnt[2]_C_i_1_n_0\
    );
\oct_cnt_reg[0]_C\: unisim.vcomponents.FDCE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP1,
      CE => '1',
      CLR => \oct_cnt_reg[0]_LDC_i_2_n_0\,
      D => \oct_cnt[0]_C_i_1_n_0\,
      Q => \oct_cnt_reg[0]_C_n_0\
    );
\oct_cnt_reg[0]_LDC\: unisim.vcomponents.LDCE
    generic map(
      INIT => '0'
    )
        port map (
      CLR => \oct_cnt_reg[0]_LDC_i_2_n_0\,
      D => '1',
      G => \oct_cnt_reg[0]_LDC_i_1_n_0\,
      GE => '1',
      Q => \oct_cnt_reg[0]_LDC_n_0\
    );
\oct_cnt_reg[0]_LDC_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => MR,
      I1 => P1,
      I2 => PL,
      O => \oct_cnt_reg[0]_LDC_i_1_n_0\
    );
\oct_cnt_reg[0]_LDC_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"57"
    )
        port map (
      I0 => MR,
      I1 => P1,
      I2 => PL,
      O => \oct_cnt_reg[0]_LDC_i_2_n_0\
    );
\oct_cnt_reg[0]_P\: unisim.vcomponents.FDPE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP1,
      CE => '1',
      D => \oct_cnt[0]_C_i_1_n_0\,
      PRE => \oct_cnt_reg[0]_LDC_i_1_n_0\,
      Q => \oct_cnt_reg[0]_P_n_0\
    );
\oct_cnt_reg[1]_C\: unisim.vcomponents.FDCE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP1,
      CE => '1',
      CLR => \oct_cnt_reg[1]_LDC_i_2_n_0\,
      D => \oct_cnt[1]_C_i_1_n_0\,
      Q => \oct_cnt_reg[1]_C_n_0\
    );
\oct_cnt_reg[1]_LDC\: unisim.vcomponents.LDCE
    generic map(
      INIT => '0'
    )
        port map (
      CLR => \oct_cnt_reg[1]_LDC_i_2_n_0\,
      D => '1',
      G => \oct_cnt_reg[1]_LDC_i_1_n_0\,
      GE => '1',
      Q => \oct_cnt_reg[1]_LDC_n_0\
    );
\oct_cnt_reg[1]_LDC_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => MR,
      I1 => P2,
      I2 => PL,
      O => \oct_cnt_reg[1]_LDC_i_1_n_0\
    );
\oct_cnt_reg[1]_LDC_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"57"
    )
        port map (
      I0 => MR,
      I1 => P2,
      I2 => PL,
      O => \oct_cnt_reg[1]_LDC_i_2_n_0\
    );
\oct_cnt_reg[1]_P\: unisim.vcomponents.FDPE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP1,
      CE => '1',
      D => \oct_cnt[1]_C_i_1_n_0\,
      PRE => \oct_cnt_reg[1]_LDC_i_1_n_0\,
      Q => \oct_cnt_reg[1]_P_n_0\
    );
\oct_cnt_reg[2]_C\: unisim.vcomponents.FDCE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP1,
      CE => '1',
      CLR => \oct_cnt_reg[2]_LDC_i_2_n_0\,
      D => \oct_cnt[2]_C_i_1_n_0\,
      Q => \oct_cnt_reg[2]_C_n_0\
    );
\oct_cnt_reg[2]_LDC\: unisim.vcomponents.LDCE
    generic map(
      INIT => '0'
    )
        port map (
      CLR => \oct_cnt_reg[2]_LDC_i_2_n_0\,
      D => '1',
      G => \oct_cnt_reg[2]_LDC_i_1_n_0\,
      GE => '1',
      Q => \oct_cnt_reg[2]_LDC_n_0\
    );
\oct_cnt_reg[2]_LDC_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"08"
    )
        port map (
      I0 => MR,
      I1 => P3,
      I2 => PL,
      O => \oct_cnt_reg[2]_LDC_i_1_n_0\
    );
\oct_cnt_reg[2]_LDC_i_2\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"57"
    )
        port map (
      I0 => MR,
      I1 => P3,
      I2 => PL,
      O => \oct_cnt_reg[2]_LDC_i_2_n_0\
    );
\oct_cnt_reg[2]_P\: unisim.vcomponents.FDPE
    generic map(
      IS_C_INVERTED => '1'
    )
        port map (
      C => CP1,
      CE => '1',
      D => \oct_cnt[2]_C_i_1_n_0\,
      PRE => \oct_cnt_reg[2]_LDC_i_1_n_0\,
      Q => \oct_cnt_reg[2]_P_n_0\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
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
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "design_1_sysu_74LS197_0_0,sysu_74LS197,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "sysu_74LS197,Vivado 2017.4";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
begin
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_sysu_74LS197
     port map (
      CP0 => CP0,
      CP1 => CP1,
      MR => MR,
      P0 => P0,
      P1 => P1,
      P2 => P2,
      P3 => P3,
      PL => PL,
      Q0 => Q0,
      Q1 => Q1,
      Q2 => Q2,
      Q3 => Q3
    );
end STRUCTURE;
