`timescale 1ns / 1ps
module alusim; 
// Inputs 
reg [31:0] input1; 
reg [31:0] input2; 
reg [3:0] aluCtr; 
// Outputs 
wire [31:0] aluRes; 
wire [31:0] hi;
wire zero; 
// Instantiate the Unit Under Test (UUT) 
alu uut ( 
.input1(input1), 
.input2(input2), 
.aluCtr(aluCtr), 
.aluRes(aluRes), 
.hi(hi), 
.zero(zero) 
); 
initial begin 
// Initialize Inputs 
input1 = 1; 
input2 = 1; 
aluCtr = 4'b0110; 
#100; 
input1 = 2; 
input2 = 1; 
aluCtr = 4'b0110; 
#100 
input1 = 32'hffffffff; 
input2 = 32'h00000002; 
aluCtr = 4'b1011;
end
endmodule
