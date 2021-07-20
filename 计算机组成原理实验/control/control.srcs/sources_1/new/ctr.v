`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/20 14:46:15
// Design Name: 
// Module Name: ctr
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


module ctr(
    input [5:0] opCode,
    output reg regDst, output reg aluSrc, output reg memToReg, output reg regWrite, output reg memRead, output reg memWrite, output reg branch,
    output reg ExtOp, //符号扩展方式，1 为 sign-extend，0 为 zero-extend
    output reg[3:0] aluop, // 经过 ALU 控制译码决定 ALU 功能
    output reg jmp
);

always@(opCode) begin
// 操作码改变时改变控制信号
case(opCode)
    6'b000010: begin
    regDst = 0;  aluSrc = 0; memToReg = 0; shift = 0; jal = 0;
    regWrite = 0; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0000; jmp = 1; ExtOp = 1;
    end // 'j' 指令操作码: 000010，无需 ALU
    
    6'b000011: begin
    regDst = 0;  aluSrc = 0; memToReg = 0; shift = 0; jal = 1;
    regWrite = 0; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0000; jmp = 1; ExtOp = 1;
    end // 'jal' 指令操作码: 000011，无需 ALU
    
    6'b000000: begin
    regDst = 1;  aluSrc = 0; memToReg = 0; shift = 0; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b1111; jmp = 0; ExtOp = 1;
    end // 'R 型' 指令操作码: 000000
    
    //'I'型指令操作码
    6'b100011: begin
    regDst = 0;  aluSrc = 1; memToReg = 1; shift = 0; jal = 0;
    regWrite = 1; memRead = 1; memWrite = 0; branch = 0; aluop = 4'b0000; jmp = 0; ExtOp = 1;
    end // 'lw' 指令操作码: 100011
    
    6'b101011: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 0; jal = 0;
    regWrite = 0; memRead = 0; memWrite = 1; branch = 0; aluop = 4'b0000; jmp = 0; ExtOp = 1;
    end // 'sw' 指令操作码: 101011
    
    6'b000100: begin
    regDst = 0;  aluSrc = 0; memToReg = 0; shift = 0; jal = 0;
    regWrite = 0; memRead = 0; memWrite = 0; branch = 1; aluop = 4'b0001; jmp = 0; ExtOp = 1;
    end // 'beq' 指令操作码: 000100
    
    6'b000101: begin
    regDst = 0;  aluSrc = 0; memToReg = 0; shift = 0; jal = 0;
    regWrite = 0; memRead = 0; memWrite = 0; branch = 1; aluop = 4'b0110; jmp = 0; ExtOp = 1;
    end // 'bne' 指令操作码: 000101
    
    6'b001000: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 0; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0000; jmp = 0; ExtOp = 1;
    end // 'addi' 指令操作码: 001000
    
    6'b001100: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 0; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0100; jmp = 0; ExtOp = 0;
    end // 'andi' 指令操作码: 001100
    
    6'b001101: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 0; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0010; jmp = 0; ExtOp = 0;
    end // 'ori' 指令操作码: 001101
    
    6'b001110: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 0; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b1100; jmp = 0; ExtOp = 0;
    end // 'xori' 指令操作码: 001110
     
    6'b001010: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 0; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0011; jmp = 0; ExtOp = 1;
    end // 'slti' 指令操作码: 001010
    
    6'b001111: begin
    regDst = 0;  aluSrc = 1; memToReg = 0; shift = 1; jal = 0;
    regWrite = 1; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b1011; jmp = 0; ExtOp = 1;
    end // 'lui' 指令操作码: 001111

    default: begin
    regDst = 0;  aluSrc = 0; memToReg = 0; shift = 0; jal = 0;
    regWrite = 0; memRead = 0; memWrite = 0; branch = 0; aluop = 4'b0000; jmp = 0; ExtOp = 0;
    end // 默认设置
endcase end
endmodule
