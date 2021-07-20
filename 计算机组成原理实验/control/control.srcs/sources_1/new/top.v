`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/20 14:54:34
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
    input clkin, input reset,
    output reg_dst, output alu_src, output memtoreg, output regwrite, output memread, output memwrite, output branch, output jmp,
    output aluCtr
);
// ָ��Ĵ���Addr 
wire[31:0] instruction; 
reg[3:0] Addr;
// CPU �����ź���
wire reg_dst, jmp, branch, memread, memwrite, memtoreg; 
wire[1:0] aluop;
wire regwrite;
// ALU �����ź���
wire[3:0] aluCtr;
// �����Ĵ���
regFile regFile ( 
.clk(clkin), .Addr(Addr), .instruction(instruction) );

// ʵ����������ģ��
ctr mainctr(
.opCode(instruction[31:26]),
.regDst(reg_dst),
.aluSrc(alu_src),
.memToReg(memtoreg),
.regWrite(regwrite),
.memRead(memread),
.memWrite(memwrite),
.branch(branch),
.aluop(aluop),
.jmp(jmp));
//  ʵ���� ALU ����ģ��
aluctr aluctr1(
.ALUOp(aluop),
.funct(instruction[5:0]),
.ALUCtr(aluCtr));
endmodule
