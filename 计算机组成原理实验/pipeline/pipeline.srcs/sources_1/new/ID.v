`timescale 1ns / 1ps
module ID(clk,reset,inst_id,
RegWrite_wb,RegWriteAddr_wb,RegWriteData_wb,
RegDst_id,MemtoReg_id,RegWrite_id,
MemWrite_id,MemRead_id,ALUCode_id,
ALUSrcB_id,Branch_id,
Imm_id,RsData_id,RtData_id,
RtAddr_id,RdAddr_id
);
input clk;
input reset;
input[31:0] inst_id;//IF����ָ��
 
//WB��������
input RegWrite_wb;
input[4:0] RegWriteAddr_wb;
input[31:0] RegWriteData_wb;
 
//�˸��ź����
output RegWrite_id;
output RegDst_id;
output MemRead_id;
output MemWrite_id;
output ALUSrcB_id;
output Branch_id;
output MemtoReg_id;
output[2:0] ALUCode_id;
 
//�������
output[31:0] Imm_id;//������չ
output[31:0] RsData_id;//�Ĵ��������1
output[31:0] RtData_id;//�Ĵ��������2
output[4:0] RtAddr_id;//rt
output[4:0] RdAddr_id;//rd
 
assign RtAddr_id=inst_id[20:16];//rt
assign RdAddr_id=inst_id[15:11];//rd
assign Imm_id={{16{inst_id[15]}},inst_id[15:0]};//������չ��32λ������
 
/*����ģ��*/
CtrlUnit CtrlUnit(
//����
.inst(inst_id),
//���
.RegWrite(RegWrite_id),.RegDst(RegDst_id),
.Branch(Branch_id),.MemRead(MemRead_id),.MemWrite(MemWrite_id),
.ALUCode(ALUCode_id),.ALUSrc_B(ALUSrcB_id),
.MemtoReg(MemtoReg_id)
);
 
/*�Ĵ�����ģ��*/
RegisterFiles RegisterFiles(
//���룬��WB�����ṩ
.clk(clk),.rst(reset),.L_S(RegWrite_wb),
.R_addr_A(inst_id[25:21]),.R_addr_B(inst_id[20:16]),
.Wt_addr(RegWriteAddr_wb),.wt_data(RegWriteData_wb),
//���
.rdata_A(RsData_id),.rdata_B(RtData_id)
);
 
 
endmodule