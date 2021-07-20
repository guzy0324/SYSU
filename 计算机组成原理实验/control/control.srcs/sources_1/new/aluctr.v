`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/20 14:51:00
// Design Name: 
// Module Name: aluctr
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

module aluctr(
    input [1:0] ALUOp, input [5:0] funct, output reg [3:0]  ALUCtr
);

always @(ALUOp or funct) //  如果操作码或者功能码变化执行操作
    casex({ALUOp, funct}) // 拼接操作码和功能码便于下一步的判断
        8'b00xxxxxx: ALUCtr = 4'b0010; // lw，sw，addi 
        8'b01xxxxxx: ALUCtr = 4'b0110; // beq 
        8'b1xxx0000: ALUCtr = 4'b0010; // add 
        8'b1xxx0010: ALUCtr = 4'b0110; // sub 
        8'b1xxx0100: ALUCtr = 4'b0000; // and 
        8'b1xxx0101: ALUCtr = 4'b0001; // or 
        8'b1xxx1010: ALUCtr = 4'b0111; // slt
        
    endcase
endmodule
