`timescale 1ns / 1ps
module EX(clk,next_pc_ex,
ALUCode_ex,ALUSrcB_ex,
RegDst_ex,
Imm_ex,RsData_ex,RtData_ex,
RtAddr_ex,RdAddr_ex,
//���
Branch_addr_ex,
alu_zero_ex,alu_res_ex,RegWriteAddr_ex
);
input clk;
input[31:0] next_pc_ex;
input[2:0] ALUCode_ex;
input ALUSrcB_ex;
input RegDst_ex;
input[31:0] Imm_ex;
input[31:0] RsData_ex;
input[31:0] RtData_ex;
input[4:0] RtAddr_ex;
input[4:0] RdAddr_ex;
//
output[31:0] Branch_addr_ex;
output alu_zero_ex;
output[31:0] alu_res_ex;
output reg[4:0] RegWriteAddr_ex;
 
//��֧��ַ
adder_32bits adder_32bits_ex(.a(next_pc_ex),.b(Imm_ex<<2),.c(Branch_addr_ex));
 
//ALUSrcB�Ķ�ѡ��
reg[31:0] alu_in;
always@(*)begin
case(ALUSrcB_ex)
1'b0:alu_in<=RtData_ex;//���ԼĴ����ѵڶ������
1'b1:alu_in<=Imm_ex;//���Է�����չ
endcase
end
 
//ALU
/*
ALU ALU(.ALU_operation(ALUCode_ex),.A(RsData_ex),.B(alu_in),
.res(alu_res_ex),.zero(alu_zero_ex),.overflow()//overflowʲôҲ����
);*/
ALU ALU(.aluCtr({ALUCode_ex}),.input1(RsData_ex),.input2(alu_in),
.aluRes(alu_res_ex),.zero(alu_zero_ex)
);
 
//д�Ĵ����ѵ�ַ�Ķ�ѡ��
always@(*)begin
case(RegDst_ex)
1'b0:RegWriteAddr_ex<=RtAddr_ex;//rt
1'b1:RegWriteAddr_ex<=RdAddr_ex;//rd
endcase
end
 
endmodule