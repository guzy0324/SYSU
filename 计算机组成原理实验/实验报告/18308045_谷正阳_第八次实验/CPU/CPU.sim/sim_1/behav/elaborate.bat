@echo off
set xv_path=C:\\Xilinx\\Vivado\\2015.4\\bin
call %xv_path%/xelab  -wto b825ecf65d0a46bf8113eb1a07b15aa0 -m64 --debug typical --relax --mt 2 -L blk_mem_gen_v8_3_1 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot topsim_behav xil_defaultlib.topsim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
