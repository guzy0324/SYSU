onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib irom_opt

do {wave.do}

view wave
view structure
view signals

do {irom.udo}

run -all

quit -force
