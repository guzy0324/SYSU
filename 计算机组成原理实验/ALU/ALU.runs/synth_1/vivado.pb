
p
Command: %s
53*	vivadotcl2?
+synth_design -top top -part xc7a35tcpg236-12default:defaultZ4-113h px? 
:
Starting synth_design
149*	vivadotclZ4-321h px? 
?
@Attempting to get a license for feature '%s' and/or device '%s'
308*common2
	Synthesis2default:default2
xc7a35t2default:defaultZ17-347h px? 
?
0Got license for feature '%s' and/or device '%s'
310*common2
	Synthesis2default:default2
xc7a35t2default:defaultZ17-349h px? 
?
?The version limit for your license is '%s' and will expire in %s days. A version limit expiration means that, although you may be able to continue to use the current version of tools or IP with this license, you will not be eligible for any updates or new releases.
519*common2
2019.062default:default2
-1362default:defaultZ17-1223h px? 
?
%s*synth2?
xStarting RTL Elaboration : Time (s): cpu = 00:00:13 ; elapsed = 00:00:19 . Memory (MB): peak = 289.160 ; gain = 117.258
2default:defaulth px? 
?
synthesizing module '%s'638*oasys2
top2default:default2E
/C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/top.v2default:default2
242default:default8@Z8-638h px? 
?
synthesizing module '%s'638*oasys2
alu2default:default2E
/C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/alu.v2default:default2
232default:default8@Z8-638h px? 
?
%done synthesizing module '%s' (%s#%s)256*oasys2
alu2default:default2
12default:default2
12default:default2E
/C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/alu.v2default:default2
232default:default8@Z8-256h px? 
?
synthesizing module '%s'638*oasys2
display2default:default2I
3C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/display.v2default:default2
272default:default8@Z8-638h px? 
?
default block is never used226*oasys2I
3C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/display.v2default:default2
692default:default8@Z8-226h px? 
?
%done synthesizing module '%s' (%s#%s)256*oasys2
display2default:default2
22default:default2
12default:default2I
3C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/display.v2default:default2
272default:default8@Z8-256h px? 
?
%done synthesizing module '%s' (%s#%s)256*oasys2
top2default:default2
32default:default2
12default:default2E
/C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/top.v2default:default2
242default:default8@Z8-256h px? 
w
!design %s has unconnected port %s3331*oasys2
top2default:default2
reset2default:defaultZ8-3331h px? 
?
%s*synth2?
xFinished RTL Elaboration : Time (s): cpu = 00:00:15 ; elapsed = 00:00:21 . Memory (MB): peak = 326.531 ; gain = 154.629
2default:defaulth px? 
D
%s*synth2,

Report Check Netlist: 
2default:defaulth px? 
u
%s*synth2]
I+------+------------------+-------+---------+-------+------------------+
2default:defaulth px? 
u
%s*synth2]
I|      |Item              |Errors |Warnings |Status |Description       |
2default:defaulth px? 
u
%s*synth2]
I+------+------------------+-------+---------+-------+------------------+
2default:defaulth px? 
u
%s*synth2]
I|1     |multi_driven_nets |      0|        0|Passed |Multi driven nets |
2default:defaulth px? 
u
%s*synth2]
I+------+------------------+-------+---------+-------+------------------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished RTL Optimization Phase 1 : Time (s): cpu = 00:00:15 ; elapsed = 00:00:21 . Memory (MB): peak = 326.531 ; gain = 154.629
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
V
Loading part %s157*device2#
xc7a35tcpg236-12default:defaultZ21-403h px? 
K
)Preparing netlist for logic optimization
349*projectZ1-570h px? 
>

Processing XDC Constraints
244*projectZ1-262h px? 
=
Initializing timing engine
348*projectZ1-569h px? 
?
Parsing XDC File [%s]
179*designutils2F
2C:/Users/guzy0/ALU/ALU.srcs/constrs_1/new/cons.xdc2default:defaultZ20-179h px? 
?
Finished Parsing XDC File [%s]
178*designutils2F
2C:/Users/guzy0/ALU/ALU.srcs/constrs_1/new/cons.xdc2default:defaultZ20-178h px? 
?
?Implementation specific constraints were found while reading constraint file [%s]. These constraints will be ignored for synthesis but will be used in implementation. Impacted constraints are listed in the file [%s].
233*project2F
2C:/Users/guzy0/ALU/ALU.srcs/constrs_1/new/cons.xdc2default:default2)
.Xil/top_propImpl.xdc2default:defaultZ1-236h px? 
H
&Completed Processing XDC Constraints

245*projectZ1-263h px? 
~
!Unisim Transformation Summary:
%s111*project29
%No Unisim elements were transformed.
2default:defaultZ1-111h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common24
 Constraint Validation Runtime : 2default:default2
00:00:002default:default2 
00:00:00.0132default:default2
597.6022default:default2
0.0002default:defaultZ17-268h px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
~Finished Constraint Validation : Time (s): cpu = 00:00:32 ; elapsed = 00:00:39 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
V
%s*synth2>
*Start Loading Part and Timing Information
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
J
%s*synth22
Loading part: xc7a35tcpg236-1
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Loading Part and Timing Information : Time (s): cpu = 00:00:32 ; elapsed = 00:00:39 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
Z
%s*synth2B
.Start Applying 'set_property' XDC Constraints
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished applying 'set_property' XDC Constraints : Time (s): cpu = 00:00:32 ; elapsed = 00:00:39 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
t
8ROM "%s" won't be mapped to RAM because it is too sparse3998*oasys2
zero2default:defaultZ8-5546h px? 
?
[ROM "%s" won't be mapped to Block RAM because address size (%s) smaller than threshold (%s)3996*oasys2
zero2default:default2
42default:default2
52default:defaultZ8-5544h px? 
?
^ROM "%s" won't be mapped to RAM because address size (%s) is larger than maximum supported(%s)3997*oasys2
clk_cnt2default:default2
322default:default2
252default:defaultZ8-5545h px? 
?
^ROM "%s" won't be mapped to RAM because address size (%s) is larger than maximum supported(%s)3997*oasys2
	clk_400Hz2default:default2
322default:default2
252default:defaultZ8-5545h px? 
?
!inferring latch for variable '%s'327*oasys2
zero_reg2default:default2E
/C:/Users/guzy0/ALU/ALU.srcs/sources_1/new/alu.v2default:default2
382default:default8@Z8-327h px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished RTL Optimization Phase 2 : Time (s): cpu = 00:00:33 ; elapsed = 00:00:40 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
E
%s*synth2-

Report RTL Partitions: 
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
+| |RTL Partition |Replication |Instances |
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
L
%s*synth24
 Start RTL Component Statistics 
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
K
%s*synth23
Detailed RTL Component Info : 
2default:defaulth px? 
:
%s*synth2"
+---Adders : 
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input     32 Bit       Adders := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   3 Input     16 Bit       Adders := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input     16 Bit       Adders := 1     
2default:defaulth px? 
8
%s*synth2 
+---XORs : 
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input     16 Bit         XORs := 1     
2default:defaulth px? 
=
%s*synth2%
+---Registers : 
2default:defaulth px? 
Z
%s*synth2B
.	               32 Bit    Registers := 1     
2default:defaulth px? 
Z
%s*synth2B
.	                4 Bit    Registers := 1     
2default:defaulth px? 
Z
%s*synth2B
.	                1 Bit    Registers := 1     
2default:defaulth px? 
9
%s*synth2!
+---Muxes : 
2default:defaulth px? 
Z
%s*synth2B
.	   7 Input     16 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	  16 Input      7 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   5 Input      4 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   7 Input      3 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input      1 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   7 Input      1 Bit        Muxes := 1     
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
O
%s*synth27
#Finished RTL Component Statistics 
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
Y
%s*synth2A
-Start RTL Hierarchical Component Statistics 
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
O
%s*synth27
#Hierarchical RTL Component report 
2default:defaulth px? 
8
%s*synth2 
Module alu 
2default:defaulth px? 
K
%s*synth23
Detailed RTL Component Info : 
2default:defaulth px? 
:
%s*synth2"
+---Adders : 
2default:defaulth px? 
Z
%s*synth2B
.	   3 Input     16 Bit       Adders := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input     16 Bit       Adders := 1     
2default:defaulth px? 
8
%s*synth2 
+---XORs : 
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input     16 Bit         XORs := 1     
2default:defaulth px? 
9
%s*synth2!
+---Muxes : 
2default:defaulth px? 
Z
%s*synth2B
.	   7 Input     16 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   7 Input      3 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input      1 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   7 Input      1 Bit        Muxes := 1     
2default:defaulth px? 
<
%s*synth2$
Module display 
2default:defaulth px? 
K
%s*synth23
Detailed RTL Component Info : 
2default:defaulth px? 
:
%s*synth2"
+---Adders : 
2default:defaulth px? 
Z
%s*synth2B
.	   2 Input     32 Bit       Adders := 1     
2default:defaulth px? 
=
%s*synth2%
+---Registers : 
2default:defaulth px? 
Z
%s*synth2B
.	               32 Bit    Registers := 1     
2default:defaulth px? 
Z
%s*synth2B
.	                4 Bit    Registers := 1     
2default:defaulth px? 
Z
%s*synth2B
.	                1 Bit    Registers := 1     
2default:defaulth px? 
9
%s*synth2!
+---Muxes : 
2default:defaulth px? 
Z
%s*synth2B
.	  16 Input      7 Bit        Muxes := 1     
2default:defaulth px? 
Z
%s*synth2B
.	   5 Input      4 Bit        Muxes := 1     
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
[
%s*synth2C
/Finished RTL Hierarchical Component Statistics
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
H
%s*synth20
Start Part Resource Summary
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2j
VPart Resources:
DSPs: 90 (col length:60)
BRAMs: 100 (col length: RAMB18 60 RAMB36 30)
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
K
%s*synth23
Finished Part Resource Summary
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Start Parallel Synthesis Optimization  : Time (s): cpu = 00:00:34 ; elapsed = 00:00:41 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
N
%s*synth26
"Start Cross Boundary Optimization
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
x
8ROM "%s" won't be mapped to RAM because it is too sparse3998*oasys2
alu/zero2default:defaultZ8-5546h px? 
?
^ROM "%s" won't be mapped to RAM because address size (%s) is larger than maximum supported(%s)3997*oasys2!
disp1/clk_cnt2default:default2
322default:default2
252default:defaultZ8-5545h px? 
?
^ROM "%s" won't be mapped to RAM because address size (%s) is larger than maximum supported(%s)3997*oasys2#
disp1/clk_400Hz2default:default2
322default:default2
252default:defaultZ8-5545h px? 
w
!design %s has unconnected port %s3331*oasys2
top2default:default2
reset2default:defaultZ8-3331h px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Cross Boundary Optimization : Time (s): cpu = 00:00:35 ; elapsed = 00:00:42 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
~Finished Parallel Reinference  : Time (s): cpu = 00:00:35 ; elapsed = 00:00:42 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
E
%s*synth2-

Report RTL Partitions: 
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
+| |RTL Partition |Replication |Instances |
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
D
%s*synth2,
Start Area Optimization
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
ESequential element (%s) is unused and will be removed from module %s.3332*oasys2"
\alu/zero_reg 2default:default2
top2default:defaultZ8-3332h px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
zFinished Area Optimization : Time (s): cpu = 00:00:36 ; elapsed = 00:00:43 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Parallel Area Optimization  : Time (s): cpu = 00:00:36 ; elapsed = 00:00:43 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
E
%s*synth2-

Report RTL Partitions: 
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
+| |RTL Partition |Replication |Instances |
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
F
%s*synth2.
Start Timing Optimization
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
R
%s*synth2:
&Start Applying XDC Timing Constraints
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Applying XDC Timing Constraints : Time (s): cpu = 00:01:01 ; elapsed = 00:01:09 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
|Finished Timing Optimization : Time (s): cpu = 00:01:01 ; elapsed = 00:01:09 . Memory (MB): peak = 597.602 ; gain = 425.699
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
E
%s*synth2-

Report RTL Partitions: 
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
+| |RTL Partition |Replication |Instances |
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
E
%s*synth2-
Start Technology Mapping
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
{Finished Technology Mapping : Time (s): cpu = 00:01:01 ; elapsed = 00:01:09 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Parallel Technology Mapping Optimization  : Time (s): cpu = 00:01:01 ; elapsed = 00:01:09 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
E
%s*synth2-

Report RTL Partitions: 
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
+| |RTL Partition |Replication |Instances |
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
?
%s*synth2?
?Finished Parallel Synthesis Optimization  : Time (s): cpu = 00:01:01 ; elapsed = 00:01:09 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2'
Start IO Insertion
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
Q
%s*synth29
%Start Flattening Before IO Insertion
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
T
%s*synth2<
(Finished Flattening Before IO Insertion
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
H
%s*synth20
Start Final Netlist Cleanup
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
K
%s*synth23
Finished Final Netlist Cleanup
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
uFinished IO Insertion : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
D
%s*synth2,

Report Check Netlist: 
2default:defaulth px? 
u
%s*synth2]
I+------+------------------+-------+---------+-------+------------------+
2default:defaulth px? 
u
%s*synth2]
I|      |Item              |Errors |Warnings |Status |Description       |
2default:defaulth px? 
u
%s*synth2]
I+------+------------------+-------+---------+-------+------------------+
2default:defaulth px? 
u
%s*synth2]
I|1     |multi_driven_nets |      0|        0|Passed |Multi driven nets |
2default:defaulth px? 
u
%s*synth2]
I+------+------------------+-------+---------+-------+------------------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
O
%s*synth27
#Start Renaming Generated Instances
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Renaming Generated Instances : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
E
%s*synth2-

Report RTL Partitions: 
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
+| |RTL Partition |Replication |Instances |
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
W
%s*synth2?
++-+--------------+------------+----------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
L
%s*synth24
 Start Rebuilding User Hierarchy
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Rebuilding User Hierarchy : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
K
%s*synth23
Start Renaming Generated Ports
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Renaming Generated Ports : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
M
%s*synth25
!Start Handling Custom Attributes
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Handling Custom Attributes : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
J
%s*synth22
Start Renaming Generated Nets
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Renaming Generated Nets : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
K
%s*synth23
Start Writing Synthesis Report
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
A
%s*synth2)

Report BlackBoxes: 
2default:defaulth px? 
J
%s*synth22
+-+--------------+----------+
2default:defaulth px? 
J
%s*synth22
| |BlackBox name |Instances |
2default:defaulth px? 
J
%s*synth22
+-+--------------+----------+
2default:defaulth px? 
J
%s*synth22
+-+--------------+----------+
2default:defaulth px? 
A
%s*synth2)

Report Cell Usage: 
2default:defaulth px? 
D
%s*synth2,
+------+-------+------+
2default:defaulth px? 
D
%s*synth2,
|      |Cell   |Count |
2default:defaulth px? 
D
%s*synth2,
+------+-------+------+
2default:defaulth px? 
D
%s*synth2,
|1     |BUFG   |     1|
2default:defaulth px? 
D
%s*synth2,
|2     |CARRY4 |    12|
2default:defaulth px? 
D
%s*synth2,
|3     |LUT1   |    46|
2default:defaulth px? 
D
%s*synth2,
|4     |LUT2   |     4|
2default:defaulth px? 
D
%s*synth2,
|5     |LUT3   |     2|
2default:defaulth px? 
D
%s*synth2,
|6     |LUT4   |    11|
2default:defaulth px? 
D
%s*synth2,
|7     |LUT5   |    14|
2default:defaulth px? 
D
%s*synth2,
|8     |LUT6   |    26|
2default:defaulth px? 
D
%s*synth2,
|9     |FDRE   |    37|
2default:defaulth px? 
D
%s*synth2,
|10    |IBUF   |    14|
2default:defaulth px? 
D
%s*synth2,
|11    |OBUF   |    11|
2default:defaulth px? 
D
%s*synth2,
+------+-------+------+
2default:defaulth px? 
E
%s*synth2-

Report Instance Areas: 
2default:defaulth px? 
O
%s*synth27
#+------+---------+--------+------+
2default:defaulth px? 
O
%s*synth27
#|      |Instance |Module  |Cells |
2default:defaulth px? 
O
%s*synth27
#+------+---------+--------+------+
2default:defaulth px? 
O
%s*synth27
#|1     |top      |        |   178|
2default:defaulth px? 
O
%s*synth27
#|2     |  alu    |alu     |    35|
2default:defaulth px? 
O
%s*synth27
#|3     |  disp1  |display |   101|
2default:defaulth px? 
O
%s*synth27
#+------+---------+--------+------+
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
?
%s*synth2?
?Finished Writing Synthesis Report : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
~
%s*synth2f
R---------------------------------------------------------------------------------
2default:defaulth px? 
r
%s*synth2Z
FSynthesis finished with 0 errors, 0 critical warnings and 3 warnings.
2default:defaulth px? 
?
%s*synth2?
~Synthesis Optimization Runtime : Time (s): cpu = 00:00:38 ; elapsed = 00:00:50 . Memory (MB): peak = 602.480 ; gain = 116.297
2default:defaulth px? 
?
%s*synth2?
Synthesis Optimization Complete : Time (s): cpu = 00:01:02 ; elapsed = 00:01:10 . Memory (MB): peak = 602.480 ; gain = 430.578
2default:defaulth px? 
B
 Translating synthesized netlist
350*projectZ1-571h px? 
f
-Analyzing %s Unisim elements for replacement
17*netlist2
262default:defaultZ29-17h px? 
j
2Unisim Transformation completed in %s CPU seconds
28*netlist2
02default:defaultZ29-28h px? 
K
)Preparing netlist for logic optimization
349*projectZ1-570h px? 
u
)Pushed %s inverter(s) to %s load pin(s).
98*opt2
02default:default2
02default:defaultZ31-138h px? 
~
!Unisim Transformation Summary:
%s111*project29
%No Unisim elements were transformed.
2default:defaultZ1-111h px? 
U
Releasing license: %s
83*common2
	Synthesis2default:defaultZ17-83h px? 
?
G%s Infos, %s Warnings, %s Critical Warnings and %s Errors encountered.
28*	vivadotcl2
272default:default2
42default:default2
02default:default2
02default:defaultZ4-41h px? 
^
%s completed successfully
29*	vivadotcl2 
synth_design2default:defaultZ4-42h px? 
?
I%sTime (s): cpu = %s ; elapsed = %s . Memory (MB): peak = %s ; gain = %s
268*common2"
synth_design: 2default:default2
00:00:592default:default2
00:01:022default:default2
602.4802default:default2
393.7582default:defaultZ17-268h px? 
?
sreport_utilization: Time (s): cpu = 00:00:00 ; elapsed = 00:00:00.046 . Memory (MB): peak = 602.480 ; gain = 0.000
*commonh px? 
?
Exiting %s at %s...
206*common2
Vivado2default:default2,
Wed Nov 13 14:49:42 20192default:defaultZ17-206h px? 


End Record