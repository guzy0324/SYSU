`timescale 1ns / 1ps
module MEM(clk,MemRead_mem,
MemWrite_mem,Branch_mem,alu_zero_mem,
alu_res_mem,RtData_mem,
branch_or_pc_mem,Dout_mem
);
input clk;
//MemRead信号暂时不要了
input MemRead_mem;
input MemWrite_mem;
input Branch_mem;
input alu_zero_mem;
input[31:0]alu_res_mem;
input[31:0] RtData_mem;
output branch_or_pc_mem;
output[31:0] Dout_mem;
 
DataRAM DataRAM(
.clka(~clk),//input clka
.wea(~MemRead_mem&MemWrite_mem),//input [0:0] wea
//.addra(alu_res_mem[11:2]),//input [9 : 0] addra
.addra(alu_res_mem[9:2]), 
.dina(RtData_mem),//input [31:0] dina
.douta(Dout_mem)//output [31:0] douta
);
 
//and模块，确定跳转信号
and_1bit and_1bit(.a(Branch_mem),.b(alu_zero_mem),.c(branch_or_pc_mem));
 
endmodule