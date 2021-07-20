`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/20 15:13:10
// Design Name: 
// Module Name: ctrsim
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


module ctrsim; 
// Inputs 
reg [5:0] opCode; 
// Outputs 
wire regDst; 
wire aluSrc; 
wire memToReg; 
wire regWrite; 
wire memRead; 
wire memWrite; 
wire branch; 
wire [1:0] aluop; 
wire jmp; 
// Instantiate the Unit Under Test (UUT) 
ctr uut ( 
.opCode(opCode), 
.regDst(regDst), 
.aluSrc(aluSrc), 
.memToReg(memToReg), 
.regWrite(regWrite), 
.memRead(memRead), 
.memWrite(memWrite), 
.branch(branch), 
.aluop(aluop), 
.jmp(jmp) 
); 
initial begin 
// Initialize Inputs 
opCode = 6'b000000; 
#100; 
opCode = 6'b000010; 
// Wait 100 ns for global reset to finish 
#100; 
opCode = 6'b110000; 
#100; 
opCode = 6'b100011; 
#100; 
opCode = 6'b000100; 
#100; 
opCode = 6'b001000; 
end 
endmodule 

