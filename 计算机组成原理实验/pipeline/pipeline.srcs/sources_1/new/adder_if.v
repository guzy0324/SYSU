`timescale 1ns / 1ps
module adder_if(a,b,c);
input [31:0] a,b;//偏移量
//output [31:0] PCadd4;//新指令地址
output [31:0] c;
assign c=a+b;
endmodule