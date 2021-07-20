`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/06 14:56:40
// Design Name: 
// Module Name: alu
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module alu( 
input [15:0] input1, 
input [15:0] input2, 
input [3:0] aluCtr, 
output reg[15:0] aluRes, 
output reg zero 
); 

always @(input1 or input2 or aluCtr) // 运算数或控制码变化时操作
begin 
case(aluCtr) 
4'b0110: // 减
begin 
aluRes = input1 - input2; 
if(aluRes == 0) 
zero = 1; 
else 
zero = 0; 
end 
4'b0010: // 加
aluRes = input1 + input2; 
4'b0000: // 与
aluRes = input1 & input2; 
4'b0001: // 或
aluRes = input1 | input2; 
4'b1100: // 异或
aluRes = input1 ^ input2; 
4'b0111: // 小于设置
begin 
if(input1<input2) 
aluRes = 1;
else
aluRes = 0;
end 
default: 
aluRes = 0; 
endcase 
end 
endmodule 
