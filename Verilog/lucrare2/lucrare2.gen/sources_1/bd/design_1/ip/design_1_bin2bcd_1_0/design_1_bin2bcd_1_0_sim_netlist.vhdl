-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Tue Mar 29 18:53:32 2022
-- Host        : DESKTOP-620LK0K running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/Users/student/Desktop/Emanuel/project3/project3.gen/sources_1/bd/design_1/ip/design_1_bin2bcd_1_0/design_1_bin2bcd_1_0_sim_netlist.vhdl
-- Design      : design_1_bin2bcd_1_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_bin2bcd_1_0_bin2bcd is
  port (
    BCD0 : out STD_LOGIC_VECTOR ( 1 downto 0 );
    BCD1 : out STD_LOGIC_VECTOR ( 2 downto 0 );
    valoare_bin : in STD_LOGIC_VECTOR ( 4 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of design_1_bin2bcd_1_0_bin2bcd : entity is "bin2bcd";
end design_1_bin2bcd_1_0_bin2bcd;

architecture STRUCTURE of design_1_bin2bcd_1_0_bin2bcd is
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \BCD0[0]_INST_0\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \BCD1[1]_INST_0\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \BCD1[2]_INST_0\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \BCD1[3]_INST_0\ : label is "soft_lutpair0";
begin
\BCD0[0]_INST_0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"793C6138"
    )
        port map (
      I0 => valoare_bin(1),
      I1 => valoare_bin(2),
      I2 => valoare_bin(4),
      I3 => valoare_bin(3),
      I4 => valoare_bin(0),
      O => BCD0(0)
    );
\BCD1[1]_INST_0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"C3611C86"
    )
        port map (
      I0 => valoare_bin(3),
      I1 => valoare_bin(4),
      I2 => valoare_bin(2),
      I3 => valoare_bin(1),
      I4 => valoare_bin(0),
      O => BCD1(0)
    );
\BCD1[2]_INST_0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"249A45A2"
    )
        port map (
      I0 => valoare_bin(1),
      I1 => valoare_bin(2),
      I2 => valoare_bin(4),
      I3 => valoare_bin(3),
      I4 => valoare_bin(0),
      O => BCD1(1)
    );
\BCD1[3]_INST_0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"41201804"
    )
        port map (
      I0 => valoare_bin(1),
      I1 => valoare_bin(2),
      I2 => valoare_bin(4),
      I3 => valoare_bin(3),
      I4 => valoare_bin(0),
      O => BCD1(2)
    );
\_inferred__0/i_\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"B424"
    )
        port map (
      I0 => valoare_bin(2),
      I1 => valoare_bin(4),
      I2 => valoare_bin(3),
      I3 => valoare_bin(1),
      O => BCD0(1)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_bin2bcd_1_0 is
  port (
    valoare_bin : in STD_LOGIC_VECTOR ( 5 downto 0 );
    BCD0 : out STD_LOGIC_VECTOR ( 3 downto 0 );
    BCD1 : out STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of design_1_bin2bcd_1_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of design_1_bin2bcd_1_0 : entity is "design_1_bin2bcd_1_0,bin2bcd,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of design_1_bin2bcd_1_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of design_1_bin2bcd_1_0 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of design_1_bin2bcd_1_0 : entity is "bin2bcd,Vivado 2021.2";
end design_1_bin2bcd_1_0;

architecture STRUCTURE of design_1_bin2bcd_1_0 is
  signal \<const0>\ : STD_LOGIC;
  signal \^bcd0\ : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal \^bcd1\ : STD_LOGIC_VECTOR ( 3 downto 1 );
  signal \^valoare_bin\ : STD_LOGIC_VECTOR ( 5 downto 0 );
begin
  BCD0(3) <= \<const0>\;
  BCD0(2 downto 0) <= \^bcd0\(2 downto 0);
  BCD1(3 downto 1) <= \^bcd1\(3 downto 1);
  BCD1(0) <= \^valoare_bin\(0);
  \^valoare_bin\(5 downto 0) <= valoare_bin(5 downto 0);
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
inst: entity work.design_1_bin2bcd_1_0_bin2bcd
     port map (
      BCD0(1 downto 0) => \^bcd0\(1 downto 0),
      BCD1(2 downto 0) => \^bcd1\(3 downto 1),
      valoare_bin(4 downto 0) => \^valoare_bin\(5 downto 1)
    );
\inst/\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"E0"
    )
        port map (
      I0 => \^valoare_bin\(3),
      I1 => \^valoare_bin\(4),
      I2 => \^valoare_bin\(5),
      O => \^bcd0\(2)
    );
end STRUCTURE;
