# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "F" -parent ${Page_0}


}

proc update_PARAM_VALUE.F { PARAM_VALUE.F } {
	# Procedure called to update F when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.F { PARAM_VALUE.F } {
	# Procedure called to validate F
	return true
}


proc update_MODELPARAM_VALUE.F { MODELPARAM_VALUE.F PARAM_VALUE.F } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.F}] ${MODELPARAM_VALUE.F}
}

