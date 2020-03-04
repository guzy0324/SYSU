@echo off
set xv_path=C:\\Xilinx\\Vivado\\2015.4\\bin
call %xv_path%/xelab  -wto da0cd20755a542b386f73f7c9d73f50c -m64 --debug typical --relax --mt 2 -L dist_mem_gen_v8_0_9 -L xil_defaultlib -L blk_mem_gen_v8_3_1 -L unisims_ver -L unimacro_ver -L secureip --snapshot sim_behav xil_defaultlib.sim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
