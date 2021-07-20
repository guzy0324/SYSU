`timescale 1ns / 1ps
module IF(clk,reset,branch_or_pc,
branch_addr,next_pc_if,inst_if,
pc
);
input clk;
input reset;
input branch_or_pc;//Branch&ALU_zero
input[31:0]  branch_addr;//Branch��ת��ַ
output[31:0]  next_pc_if;//pc+4
output[31:0]  inst_if;//��ROM�ж���ָ��
output[31:0]  pc;
 
//PC�Ķ�ѡ��
reg[31:0]  pc_in;//pcѡ��
always@(*)
begin
    case(branch_or_pc)
    1'b0:pc_in<=next_pc_if;//û�з�֧Ҳû��jump
    1'b1:pc_in<=branch_addr;//��Branch
endcase
end


//PC�Ĵ���
reg[31:0] pc;
always@(posedge clk)
begin
    if(reset) pc<=32'b0;//��λ
    else pc<=pc_in;
end
 
//������һ��PC�ļӷ���
adder_if adder32_bits_if(
.a(pc),
.b(32'b00000000000000000000000000000100),
.c(next_pc_if)
);
 
//ָ��ROM
//InstructionROM InstructionROM(.a(pc[11:2]),.spo(inst_if));
InstructionROM InstructionROM(.a(pc[9:2]),.spo(inst_if));

endmodule
