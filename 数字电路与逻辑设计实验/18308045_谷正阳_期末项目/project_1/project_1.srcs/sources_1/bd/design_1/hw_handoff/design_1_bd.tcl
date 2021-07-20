
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
set scripts_vivado_version 2017.4
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source design_1_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xc7s50csga324-1
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
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

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

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
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
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports

  # Create ports
  set F [ create_bd_port -dir O F ]
  set I0 [ create_bd_port -dir I I0 ]
  set I1 [ create_bd_port -dir I I1 ]
  set I2 [ create_bd_port -dir I I2 ]
  set I3 [ create_bd_port -dir I I3 ]
  set M [ create_bd_port -dir I M ]
  set O0 [ create_bd_port -dir O O0 ]
  set O1 [ create_bd_port -dir O O1 ]
  set O2 [ create_bd_port -dir O O2 ]
  set O3 [ create_bd_port -dir O O3 ]

  # Create instance: sysu_74LS04_0, and set properties
  set sysu_74LS04_0 [ create_bd_cell -type ip -vlnv sysu:user:sysu_74LS04:1.0 sysu_74LS04_0 ]

  # Create instance: sysu_74LS08_0, and set properties
  set sysu_74LS08_0 [ create_bd_cell -type ip -vlnv sysu:user:sysu_74LS08:1.0 sysu_74LS08_0 ]

  # Create instance: sysu_74LS283_0, and set properties
  set sysu_74LS283_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:sysu_74LS283:1.0 sysu_74LS283_0 ]

  # Create instance: sysu_74LS32_0, and set properties
  set sysu_74LS32_0 [ create_bd_cell -type ip -vlnv sysu:user:sysu_74LS32:1.0 sysu_74LS32_0 ]

  # Create instance: sysu_74LS86_0, and set properties
  set sysu_74LS86_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:sysu_74LS86:1.0 sysu_74LS86_0 ]

  # Create instance: sysu_high_level_0, and set properties
  set sysu_high_level_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:sysu_high_level:1.0 sysu_high_level_0 ]

  # Create instance: sysu_low_level_0, and set properties
  set sysu_low_level_0 [ create_bd_cell -type ip -vlnv xilinx.com:user:sysu_low_level:1.0 sysu_low_level_0 ]

  # Create port connections
  connect_bd_net -net A1_0_1 [get_bd_ports I1] [get_bd_pins sysu_74LS283_0/A1] [get_bd_pins sysu_74LS32_0/B1]
  connect_bd_net -net A2_0_1 [get_bd_ports I2] [get_bd_pins sysu_74LS283_0/A2] [get_bd_pins sysu_74LS32_0/A1]
  connect_bd_net -net A3_0_1 [get_bd_ports I3] [get_bd_pins sysu_74LS08_0/A1] [get_bd_pins sysu_74LS283_0/A3]
  connect_bd_net -net I0_1 [get_bd_ports I0] [get_bd_pins sysu_74LS283_0/A0]
  connect_bd_net -net Net [get_bd_ports M] [get_bd_pins sysu_74LS04_0/A1] [get_bd_pins sysu_74LS08_0/A4] [get_bd_pins sysu_74LS283_0/Ci] [get_bd_pins sysu_74LS86_0/B1] [get_bd_pins sysu_74LS86_0/B2] [get_bd_pins sysu_74LS86_0/B3] [get_bd_pins sysu_74LS86_0/B4]
  connect_bd_net -net sysu_74LS04_0_Y1 [get_bd_pins sysu_74LS04_0/Y1] [get_bd_pins sysu_74LS08_0/B3]
  connect_bd_net -net sysu_74LS08_0_Y1 [get_bd_pins sysu_74LS08_0/A3] [get_bd_pins sysu_74LS08_0/Y1]
  connect_bd_net -net sysu_74LS08_0_Y2 [get_bd_pins sysu_74LS08_0/B4] [get_bd_pins sysu_74LS08_0/Y2]
  connect_bd_net -net sysu_74LS08_0_Y3 [get_bd_pins sysu_74LS08_0/Y3] [get_bd_pins sysu_74LS32_0/A3]
  connect_bd_net -net sysu_74LS08_0_Y4 [get_bd_pins sysu_74LS08_0/Y4] [get_bd_pins sysu_74LS32_0/B3]
  connect_bd_net -net sysu_74LS283_0_S0 [get_bd_ports O0] [get_bd_pins sysu_74LS283_0/S0]
  connect_bd_net -net sysu_74LS283_0_S1 [get_bd_ports O1] [get_bd_pins sysu_74LS283_0/S1] [get_bd_pins sysu_74LS32_0/A2]
  connect_bd_net -net sysu_74LS283_0_S2 [get_bd_ports O2] [get_bd_pins sysu_74LS283_0/S2] [get_bd_pins sysu_74LS32_0/B2]
  connect_bd_net -net sysu_74LS283_0_S3 [get_bd_ports O3] [get_bd_pins sysu_74LS08_0/B2] [get_bd_pins sysu_74LS283_0/S3]
  connect_bd_net -net sysu_74LS32_0_Y1 [get_bd_pins sysu_74LS08_0/B1] [get_bd_pins sysu_74LS32_0/Y1]
  connect_bd_net -net sysu_74LS32_0_Y2 [get_bd_pins sysu_74LS08_0/A2] [get_bd_pins sysu_74LS32_0/Y2]
  connect_bd_net -net sysu_74LS32_0_Y3 [get_bd_ports F] [get_bd_pins sysu_74LS32_0/Y3]
  connect_bd_net -net sysu_74LS86_0_Y1 [get_bd_pins sysu_74LS283_0/B3] [get_bd_pins sysu_74LS86_0/Y1]
  connect_bd_net -net sysu_74LS86_0_Y2 [get_bd_pins sysu_74LS283_0/B2] [get_bd_pins sysu_74LS86_0/Y2]
  connect_bd_net -net sysu_74LS86_0_Y3 [get_bd_pins sysu_74LS283_0/B1] [get_bd_pins sysu_74LS86_0/Y3]
  connect_bd_net -net sysu_74LS86_0_Y4 [get_bd_pins sysu_74LS283_0/B0] [get_bd_pins sysu_74LS86_0/Y4]
  connect_bd_net -net sysu_high_level_0_high [get_bd_pins sysu_74LS86_0/A2] [get_bd_pins sysu_74LS86_0/A4] [get_bd_pins sysu_high_level_0/high]
  connect_bd_net -net sysu_low_level_0_low [get_bd_pins sysu_74LS86_0/A1] [get_bd_pins sysu_74LS86_0/A3] [get_bd_pins sysu_low_level_0/low]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


