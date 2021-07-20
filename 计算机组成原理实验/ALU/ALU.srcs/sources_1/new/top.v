`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/06 15:21:51
// Design Name: 
// Module Name: top
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


module top( 
input clk, 
input reset, //复位信号（连接一个按键）
input [3:0] aluCtr,
//input [15:0] input1,
//input [15:0] input2,
input [8:0] input3,
output [6:0] seg,//段码
output [3:0] sm_wei//哪个数码管
);
// ALU信号线
wire zero; 
wire[15:0] aluRes; 
//wire[15:0] expand;
// ALU控制信号线
wire [15:0] input1;
wire [15:0] input2;
// 实例化ALU模块
assign input1 = 16'h0x7;
assign input2[15:9] = {7{input3[8]}};
assign input2[8:0] = input3[8:0];
alu alu(.input1(input1), 
.input2(input2), 
.aluCtr(aluCtr), 
.zero(zero), 
.aluRes(aluRes)); 
// 。。。。。。。。。。。。。。。。。。。。。。。。。。实例化符号扩展模块
//signext signext(.inst(inst[15:0]), .data(expand));

//...............................实例化数码管显示模块
display disp1 (.clk(clk),.sm_wei(sm_wei),.data(aluRes[15:0]),.sm_duan(seg));
endmodule
