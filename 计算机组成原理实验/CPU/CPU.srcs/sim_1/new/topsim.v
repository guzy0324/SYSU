`timescale 1ns / 1ps
module topsim; 
// Inputs 
reg clkin; 
reg reset; 
wire [31:0] inst, RsData, RtData; 
wire [31:0] pc, next_pc;
wire alu_src_a;
wire [1:0] alu_src_b;
wire [3:0] aluCtr;
wire [2:0] op;
wire [31:0] in1, in2, aluRes, hiData;
wire [31:0] regWriteData, resDis;
wire [31:0] ra, hiReg;
wire [4:0] regWriteAddr;
// Instantiate the Unit Under Test (UUT) 
top uut ( 
    .clkin(clkin), 
    .reset(reset), 
    .pc(pc), 
    .inst(inst), 
    .RsData(RsData), 
    .RtData(RtData), 
    .alu_src_a(alu_src_a), 
    .alu_src_b(alu_src_b), 
    .mux9(regWriteData), 
    .mux8(next_pc),
    .mux6(in1),
    .mux2(in2), 
    .aluop(op), 
    .aluCtr(aluCtr), 
    .aluRes(aluRes), 
    .mux10(regWriteAddr), 
    .resDis(resDis), 
    .ra(ra), 
    .hiReg(hiReg), 
    .hi(hiData) 
); 
initial begin 
// Initialize Inputs 
clkin = 0; 
reset = 1; 
// Wait 100 ns for global reset to finish 
//#100;
#5; 
reset = 0; 
end 
parameter PERIOD = 10; 
always begin 
clkin = 1'b0; 
#(PERIOD / 2) clkin = 1'b1; 
#(PERIOD / 2) ; 
end 
endmodule 