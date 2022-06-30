-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Sun Apr 10 17:18:44 2022
-- Host        : DESKTOP-D952KFM running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ design_1_numarator_59_1_0_sim_netlist.vhdl
-- Design      : design_1_numarator_59_1_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_numarator_59 is
  port (
    carry_out : out STD_LOGIC;
    valoare_bin : out STD_LOGIC_VECTOR ( 5 downto 0 );
    reset : in STD_LOGIC;
    pauza : in STD_LOGIC;
    clk_out_led : in STD_LOGIC
  );
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_numarator_59;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_numarator_59 is
  signal \^carry_out\ : STD_LOGIC;
  signal carry_out_i_1_n_0 : STD_LOGIC;
  signal carry_out_i_2_n_0 : STD_LOGIC;
  signal p_0_in : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal \^valoare_bin\ : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal \valoare_bin[5]_i_1_n_0\ : STD_LOGIC;
  signal \valoare_bin[5]_i_2_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \valoare_bin[1]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \valoare_bin[2]_i_1\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \valoare_bin[3]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \valoare_bin[4]_i_1\ : label is "soft_lutpair0";
begin
  carry_out <= \^carry_out\;
  valoare_bin(5 downto 0) <= \^valoare_bin\(5 downto 0);
carry_out_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"A808"
    )
        port map (
      I0 => reset,
      I1 => carry_out_i_2_n_0,
      I2 => pauza,
      I3 => \^carry_out\,
      O => carry_out_i_1_n_0
    );
carry_out_i_2: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0080000000000000"
    )
        port map (
      I0 => \^valoare_bin\(3),
      I1 => \^valoare_bin\(1),
      I2 => \^valoare_bin\(0),
      I3 => \^valoare_bin\(2),
      I4 => \^valoare_bin\(4),
      I5 => \^valoare_bin\(5),
      O => carry_out_i_2_n_0
    );
carry_out_reg: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => '1',
      D => carry_out_i_1_n_0,
      Q => \^carry_out\,
      R => '0'
    );
\valoare_bin[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^valoare_bin\(0),
      O => p_0_in(0)
    );
\valoare_bin[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \^valoare_bin\(0),
      I1 => \^valoare_bin\(1),
      O => p_0_in(1)
    );
\valoare_bin[2]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"78"
    )
        port map (
      I0 => \^valoare_bin\(0),
      I1 => \^valoare_bin\(1),
      I2 => \^valoare_bin\(2),
      O => p_0_in(2)
    );
\valoare_bin[3]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7F80"
    )
        port map (
      I0 => \^valoare_bin\(1),
      I1 => \^valoare_bin\(0),
      I2 => \^valoare_bin\(2),
      I3 => \^valoare_bin\(3),
      O => p_0_in(3)
    );
\valoare_bin[4]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7FFF8000"
    )
        port map (
      I0 => \^valoare_bin\(2),
      I1 => \^valoare_bin\(0),
      I2 => \^valoare_bin\(1),
      I3 => \^valoare_bin\(3),
      I4 => \^valoare_bin\(4),
      O => p_0_in(4)
    );
\valoare_bin[5]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"4F"
    )
        port map (
      I0 => pauza,
      I1 => carry_out_i_2_n_0,
      I2 => reset,
      O => \valoare_bin[5]_i_1_n_0\
    );
\valoare_bin[5]_i_2\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => pauza,
      O => \valoare_bin[5]_i_2_n_0\
    );
\valoare_bin[5]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFFFFFF80000000"
    )
        port map (
      I0 => \^valoare_bin\(3),
      I1 => \^valoare_bin\(1),
      I2 => \^valoare_bin\(0),
      I3 => \^valoare_bin\(2),
      I4 => \^valoare_bin\(4),
      I5 => \^valoare_bin\(5),
      O => p_0_in(5)
    );
\valoare_bin_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => \valoare_bin[5]_i_2_n_0\,
      D => p_0_in(0),
      Q => \^valoare_bin\(0),
      R => \valoare_bin[5]_i_1_n_0\
    );
\valoare_bin_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => \valoare_bin[5]_i_2_n_0\,
      D => p_0_in(1),
      Q => \^valoare_bin\(1),
      R => \valoare_bin[5]_i_1_n_0\
    );
\valoare_bin_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => \valoare_bin[5]_i_2_n_0\,
      D => p_0_in(2),
      Q => \^valoare_bin\(2),
      R => \valoare_bin[5]_i_1_n_0\
    );
\valoare_bin_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => \valoare_bin[5]_i_2_n_0\,
      D => p_0_in(3),
      Q => \^valoare_bin\(3),
      R => \valoare_bin[5]_i_1_n_0\
    );
\valoare_bin_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => \valoare_bin[5]_i_2_n_0\,
      D => p_0_in(4),
      Q => \^valoare_bin\(4),
      R => \valoare_bin[5]_i_1_n_0\
    );
\valoare_bin_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => clk_out_led,
      CE => \valoare_bin[5]_i_2_n_0\,
      D => p_0_in(5),
      Q => \^valoare_bin\(5),
      R => \valoare_bin[5]_i_1_n_0\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  port (
    clk_out_led : in STD_LOGIC;
    reset : in STD_LOGIC;
    pauza : in STD_LOGIC;
    carry_out : out STD_LOGIC;
    valoare_bin : out STD_LOGIC_VECTOR ( 5 downto 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "design_1_numarator_59_1_0,numarator_59,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix : entity is "numarator_59,Vivado 2021.2";
end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture STRUCTURE of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of reset : signal is "xilinx.com:signal:reset:1.0 reset RST";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of reset : signal is "XIL_INTERFACENAME reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
begin
inst: entity work.decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_numarator_59
     port map (
      carry_out => carry_out,
      clk_out_led => clk_out_led,
      pauza => pauza,
      reset => reset,
      valoare_bin(5 downto 0) => valoare_bin(5 downto 0)
    );
end STRUCTURE;
