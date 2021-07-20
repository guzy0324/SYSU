`timescale 1ns / 1ps
//级间寄存器
module flipflop(clk,reset,in,out);
parameter WIDTH=1;//根据需要改宽度
input clk;//
input reset;
input [WIDTH-1:0] in;
output [WIDTH-1:0] out;//
reg[WIDTH-1:0] out;
always@(posedge clk)
    if(reset)
        out<={WIDTH{1'b0}};
    else 
        out<=in;
endmodule

