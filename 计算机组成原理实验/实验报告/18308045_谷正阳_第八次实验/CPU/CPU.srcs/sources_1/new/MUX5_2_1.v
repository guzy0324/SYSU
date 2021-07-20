`timescale 1ns / 1ps
module MUX5_2_1(
    input [4:0] A,
    input [4:0] B,
    input       Sel,
    output[4:0] O
);
assign O = Sel? B : A; 
endmodule