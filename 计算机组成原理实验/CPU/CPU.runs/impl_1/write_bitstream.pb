
?
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2"
Implementation2default:default2
xc7a35t2default:defaultZ17-347h px? 
?
0Got license for feature '%s' and/or device '%s'
310*common2"
Implementation2default:default2
xc7a35t2default:defaultZ17-349h px? 
?
?The version limit for your license is '%s' and will expire in %s days. A version limit expiration means that, although you may be able to continue to use the current version of tools or IP with this license, you will not be eligible for any updates or new releases.
519*common2
2019.062default:default2
-1652default:defaultZ17-1223h px? 
x
,Running DRC as a precondition to command %s
1349*	planAhead2#
write_bitstream2default:defaultZ12-1349h px? 
P
Running DRC with %s threads
24*drc2
22default:defaultZ23-27h px? 
?
Rule violation (%s) %s - %s
20*drc2
CFGBVS-12default:default2G
3Missing CFGBVS and CONFIG_VOLTAGE Design Properties2default:default2?
?Neither the CFGBVS nor CONFIG_VOLTAGE voltage property is set in the current_design.  Configuration bank voltage select (CFGBVS) must be set to VCCO or GND, and CONFIG_VOLTAGE must be set to the correct configuration voltage, in order to determine the I/O voltage support for the pins in bank 0.  It is suggested to specify these either using the 'Edit Device Properties' function in the GUI or directly in the XDC file using the following syntax:

 set_property CFGBVS value1 [current_design]
 #where value1 is either VCCO or GND

 set_property CONFIG_VOLTAGE value2 [current_design]
 #where value2 is the voltage provided to configuration bank 0

Refer to the device configuration user guide for more information.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
lDSP alu/aluRes0 input alu/aluRes0/A[29:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
lDSP alu/aluRes0 input alu/aluRes0/B[17:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
rDSP alu/aluRes0__0 input alu/aluRes0__0/A[29:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
rDSP alu/aluRes0__0 input alu/aluRes0__0/B[17:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
rDSP alu/aluRes0__1 input alu/aluRes0__1/A[29:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
rDSP alu/aluRes0__1 input alu/aluRes0__1/B[17:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
rDSP alu/aluRes0__2 input alu/aluRes0__2/A[29:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPIP-12default:default2$
Input pipelining2default:default2?
rDSP alu/aluRes0__2 input alu/aluRes0__2/B[17:0] is not pipelined. Pipelining DSP48 input will improve performance.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-12default:default2*
PREG Output pipelining2default:default2?
?DSP alu/aluRes0 output alu/aluRes0/P[47:0] is not pipelined (PREG=0). Pipelining the DSP48 output will improve performance and often saves power so it is suggested whenever possible to fully pipeline this function.  If this DSP48 function was inferred, it is suggested to describe an additional register stage after this function.  If the DSP48 was instantiated in the design, it is suggested to set the PREG attribute to 1.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-12default:default2*
PREG Output pipelining2default:default2?
?DSP alu/aluRes0__0 output alu/aluRes0__0/P[47:0] is not pipelined (PREG=0). Pipelining the DSP48 output will improve performance and often saves power so it is suggested whenever possible to fully pipeline this function.  If this DSP48 function was inferred, it is suggested to describe an additional register stage after this function.  If the DSP48 was instantiated in the design, it is suggested to set the PREG attribute to 1.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-12default:default2*
PREG Output pipelining2default:default2?
?DSP alu/aluRes0__1 output alu/aluRes0__1/P[47:0] is not pipelined (PREG=0). Pipelining the DSP48 output will improve performance and often saves power so it is suggested whenever possible to fully pipeline this function.  If this DSP48 function was inferred, it is suggested to describe an additional register stage after this function.  If the DSP48 was instantiated in the design, it is suggested to set the PREG attribute to 1.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-12default:default2*
PREG Output pipelining2default:default2?
?DSP alu/aluRes0__2 output alu/aluRes0__2/P[47:0] is not pipelined (PREG=0). Pipelining the DSP48 output will improve performance and often saves power so it is suggested whenever possible to fully pipeline this function.  If this DSP48 function was inferred, it is suggested to describe an additional register stage after this function.  If the DSP48 was instantiated in the design, it is suggested to set the PREG attribute to 1.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-22default:default2*
MREG Output pipelining2default:default2?
?DSP alu/aluRes0 multiplier stage alu/aluRes0/P[47:0] is not pipelined (MREG=0). Pipelining the multiplier function will improve performance and will save significant power so it is suggested whenever possible to fully pipeline this function.  If this multiplier was inferred, it is suggested to describe an additional register stage after this function.  If there is no registered adder/accumulator following the multiply function, two pipeline stages are suggested to allow both the MREG and PREG registers to be used.  If the DSP48 was instantiated in the design, it is suggested to set both the MREG and PREG attributes to 1 when performing multiply functions.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-22default:default2*
MREG Output pipelining2default:default2?
?DSP alu/aluRes0__0 multiplier stage alu/aluRes0__0/P[47:0] is not pipelined (MREG=0). Pipelining the multiplier function will improve performance and will save significant power so it is suggested whenever possible to fully pipeline this function.  If this multiplier was inferred, it is suggested to describe an additional register stage after this function.  If there is no registered adder/accumulator following the multiply function, two pipeline stages are suggested to allow both the MREG and PREG registers to be used.  If the DSP48 was instantiated in the design, it is suggested to set both the MREG and PREG attributes to 1 when performing multiply functions.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-22default:default2*
MREG Output pipelining2default:default2?
?DSP alu/aluRes0__1 multiplier stage alu/aluRes0__1/P[47:0] is not pipelined (MREG=0). Pipelining the multiplier function will improve performance and will save significant power so it is suggested whenever possible to fully pipeline this function.  If this multiplier was inferred, it is suggested to describe an additional register stage after this function.  If there is no registered adder/accumulator following the multiply function, two pipeline stages are suggested to allow both the MREG and PREG registers to be used.  If the DSP48 was instantiated in the design, it is suggested to set both the MREG and PREG attributes to 1 when performing multiply functions.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
DPOP-22default:default2*
MREG Output pipelining2default:default2?
?DSP alu/aluRes0__2 multiplier stage alu/aluRes0__2/P[47:0] is not pipelined (MREG=0). Pipelining the multiplier function will improve performance and will save significant power so it is suggested whenever possible to fully pipeline this function.  If this multiplier was inferred, it is suggested to describe an additional register stage after this function.  If there is no registered adder/accumulator following the multiply function, two pipeline stages are suggested to allow both the MREG and PREG registers to be used.  If the DSP48 was instantiated in the design, it is suggested to set both the MREG and PREG attributes to 1 when performing multiply functions.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
PDRC-1532default:default2%
Gated clock check2default:default2?
?Net imem/hi_reg[31]_60 is a gated clock net sourced by a combinational pin imem/flag_reg[1]_i_2/O, cell imem/flag_reg[1]_i_2. This is not good design practice and will likely impact performance. For SLICE registers, for example, use the CE pin to control the loading of data.2default:defaultZ23-20h px? 
?
Rule violation (%s) %s - %s
20*drc2
PDRC-1532default:default2%
Gated clock check2default:default2?
?Net imem/pc_reg[1] is a gated clock net sourced by a combinational pin imem/zero_reg_i_2/O, cell imem/zero_reg_i_2. This is not good design practice and will likely impact performance. For SLICE registers, for example, use the CE pin to control the loading of data.2default:defaultZ23-20h px? 
g
DRC finished with %s
1905*	planAhead2)
0 Errors, 19 Warnings2default:defaultZ12-3199h px? 
i
BPlease refer to the DRC report (report_drc) for more information.
1906*	planAheadZ12-3200h px? 
?
Loading data files...
1271*designutilsZ12-1165h px? 
>
Loading site data...
1273*designutilsZ12-1167h px? 
?
Loading route data...
1272*designutilsZ12-1166h px? 
?
Processing options...
1362*designutilsZ12-1514h px? 
<
Creating bitmap...
1249*designutilsZ12-1141h px? 
7
Creating bitstream...
7*	bitstreamZ40-7h px? 
Z
Writing bitstream %s...
11*	bitstream2
	./top.bit2default:defaultZ40-11h px? 
F
Bitgen Completed Successfully.
1606*	planAheadZ12-1842h px? 
Z
Releasing license: %s
83*common2"
Implementation2default:defaultZ17-83h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2%
write_bitstream: 2default:default2
00:00:222default:default2
00:00:212default:default2
1521.1252default:default2
350.4842default:defaultZ17-268h px? 
`
Unable to parse hwdef file %s162*	vivadotcl2
	top.hwdef2default:defaultZ4-395h px? 


End Record