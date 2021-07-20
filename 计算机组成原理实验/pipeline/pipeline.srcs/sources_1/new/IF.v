`timescale 1ns / 1ps
module IF(clk,reset,branch_or_pc,
branch_addr,next_pc_if,inst_if,
pc
);
input clk;
input reset;
input branch_or_pc;//Branch&ALU_zero
input[31:0]  branch_addr;//Branch跳转地址
output[31:0]  next_pc_if;//pc+4
output[31:0]  inst_if;//从ROM中读的指令
output[31:0]  pc;
 
//PC的多选器
reg[31:0]  pc_in;//pc选择
always@(*)
begin
    case(branch_or_pc)
    1'b0:pc_in<=next_pc_if;//没有分支也没有jump
    1'b1:pc_in<=branch_addr;//有Branch
endcase
end


//PC寄存器
reg[31:0] pc;
always@(posedge clk)
begin
    if(reset) pc<=32'b0;//复位
    else pc<=pc_in;
end
 
//计算下一个PC的加法器
adder_if adder32_bits_if(
.a(pc),
.b(32'b00000000000000000000000000000100),
.c(next_pc_if)
);
 
//指令ROM
//InstructionROM InstructionROM(.a(pc[11:2]),.spo(inst_if));
InstructionROM InstructionROM(.a(pc[9:2]),.spo(inst_if));

endmodule
