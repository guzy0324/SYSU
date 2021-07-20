`timescale 1ns / 1ps
//module alu(
module ALU(
    input [31:0] input1, 
    input [31:0] input2,
    //input [3:0] aluCtr, 
    input [2:0] aluCtr, 
    output reg[31:0] aluRes, 
    output reg zero
    //output reg zero, 
    //output reg negtive, 
    //output reg[31:0] hi
); 
always @(input1 or input2 or aluCtr) // 运算数或控制码变化时操作
begin 
    case(aluCtr) 
        //4'b0110: // 减
        3'b110:
        begin 
        aluRes = input1 - input2; 
        if(aluRes == 0) 
            zero = 1; 
        else 
            zero = 0; 
        /*if(aluRes[31] == 1) 
            negtive = 1; 
        else 
            negtive = 0;*/ 
        end 
        
        //4'b0010: // 加
        3'b010:
        aluRes = input1 + input2; 
        
        //4'b0000: // 与
        3'b000:
        aluRes = input1 & input2; 
        
        //4'b0001: // 或
        3'b001:
        aluRes = input1 | input2; 
        
        //4'b0100: // 异或
        3'b100:
        aluRes = input1 ^ input2; 
        
        //4'b0111: // 小于设置
        3'b111:
        begin 
        if((input1 < input2 && ~(input1[31]^input2[31])) || (input1[31] & ~input2[31])) 
            aluRes = 1; 
        else
            aluRes = 0;
        end 
        
        //4'b0101: //nor
        3'b101:
        aluRes = ~(input1 | input2);
/*
        4'b1000: //sll, sllv
        aluRes = input1 << input2;
        
        4'b1001: //srl, srlv
        aluRes = input1 >> input2;
        
        4'b1010: //sra, srav
        aluRes = $signed(input1) >>> input2;

        4'b1011: // multu
        {hi, aluRes} = input1 * input2;
        
        4'b1100: // divu
        begin
        aluRes = input1 / input2;
        hi = input1 % input2;
        end*/

        default: 
        aluRes = 0; 
    endcase 
end 
endmodule 