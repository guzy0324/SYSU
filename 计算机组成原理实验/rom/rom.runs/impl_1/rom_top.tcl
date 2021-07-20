proc start_step { step } {
  set stopFile ".stop.rst"
  if {[file isfile .stop.rst]} {
    puts ""
    puts "*** Halting run - EA reset detected ***"
    puts ""
    puts ""
    return -code error
  }
  set beginFile ".$step.begin.rst"
  set platform "$::tcl_platform(platform)"
  set user "$::tcl_platform(user)"
  set pid [pid]
  set host ""
  if { [string equal $platform unix] } {
    if { [info exist ::env(HOSTNAME)] } {
      set host $::env(HOSTNAME)
    }
  } else {
    if { [info exist ::env(COMPUTERNAME)] } {
      set host $::env(COMPUTERNAME)
    }
  }
  set ch [open $beginFile w]
  puts $ch "<?xml version=\"1.0\"?>"
  puts $ch "<ProcessHandle Version=\"1\" Minor=\"0\">"
  puts $ch "    <Process Command=\".planAhead.\" Owner=\"$user\" Host=\"$host\" Pid=\"$pid\">"
  puts $ch "    </Process>"
  puts $ch "</ProcessHandle>"
  close $ch
}

proc end_step { step } {
  set endFile ".$step.end.rst"
  set ch [open $endFile w]
  close $ch
}

proc step_failed { step } {
  set endFile ".$step.error.rst"
  set ch [open $endFile w]
  close $ch
}

set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000

start_step init_design
set rc [catch {
  create_msg_db init_design.pb
  set_param xicom.use_bs_reader 1
  set_property design_mode GateLvl [current_fileset]
  set_property webtalk.parent_dir C:/Users/guzy0/rom/rom.cache/wt [current_project]
  set_property parent.project_path C:/Users/guzy0/rom/rom.xpr [current_project]
  set_property ip_repo_paths c:/Users/guzy0/rom/rom.cache/ip [current_project]
  set_property ip_output_repo c:/Users/guzy0/rom/rom.cache/ip [current_project]
  add_files -quiet C:/Users/guzy0/rom/rom.runs/synth_1/rom_top.dcp
  add_files -quiet C:/Users/guzy0/rom/rom.runs/Ins_Rom_synth_1/Ins_Rom.dcp
  set_property netlist_only true [get_files C:/Users/guzy0/rom/rom.runs/Ins_Rom_synth_1/Ins_Rom.dcp]
  add_files -quiet C:/Users/guzy0/rom/rom.runs/Ins_Rom_2_synth_1/Ins_Rom_2.dcp
  set_property netlist_only true [get_files C:/Users/guzy0/rom/rom.runs/Ins_Rom_2_synth_1/Ins_Rom_2.dcp]
  read_xdc -mode out_of_context -ref Ins_Rom c:/Users/guzy0/rom/rom.srcs/sources_1/ip/Ins_Rom/Ins_Rom_ooc.xdc
  set_property processing_order EARLY [get_files c:/Users/guzy0/rom/rom.srcs/sources_1/ip/Ins_Rom/Ins_Rom_ooc.xdc]
  read_xdc -mode out_of_context -ref Ins_Rom_2 c:/Users/guzy0/rom/rom.srcs/sources_1/ip/Ins_Rom_2/Ins_Rom_2_ooc.xdc
  set_property processing_order EARLY [get_files c:/Users/guzy0/rom/rom.srcs/sources_1/ip/Ins_Rom_2/Ins_Rom_2_ooc.xdc]
  read_xdc C:/Users/guzy0/rom/rom.srcs/constrs_1/new/constraint.xdc
  link_design -top rom_top -part xc7a35tcpg236-1
  close_msg_db -file init_design.pb
} RESULT]
if {$rc} {
  step_failed init_design
  return -code error $RESULT
} else {
  end_step init_design
}

start_step opt_design
set rc [catch {
  create_msg_db opt_design.pb
  catch {write_debug_probes -quiet -force debug_nets}
  opt_design 
  write_checkpoint -force rom_top_opt.dcp
  report_drc -file rom_top_drc_opted.rpt
  close_msg_db -file opt_design.pb
} RESULT]
if {$rc} {
  step_failed opt_design
  return -code error $RESULT
} else {
  end_step opt_design
}

start_step place_design
set rc [catch {
  create_msg_db place_design.pb
  catch {write_hwdef -file rom_top.hwdef}
  place_design 
  write_checkpoint -force rom_top_placed.dcp
  report_io -file rom_top_io_placed.rpt
  report_utilization -file rom_top_utilization_placed.rpt -pb rom_top_utilization_placed.pb
  report_control_sets -verbose -file rom_top_control_sets_placed.rpt
  close_msg_db -file place_design.pb
} RESULT]
if {$rc} {
  step_failed place_design
  return -code error $RESULT
} else {
  end_step place_design
}

start_step route_design
set rc [catch {
  create_msg_db route_design.pb
  route_design 
  write_checkpoint -force rom_top_routed.dcp
  report_drc -file rom_top_drc_routed.rpt -pb rom_top_drc_routed.pb
  report_timing_summary -warn_on_violation -max_paths 10 -file rom_top_timing_summary_routed.rpt -rpx rom_top_timing_summary_routed.rpx
  report_power -file rom_top_power_routed.rpt -pb rom_top_power_summary_routed.pb
  report_route_status -file rom_top_route_status.rpt -pb rom_top_route_status.pb
  report_clock_utilization -file rom_top_clock_utilization_routed.rpt
  close_msg_db -file route_design.pb
} RESULT]
if {$rc} {
  step_failed route_design
  return -code error $RESULT
} else {
  end_step route_design
}

start_step write_bitstream
set rc [catch {
  create_msg_db write_bitstream.pb
  catch { write_mem_info -force rom_top.mmi }
  write_bitstream -force rom_top.bit 
  catch { write_sysdef -hwdef rom_top.hwdef -bitfile rom_top.bit -meminfo rom_top.mmi -file rom_top.sysdef }
  close_msg_db -file write_bitstream.pb
} RESULT]
if {$rc} {
  step_failed write_bitstream
  return -code error $RESULT
} else {
  end_step write_bitstream
}

