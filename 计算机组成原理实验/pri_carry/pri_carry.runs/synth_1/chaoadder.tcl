# 
# Synthesis run script generated by Vivado
# 

set_param xicom.use_bs_reader 1
debug::add_scope template.lib 1
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
set_msg_config -id {Synth 8-256} -limit 10000
set_msg_config -id {Synth 8-638} -limit 10000
create_project -in_memory -part xc7a35tcpg236-1

set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Users/Administrator/Desktop/project/pri_carry/pri_carry.cache/wt [current_project]
set_property parent.project_path C:/Users/Administrator/Desktop/project/pri_carry/pri_carry.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
read_verilog -library xil_defaultlib C:/Users/Administrator/Desktop/project/pri_carry/pri_carry.srcs/sources_1/new/addsub.v
synth_design -top chaoadder -part xc7a35tcpg236-1
write_checkpoint -noxdef chaoadder.dcp
catch { report_utilization -file chaoadder_utilization_synth.rpt -pb chaoadder_utilization_synth.pb }
