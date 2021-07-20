`timescale 1ns / 1ps
module MUX32_2_1(
    input [31:0] A,
    input [31:0] B,
    input        Sel,
    output[31:0] O
);
assign O = Sel? B : A;
endmodule