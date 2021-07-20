`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/06 15:04:49
// Design Name: 
// Module Name: alusim
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


module alusim; 
// Inputs 
reg [15:0] input1; 
reg [15:0] input2; 
reg [3:0] aluCtr; 
// Outputs 
wire [31:0] aluRes;
wire [31:0] data1;
wire [31:0] data2; 
wire zero; 
// Instantiate the Unit Under Test (UUT) 
signext uut1 (
.inst(input1),
.data(data1)
);

signext uut2 (
.inst(input2),
.data(data2)
);

alu uut3 ( 
.input1(data1), 
.input2(data2), 
.aluCtr(aluCtr), 
.aluRes(aluRes), 
.zero(zero) 
); 
initial begin 
// Initialize Inputs 
input1 = 1; 
input2 = 1; 
aluCtr = 4'b0110; 
#100; 
input1 = 16'hfffe; 
input2 = 1; 
aluCtr = 4'b0110; 
#100 
input1 = 1; 
input2 = 1; 
aluCtr = 4'b0010; 
#100 
input1 = 1; 
input2 = 0; 
aluCtr = 4'b0000; 
#100 
input1 = 1; 
input2 = 0; 
aluCtr = 4'b0001; 
#100 
input1 = 1; 
input2 = 0; 
aluCtr = 4'b0111; 
#100 
input1 = 0; 
input2 = 1; 
aluCtr = 4'b0111; 
end 
endmodule 
