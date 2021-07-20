onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib display_0_opt

do {wave.do}

view wave
view structure
view signals

do {display_0.udo}

run -all

quit -force
