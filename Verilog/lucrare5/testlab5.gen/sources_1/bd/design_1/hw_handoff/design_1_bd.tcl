
################################################################
# This is a generated script based on design: design_1
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2020.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_gid_msg -ssname BD::TCL -id 2041 -severity "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl


# The design that will be created by this Tcl script contains the following 
# module references:
# adun_scad, ajustare, alege, aliniere, compara, concatenare, extragere, norm, refacere, registru16, registru16, registru24, registru26, registru48, registru48, registru57, registru8, registru8, registru8, rezultatFinal

# Please add the sources of those modules before sourcing this Tcl script.

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xc7a100tcsg324-1
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name design_1

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_gid_msg -ssname BD::TCL -id 2001 -severity "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_gid_msg -ssname BD::TCL -id 2002 -severity "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_gid_msg -ssname BD::TCL -id 2003 -severity "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_gid_msg -ssname BD::TCL -id 2004 -severity "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_gid_msg -ssname BD::TCL -id 2005 -severity "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_gid_msg -ssname BD::TCL -id 2006 -severity "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2090 -severity "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2091 -severity "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set clear_0 [ create_bd_port -dir I clear_0 ]
  set clk_0 [ create_bd_port -dir I -type clk clk_0 ]
  set load_0 [ create_bd_port -dir I load_0 ]
  set number1_0 [ create_bd_port -dir I -from 32 -to 0 number1_0 ]
  set number2_0 [ create_bd_port -dir I -from 32 -to 0 number2_0 ]
  set op_0 [ create_bd_port -dir I op_0 ]
  set result_0 [ create_bd_port -dir O -from 31 -to 0 result_0 ]

  # Create instance: adun_scad_0, and set properties
  set block_name adun_scad
  set block_cell_name adun_scad_0
  if { [catch {set adun_scad_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $adun_scad_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: ajustare_0, and set properties
  set block_name ajustare
  set block_cell_name ajustare_0
  if { [catch {set ajustare_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $ajustare_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: alege_0, and set properties
  set block_name alege
  set block_cell_name alege_0
  if { [catch {set alege_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $alege_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: aliniere_0, and set properties
  set block_name aliniere
  set block_cell_name aliniere_0
  if { [catch {set aliniere_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $aliniere_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: compara_0, and set properties
  set block_name compara
  set block_cell_name compara_0
  if { [catch {set compara_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $compara_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: concatenare_0, and set properties
  set block_name concatenare
  set block_cell_name concatenare_0
  if { [catch {set concatenare_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $concatenare_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: extragere_0, and set properties
  set block_name extragere
  set block_cell_name extragere_0
  if { [catch {set extragere_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $extragere_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: norm_0, and set properties
  set block_name norm
  set block_cell_name norm_0
  if { [catch {set norm_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $norm_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: refacere_0, and set properties
  set block_name refacere
  set block_cell_name refacere_0
  if { [catch {set refacere_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $refacere_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru16_0, and set properties
  set block_name registru16
  set block_cell_name registru16_0
  if { [catch {set registru16_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru16_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru16_1, and set properties
  set block_name registru16
  set block_cell_name registru16_1
  if { [catch {set registru16_1 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru16_1 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru24_0, and set properties
  set block_name registru24
  set block_cell_name registru24_0
  if { [catch {set registru24_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru24_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru26_0, and set properties
  set block_name registru26
  set block_cell_name registru26_0
  if { [catch {set registru26_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru26_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru48_0, and set properties
  set block_name registru48
  set block_cell_name registru48_0
  if { [catch {set registru48_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru48_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru48_1, and set properties
  set block_name registru48
  set block_cell_name registru48_1
  if { [catch {set registru48_1 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru48_1 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru57_0, and set properties
  set block_name registru57
  set block_cell_name registru57_0
  if { [catch {set registru57_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru57_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru8_0, and set properties
  set block_name registru8
  set block_cell_name registru8_0
  if { [catch {set registru8_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru8_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru8_1, and set properties
  set block_name registru8
  set block_cell_name registru8_1
  if { [catch {set registru8_1 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru8_1 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: registru8_2, and set properties
  set block_name registru8
  set block_cell_name registru8_2
  if { [catch {set registru8_2 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $registru8_2 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create instance: rezultatFinal_0, and set properties
  set block_name rezultatFinal
  set block_cell_name rezultatFinal_0
  if { [catch {set rezultatFinal_0 [create_bd_cell -type module -reference $block_name $block_cell_name] } errmsg] } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2095 -severity "ERROR" "Unable to add referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   } elseif { $rezultatFinal_0 eq "" } {
     catch {common::send_gid_msg -ssname BD::TCL -id 2096 -severity "ERROR" "Unable to referenced block <$block_name>. Please add the files for ${block_name}'s definition into the project."}
     return 1
   }
  
  # Create port connections
  connect_bd_net -net adun_scad_0_outt [get_bd_pins adun_scad_0/outt] [get_bd_pins registru26_0/inn]
  connect_bd_net -net ajustare_0_outt [get_bd_pins ajustare_0/outt] [get_bd_pins registru8_2/inn]
  connect_bd_net -net alege_0_outt [get_bd_pins alege_0/outt] [get_bd_pins registru8_0/inn]
  connect_bd_net -net aliniere_0_outt [get_bd_pins aliniere_0/outt] [get_bd_pins registru48_1/inn]
  connect_bd_net -net clear_0_1 [get_bd_ports clear_0] [get_bd_pins registru16_0/clear] [get_bd_pins registru16_1/clear] [get_bd_pins registru24_0/clear] [get_bd_pins registru26_0/clear] [get_bd_pins registru48_0/clear] [get_bd_pins registru48_1/clear] [get_bd_pins registru57_0/clear] [get_bd_pins registru8_0/clear] [get_bd_pins registru8_1/clear] [get_bd_pins registru8_2/clear]
  connect_bd_net -net clk_0_1 [get_bd_ports clk_0] [get_bd_pins registru16_0/clk] [get_bd_pins registru16_1/clk] [get_bd_pins registru24_0/clk] [get_bd_pins registru26_0/clk] [get_bd_pins registru48_0/clk] [get_bd_pins registru48_1/clk] [get_bd_pins registru57_0/clk] [get_bd_pins registru8_0/clk] [get_bd_pins registru8_1/clk] [get_bd_pins registru8_2/clk]
  connect_bd_net -net compara_0_out1 [get_bd_pins compara_0/out1] [get_bd_pins registru16_1/inn]
  connect_bd_net -net compara_0_out2 [get_bd_pins compara_0/out2] [get_bd_pins concatenare_0/comp]
  connect_bd_net -net concatenare_0_outt [get_bd_pins concatenare_0/outt] [get_bd_pins registru57_0/inn]
  connect_bd_net -net extragere_0_exp1 [get_bd_pins extragere_0/exp1] [get_bd_pins refacere_0/exp1]
  connect_bd_net -net extragere_0_exp2 [get_bd_pins extragere_0/exp2] [get_bd_pins refacere_0/exp2]
  connect_bd_net -net extragere_0_mant1 [get_bd_pins extragere_0/mant1] [get_bd_pins refacere_0/mant1]
  connect_bd_net -net extragere_0_mant2 [get_bd_pins extragere_0/mant2] [get_bd_pins refacere_0/mant2]
  connect_bd_net -net load_0_1 [get_bd_ports load_0] [get_bd_pins registru16_0/load] [get_bd_pins registru16_1/load] [get_bd_pins registru24_0/load] [get_bd_pins registru26_0/load] [get_bd_pins registru48_0/load] [get_bd_pins registru48_1/load] [get_bd_pins registru57_0/load] [get_bd_pins registru8_0/load] [get_bd_pins registru8_1/load] [get_bd_pins registru8_2/load]
  connect_bd_net -net norm_0_out1 [get_bd_pins norm_0/out1] [get_bd_pins registru24_0/inn]
  connect_bd_net -net norm_0_out2 [get_bd_pins ajustare_0/inn] [get_bd_pins norm_0/out2]
  connect_bd_net -net number1_0_1 [get_bd_ports number1_0] [get_bd_pins extragere_0/number1]
  connect_bd_net -net number2_0_1 [get_bd_ports number2_0] [get_bd_pins extragere_0/number2]
  connect_bd_net -net op_0_1 [get_bd_ports op_0] [get_bd_pins adun_scad_0/op]
  connect_bd_net -net refacere_0_exponenti [get_bd_pins refacere_0/exponenti] [get_bd_pins registru16_0/inn]
  connect_bd_net -net refacere_0_mantise [get_bd_pins refacere_0/mantise] [get_bd_pins registru48_0/inn]
  connect_bd_net -net registru16_0_outt [get_bd_pins compara_0/inn] [get_bd_pins registru16_0/outt]
  connect_bd_net -net registru16_1_outt [get_bd_pins alege_0/inn] [get_bd_pins registru16_1/outt]
  connect_bd_net -net registru24_0_out [get_bd_pins registru24_0/outt] [get_bd_pins rezultatFinal_0/mantisa]
  connect_bd_net -net registru26_0_outt [get_bd_pins norm_0/inn] [get_bd_pins registru26_0/outt]
  connect_bd_net -net registru48_0_outt [get_bd_pins concatenare_0/inn] [get_bd_pins registru48_0/outt]
  connect_bd_net -net registru48_1_outt [get_bd_pins adun_scad_0/inn] [get_bd_pins registru48_1/outt]
  connect_bd_net -net registru57_0_outt [get_bd_pins aliniere_0/inn] [get_bd_pins registru57_0/outt]
  connect_bd_net -net registru8_0_outt [get_bd_pins registru8_0/outt] [get_bd_pins registru8_1/inn]
  connect_bd_net -net registru8_1_out [get_bd_pins ajustare_0/exp] [get_bd_pins registru8_1/outt]
  connect_bd_net -net registru8_2_out [get_bd_pins registru8_2/outt] [get_bd_pins rezultatFinal_0/exponent]
  connect_bd_net -net rezultatFinal_0_result [get_bd_ports result_0] [get_bd_pins rezultatFinal_0/result]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  validate_bd_design
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


