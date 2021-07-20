`timescale 1ns / 1ps
module MUX32_4_1(
    input [31:0] A,
    input [31:0] B,
    input [31:0] C,
    input [31:0] D,
    input [1:0]  Sel,
    output[31:0] O
);
assign O = (Sel == 2'b00)? A :
            (Sel == 2'b01)? B :
            (Sel == 2'b10)? C : D; 
endmodule
