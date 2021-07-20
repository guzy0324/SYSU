vlib work
vlib activehdl

vlib activehdl/xil_defaultlib

vmap xil_defaultlib activehdl/xil_defaultlib

vlog -work xil_defaultlib  -v2k5 \
"../../../bd/design_1/ipshared/8eac/sysu_74LS283.v" \
"../../../bd/design_1/ip/design_1_sysu_74LS283_0_0/sim/design_1_sysu_74LS283_0_0.v" \
"../../../bd/design_1/ipshared/0fce/sysu_74LS86.v" \
"../../../bd/design_1/ip/design_1_sysu_74LS86_0_0/sim/design_1_sysu_74LS86_0_0.v" \
"../../../bd/design_1/sim/design_1.v" \
"../../../bd/design_1/ipshared/5caf/chip_74ls32.v" \
"../../../bd/design_1/ip/design_1_sysu_74LS32_0_0/sim/design_1_sysu_74LS32_0_0.v" \
"../../../bd/design_1/ipshared/2c5c/chip_74ls08.v" \
"../../../bd/design_1/ip/design_1_sysu_74LS08_0_0/sim/design_1_sysu_74LS08_0_0.v" \
"../../../bd/design_1/ipshared/3c12/chip_74ls04.v" \
"../../../bd/design_1/ip/design_1_sysu_74LS04_0_0/sim/design_1_sysu_74LS04_0_0.v" \
"../../../bd/design_1/ipshared/c179/sysu_high_level.v" \
"../../../bd/design_1/ip/design_1_sysu_high_level_0_1/sim/design_1_sysu_high_level_0_1.v" \
"../../../bd/design_1/ipshared/b3dc/sysu_low_level.v" \
"../../../bd/design_1/ip/design_1_sysu_low_level_0_1/sim/design_1_sysu_low_level_0_1.v" \


vlog -work xil_defaultlib \
"glbl.v"

