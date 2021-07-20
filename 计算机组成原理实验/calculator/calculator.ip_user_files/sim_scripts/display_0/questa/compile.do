vlib work
vlib msim

vlib msim/xil_defaultlib

vmap xil_defaultlib msim/xil_defaultlib

vlog -work xil_defaultlib -64 \
"../../../../calculator.srcs/sources_1/ip/display_0/display.v" \
"../../../../calculator.srcs/sources_1/ip/display_0/sim/display_0.v" \


vlog -work xil_defaultlib "glbl.v"

