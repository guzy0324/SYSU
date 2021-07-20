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
input reset, //��λ�źţ�����һ��������
input [3:0] aluCtr,
//input [15:0] input1,
//input [15:0] input2,
input [8:0] input3,
output [6:0] seg,//����
output [3:0] sm_wei//�ĸ������
);
// ALU�ź���
wire zero; 
wire[15:0] aluRes; 
//wire[15:0] expand;
// ALU�����ź���
wire [15:0] input1;
wire [15:0] input2;
// ʵ����ALUģ��
assign input1 = 16'h0x7;
assign input2[15:9] = {7{input3[8]}};
assign input2[8:0] = input3[8:0];
alu alu(.input1(input1), 
.input2(input2), 
.aluCtr(aluCtr), 
.zero(zero), 
.aluRes(aluRes)); 
// ����������������������������������������������������ʵ����������չģ��
//signext signext(.inst(inst[15:0]), .data(expand));

//...............................ʵ�����������ʾģ��
display disp1 (.clk(clk),.sm_wei(sm_wei),.data(aluRes[15:0]),.sm_duan(seg));
endmodule
