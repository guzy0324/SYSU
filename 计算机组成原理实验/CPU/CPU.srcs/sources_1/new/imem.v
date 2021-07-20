`timescale 1ns / 1ps
module imem (
    input clkin,
    input [7:0] pc,
    output [31:0] inst
);  
irom imem1(
    .clka(clkin),    // input wire clka
    .addra(pc + 2'b00),  // input wire [7 : 0] addra
    .douta(inst[31:24])  // output wire [7 : 0] douta
); 
irom imem2(
    .clka(clkin),    // input wire clka
    .addra(pc+2'b01),  // input wire [7 : 0] addra
    .douta(inst[23:16])  // output wire [7 : 0] douta
); 
irom imem3(
    .clka(clkin),    // input wire clka
    .addra(pc+2'b10),  // input wire [7 : 0] addra
    .douta(inst[15:8])  // output wire [7 : 0] douta
); 
irom imem4(
    .clka(clkin),    // input wire clka
    .addra(pc+2'b11),  // input wire [7 : 0] addra
    .douta(inst[7:0])  // output wire [7 : 0] douta
); 
endmodule
/*
24 01 00 08
34 02 00 02
00 41 18 20
00 62 28 22
00 a2 20 24
00 82 40 25
00 08 40 40
15 01 ff fe
28 46 00 04
28 c7 00 00
24 e7 00 08
10 e1 ff fe
ac 22 00 04
8c 29 00 04
24 0a ff fe
25 4a 00 01
05 40 ff fe
30 4b 00 02
3c 0c ff ff
00 0c 60 43
00 0c 60 42
00 cc 60 04
00 cc 60 07
00 cc 60 06
01 ef 78 26
39 ad 00 01
1d a0 ff fe
01 ae 68 27
01 ae 68 26
01 ae 70 2a
a4 2c 00 02
84 2c 00 02
a0 2c 00 01
80 2c 00 01
0c 00 00 24
08 00 00 2b
01 a9 00 19
00 00 78 10
00 00 80 12
01 a9 00 1b
00 00 88 10
00 00 90 12
03 e0 00 08
fc 00 00 00
*/