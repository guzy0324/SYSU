`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/20 15:14:03
// Design Name: 
// Module Name: topsim
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


module topsim; 
// Inputs 
reg clkin; 
reg reset; 
// Instantiate the Unit Under Test (UUT) 
top uut ( 
.clkin(clkin), 
.reset(reset),
.reg_dst(reg_dst), .alu_src(alu_src), .memtoreg(memtoreg), .regwrite(regwrite), .memread(memread), .memwrite(memwrite), .branch(branch), .jmp(jmp),
.aluCtr(aluCtr)
); 
initial begin 
// Initialize Inputs 
clkin = 0; 
reset = 1; 
// Wait 100 ns for global reset to finish 
#100; 
reset = 0; 
end 
parameter PERIOD = 20; 
always begin 
clkin = 1'b0; 
#(PERIOD / 2) clkin = 1'b1; 
#(PERIOD / 2) ; 
end 
endmodule 
