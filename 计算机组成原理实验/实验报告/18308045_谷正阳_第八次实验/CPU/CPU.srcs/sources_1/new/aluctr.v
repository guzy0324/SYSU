`timescale 1ns / 1ps
module aluctr(
    input [2:0] ALUOp,
    input [5:0] funct,
    output reg [3:0] ALUCtr
);
always @(ALUOp or funct)  
    casex({ALUOp, funct}) 
        //·ÇRÐÍ
        9'b000xxxxxx: ALUCtr = 4'b0010; // add
        9'b001xxxxxx: ALUCtr = 4'b0110; // sub
        9'b010xxxxxx: ALUCtr = 4'b0000; // and
        9'b011xxxxxx: ALUCtr = 4'b0001; // or
        9'b100xxxxxx: ALUCtr = 4'b0100; // xor
        9'b101xxxxxx: ALUCtr = 4'b0111; // slt
        
        //RÐÍ
        9'b111_100000: ALUCtr = 4'b0010; // add
        9'b111_100010: ALUCtr = 4'b0110; // sub
        9'b111_100100: ALUCtr = 4'b0000; // and
        9'b111_100111: ALUCtr = 4'b0101; // nor
        9'b111_100101: ALUCtr = 4'b0001; // or
        9'b111_100110: ALUCtr = 4'b0100; // xor
        9'b111_101010: ALUCtr = 4'b0111; // slt
        
        9'b111_000000: ALUCtr = 4'b1000; // sll
        9'b111_000010: ALUCtr = 4'b1001; // srl
        9'b111_000011: ALUCtr = 4'b1010; // sra
        9'b111_000100: ALUCtr = 4'b1000; // sllv
        9'b111_000110: ALUCtr = 4'b1001; // srlv
        9'b111_000111: ALUCtr = 4'b1010; // srav       
        
       /* 9'b111_011000: ALUCtr = 4'b1011; // mult
        9'b111_011010: ALUCtr = 4'b1100; // div*/
        9'b111_011001: ALUCtr = 4'b1011; // multu
        9'b111_011011: ALUCtr = 4'b1100; // divu
        
        default:ALUCtr = 4'b0010;
    endcase
endmodule
