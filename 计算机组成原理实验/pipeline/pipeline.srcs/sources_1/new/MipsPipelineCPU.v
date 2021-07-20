`timescale 1ns / 1ps
module MipsPipelineCPU(clk,reset,inst_if,
alu_res_ex,Dout_mem,
RtData_id,PC_out
,MemRead_mem,MemWrite_mem,alu_res_mem,RtData_mem
);
//CPUģ�����룺clk��reset
//CPUģ�������PC��ַ��ָ�ALU���������Ĵ����ѵ��������B��Memory���
//��Щ���ݶ���һ��ʼ�����ʹ��ݸ����
input clk;//100Mhz
input reset;
output[31:0] inst_if;//ָ��,�͸������data2
output[31:0] alu_res_ex;//ALU����͸�data4
output[31:0] Dout_mem;//memory����͸�data6,����ͼ���Data_in
output[31:0] RtData_id;//�Ĵ����ѵ����B���͸�data5������ͼ���Data_out
output[31:0] PC_out;//pc���͸�data7
output MemRead_mem;
output MemWrite_mem;
output[31:0] alu_res_mem;
output[31:0] RtData_mem;

/*IF��*/
wire branch_or_pc_mem;//������MEM���ģ�
wire[31:0] Branch_addr_mem;//������MEM���ģ�
wire[31:0] next_pc_if;
wire[31:0] inst_if;
IF IF(
//����
.clk(clk),
.reset(reset),
.branch_or_pc(branch_or_pc_mem),//��ҪMEM�����룬branch_or_pc_mem
.branch_addr(Branch_addr_mem),//��ҪEX/MEM������
//���
.next_pc_if(next_pc_if),
.inst_if(inst_if),
.pc(PC_out)//��ǰpc
);
 
/*IF-ID�Ĵ���*/
wire[31:0] next_pc_id;
wire[31:0] inst_id;
flipflop#(.WIDTH(32))IF_ID1(
.clk(clk),
.reset(reset),
.in(inst_if),//��ָ��
.out(inst_id)
);
flipflop#(.WIDTH(32))IF_ID2(
.clk(clk),
.in(next_pc_if),//��pc+4
.reset(reset),
.out(next_pc_id)
);
 
//ע������������WB���Ķ�����RegWrite��RegWriteAddr���е���ң�дWB��ע�ⲻҪ�ظ���
wire[4:0] RtAddr_id,RdAddr_id;
wire RegWrite_wb,MemtoReg_id,RegWrite_id,MemWrite_id;
wire MemRead_id,ALUSrcB_id,RegDst_id,Branch_id;
wire[4:0] RegWriteAddr_wb;
wire[2:0] ALUCode_id;
wire[31:0] Imm_id,RsData_id,RtData_id;
 
/*ID��*/
wire[31:0] RegWriteData_wb;//WB���Ķ�����ע�⣡
assign RegWriteData_wb=reg_data_wb;
 
ID ID(.clk(clk),.reset(reset),.inst_id(inst_id),
.RegWrite_wb(RegWrite_wb),.RegWriteAddr_wb(RegWriteAddr_wb),
.RegWriteData_wb(RegWriteData_wb),//�ͽ���������Ҫ����ѡ����WB����Ϊreg_data_wb��
.RegWrite_id(RegWrite_id),.RegDst_id(RegDst_id),.MemtoReg_id(MemtoReg_id),
.MemWrite_id(MemWrite_id),.MemRead_id(MemRead_id),
.ALUCode_id(ALUCode_id),.ALUSrcB_id(ALUSrcB_id),
.Branch_id(Branch_id),.Imm_id(Imm_id),.RsData_id(RsData_id),.RtData_id(RtData_id),
.RtAddr_id(RtAddr_id),.RdAddr_id(RdAddr_id));
 
/*ID-EX����Ĵ���*/
//�ܹ�14����
wire[4:0] RtAddr_ex,RdAddr_ex;
wire MemtoReg_ex,RegWrite_ex,MemWrite_ex;
wire MemRead_ex,ALUSrcB_ex,RegDst_ex,Branch_ex;
wire[2:0] ALUCode_ex;
wire[31:0] Imm_ex,RsData_ex,RtData_ex,next_pc_ex;
flipflop#(.WIDTH(1))ID_EX1(
.clk(clk),
.reset(reset),
.in(RegWrite_id),//RegWrite
.out(RegWrite_ex)
);
flipflop#(.WIDTH(1))ID_EX2(
.clk(clk),
.reset(reset),
.in(RegDst_id),//RegDst
.out(RegDst_ex)
);
flipflop#(.WIDTH(1))ID_EX3(
.clk(clk),
.reset(reset),
.in(MemRead_id),//MemRead
.out(MemRead_ex)
);
flipflop#(.WIDTH(1))ID_EX4(
.clk(clk),
.reset(reset),
.in(MemWrite_id),//MemWrite
.out(MemWrite_ex)
);
flipflop#(.WIDTH(1))ID_EX5(
.clk(clk),
.reset(reset),
.in(ALUSrcB_id),//ALUSrcB_id
.out(ALUSrcB_ex)
);
flipflop#(.WIDTH(1))ID_EX6(
.clk(clk),
.reset(reset),
.in(MemtoReg_id),//MemtoReg
.out(MemtoReg_ex)
);
flipflop#(.WIDTH(1))ID_EX7(
.clk(clk),
.reset(reset),
.in(Branch_id),//Branch
.out(Branch_ex)
);
flipflop#(.WIDTH(3))ID_EX8(//ע������Ŀ����3��
.clk(clk),
.reset(reset),
.in(ALUCode_id),//ALUCode
.out(ALUCode_ex)
);
flipflop#(.WIDTH(32))ID_EX9(//ע����32λ��
.clk(clk),
.reset(reset),
.in(next_pc_id),//pc+4
.out(next_pc_ex)
);
flipflop#(.WIDTH(32))ID_EX10(
.clk(clk),
.reset(reset),
.in(RsData_id),//�Ĵ�����A
.out(RsData_ex)
);
flipflop#(.WIDTH(32))ID_EX11(
.clk(clk),
.reset(reset),
.in(RtData_id),//�Ĵ�����B
.out(RtData_ex)
);
flipflop#(.WIDTH(32))ID_EX12(
.clk(clk),
.reset(reset),
.in(Imm_id),//Imm,������չ
.out(Imm_ex)
);
flipflop#(.WIDTH(5))ID_EX13(//ע������5��
.clk(clk),
.reset(reset),
.in(RtAddr_id),//rt
.out(RtAddr_ex)
);
flipflop#(.WIDTH(5))ID_EX14(
.clk(clk),
.reset(reset),
.in(RdAddr_id),//rd
.out(RdAddr_ex)
);
 
/*EX��*/
wire[31:0] Branch_addr_ex;
wire[31:0] alu_res_ex;
wire alu_zero_ex;
wire[4:0] RegWriteAddr_ex;
EX EX(.clk(clk),.next_pc_ex(next_pc_ex),
.ALUCode_ex(ALUCode_ex),.ALUSrcB_ex(ALUSrcB_ex),
.RegDst_ex(RegDst_ex),
.Imm_ex(Imm_ex),.RsData_ex(RsData_ex),.RtData_ex(RtData_ex),
.RtAddr_ex(RtAddr_ex),.RdAddr_ex(RdAddr_ex),
//���
.Branch_addr_ex(Branch_addr_ex),
.alu_zero_ex(alu_zero_ex),.alu_res_ex(alu_res_ex),
.RegWriteAddr_ex(RegWriteAddr_ex)
);
 
/*EX-MEM����Ĵ���*/
wire RegWrite_mem;
wire MemRead_mem;
wire MemWrite_mem;
wire MemtoReg_mem;
wire[31:0] alu_res_mem;
wire alu_zero_mem;
wire[31:0] RtData_mem;
wire[4:0] RegWriteAddr_mem;
flipflop#(.WIDTH(1))EX_MEM1(
.clk(clk),
.reset(reset),
.in(RegWrite_ex),//RegWrite
.out(RegWrite_mem)
);
flipflop#(.WIDTH(1))EX_MEM2(
.clk(clk),
.reset(reset),
.in(MemRead_ex),//MemRead
.out(MemRead_mem)
);
flipflop#(.WIDTH(1))EX_MEM3(
.clk(clk),
.reset(reset),
.in(MemWrite_ex),//MemWrite
.out(MemWrite_mem)
);
flipflop#(.WIDTH(1))EX_MEM4(
.clk(clk),
.reset(reset),
.in(MemtoReg_ex),//MemtoReg
.out(MemtoReg_mem)
);
flipflop#(.WIDTH(1))EX_MEM5(
.clk(clk),
.reset(reset),
.in(Branch_ex),//Branch
.out(Branch_mem)
);
flipflop#(.WIDTH(32))EX_MEM6(//ע����32λ��
.clk(clk),
.reset(reset),
.in(Branch_addr_ex),//Branch��ַ
.out(Branch_addr_mem)//ע�������ͻ�IF����
);
flipflop#(.WIDTH(32))EX_MEM7(
.clk(clk),
.reset(reset),
.in(alu_res_ex),//alu���
.out(alu_res_mem)
);
flipflop#(.WIDTH(1))EX_MEM8(
.clk(clk),
.reset(reset),
.in(alu_zero_ex),//alu�����ź�
.out(alu_zero_mem)
);
flipflop#(.WIDTH(32))EX_MEM9(
.clk(clk),
.reset(reset),
.in(RtData_ex),//RtData
.out(RtData_mem)
);
flipflop#(.WIDTH(5))EX_MEM10(
.clk(clk),
.reset(reset),
.in(RegWriteAddr_ex),//д�ص�ַ
.out(RegWriteAddr_mem)
);
 
/*MEM��*/
wire[31:0] Dout_mem;
 
MEM MEM(
.clk(clk),.MemRead_mem(MemRead_mem),.MemWrite_mem(MemWrite_mem),
.Branch_mem(Branch_mem),
.alu_zero_mem(alu_zero_mem),
.alu_res_mem(alu_res_mem),.RtData_mem(RtData_mem),
.branch_or_pc_mem(branch_or_pc_mem),.Dout_mem(Dout_mem)//ע���ź�Ҫ�����ͣ���IF
);
 
/*MEM-WB����Ĵ���*/
wire[31:0] Dout_wb;
wire[31:0] alu_res_wb;
 
wire MemtoReg_wb;
flipflop#(.WIDTH(1))MEM_WB1(
.clk(clk),
.reset(reset),
.in(RegWrite_mem),//RegWrite
.out(RegWrite_wb)
);
flipflop#(.WIDTH(1))MEM_WB2(
.clk(clk),
.reset(reset),
.in(MemtoReg_mem),//MemtoReg
.out(MemtoReg_wb)
);
flipflop#(.WIDTH(32))MEM_WB3(//ע��������32λ
.clk(clk),
.reset(reset),
.in(Dout_mem),//Dout��RAM�����
.out(Dout_wb)
);
flipflop#(.WIDTH(32))MEM_WB4(
.clk(clk),
.reset(reset),
.in(alu_res_mem),//alu�Ľ��
.out(alu_res_wb)
);
flipflop#(.WIDTH(5))MEM_WB5(//ע����5λ
.clk(clk),
.reset(reset),
.in(RegWriteAddr_mem),//RegWriteAddr
.out(RegWriteAddr_wb)
);
 
/*WB��*/
reg[31:0] reg_data_wb;
 
always@(*)begin
case(MemtoReg_wb)
1'b0:reg_data_wb<=alu_res_wb;//����ALU
1'b1:reg_data_wb<=Dout_wb;//����RAM
endcase
end
 
endmodule
