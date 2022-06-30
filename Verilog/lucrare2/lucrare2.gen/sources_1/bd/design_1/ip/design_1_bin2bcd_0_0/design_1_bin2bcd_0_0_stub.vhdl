-- Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2021.2 (win64) Build 3367213 Tue Oct 19 02:48:09 MDT 2021
-- Date        : Tue Mar 29 18:53:32 2022
-- Host        : DESKTOP-620LK0K running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/student/Desktop/Emanuel/project3/project3.gen/sources_1/bd/design_1/ip/design_1_bin2bcd_0_0/design_1_bin2bcd_0_0_stub.vhdl
-- Design      : design_1_bin2bcd_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_bin2bcd_0_0 is
  Port ( 
    valoare_bin : in STD_LOGIC_VECTOR ( 5 downto 0 );
    BCD0 : out STD_LOGIC_VECTOR ( 3 downto 0 );
    BCD1 : out STD_LOGIC_VECTOR ( 3 downto 0 )
  );

end design_1_bin2bcd_0_0;

architecture stub of design_1_bin2bcd_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "valoare_bin[5:0],BCD0[3:0],BCD1[3:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "bin2bcd,Vivado 2021.2";
begin
end;