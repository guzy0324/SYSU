vlib work
vlib msim

vlib msim/dist_mem_gen_v8_0_9
vlib msim/xil_defaultlib

vmap dist_mem_gen_v8_0_9 msim/dist_mem_gen_v8_0_9
vmap xil_defaultlib msim/xil_defaultlib

vcom -work dist_mem_gen_v8_0_9 -64 \
"../../../ipstatic/dist_mem_gen_v8_0_9/simulation/dist_mem_gen_v8_0.vhd" \

vcom -work xil_defaultlib -64 \
"../../../../pipeline.srcs/sources_1/ip/InstructionROM/sim/InstructionROM.vhd" \


