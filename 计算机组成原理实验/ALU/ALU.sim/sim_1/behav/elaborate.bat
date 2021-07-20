@echo off
set xv_path=C:\\Xilinx\\Vivado\\2015.4\\bin
call %xv_path%/xelab  -wto 4cfea5ee8a4e4a56979eef542eea4a2c -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot alusim_behav xil_defaultlib.alusim xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
