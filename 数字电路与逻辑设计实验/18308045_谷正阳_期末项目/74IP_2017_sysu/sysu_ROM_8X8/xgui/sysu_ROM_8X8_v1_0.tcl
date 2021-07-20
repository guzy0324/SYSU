# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "R1" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R2" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R3" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R4" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R5" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R6" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R7" -parent ${Page_0}
  ipgui::add_param $IPINST -name "R8" -parent ${Page_0}


}

proc update_PARAM_VALUE.R1 { PARAM_VALUE.R1 } {
	# Procedure called to update R1 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R1 { PARAM_VALUE.R1 } {
	# Procedure called to validate R1
	return true
}

proc update_PARAM_VALUE.R2 { PARAM_VALUE.R2 } {
	# Procedure called to update R2 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R2 { PARAM_VALUE.R2 } {
	# Procedure called to validate R2
	return true
}

proc update_PARAM_VALUE.R3 { PARAM_VALUE.R3 } {
	# Procedure called to update R3 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R3 { PARAM_VALUE.R3 } {
	# Procedure called to validate R3
	return true
}

proc update_PARAM_VALUE.R4 { PARAM_VALUE.R4 } {
	# Procedure called to update R4 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R4 { PARAM_VALUE.R4 } {
	# Procedure called to validate R4
	return true
}

proc update_PARAM_VALUE.R5 { PARAM_VALUE.R5 } {
	# Procedure called to update R5 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R5 { PARAM_VALUE.R5 } {
	# Procedure called to validate R5
	return true
}

proc update_PARAM_VALUE.R6 { PARAM_VALUE.R6 } {
	# Procedure called to update R6 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R6 { PARAM_VALUE.R6 } {
	# Procedure called to validate R6
	return true
}

proc update_PARAM_VALUE.R7 { PARAM_VALUE.R7 } {
	# Procedure called to update R7 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R7 { PARAM_VALUE.R7 } {
	# Procedure called to validate R7
	return true
}

proc update_PARAM_VALUE.R8 { PARAM_VALUE.R8 } {
	# Procedure called to update R8 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.R8 { PARAM_VALUE.R8 } {
	# Procedure called to validate R8
	return true
}


proc update_MODELPARAM_VALUE.R1 { MODELPARAM_VALUE.R1 PARAM_VALUE.R1 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R1}] ${MODELPARAM_VALUE.R1}
}

proc update_MODELPARAM_VALUE.R2 { MODELPARAM_VALUE.R2 PARAM_VALUE.R2 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R2}] ${MODELPARAM_VALUE.R2}
}

proc update_MODELPARAM_VALUE.R3 { MODELPARAM_VALUE.R3 PARAM_VALUE.R3 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R3}] ${MODELPARAM_VALUE.R3}
}

proc update_MODELPARAM_VALUE.R4 { MODELPARAM_VALUE.R4 PARAM_VALUE.R4 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R4}] ${MODELPARAM_VALUE.R4}
}

proc update_MODELPARAM_VALUE.R5 { MODELPARAM_VALUE.R5 PARAM_VALUE.R5 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R5}] ${MODELPARAM_VALUE.R5}
}

proc update_MODELPARAM_VALUE.R6 { MODELPARAM_VALUE.R6 PARAM_VALUE.R6 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R6}] ${MODELPARAM_VALUE.R6}
}

proc update_MODELPARAM_VALUE.R7 { MODELPARAM_VALUE.R7 PARAM_VALUE.R7 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R7}] ${MODELPARAM_VALUE.R7}
}

proc update_MODELPARAM_VALUE.R8 { MODELPARAM_VALUE.R8 PARAM_VALUE.R8 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.R8}] ${MODELPARAM_VALUE.R8}
}

