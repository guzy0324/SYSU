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
input[31:0] inst_id;//IF给的指令
 
//WB级的输入
input RegWrite_wb;
input[4:0] RegWriteAddr_wb;
input[31:0] RegWriteData_wb;
 
//八个信号输出
output RegWrite_id;
output RegDst_id;
output MemRead_id;
output MemWrite_id;
output ALUSrcB_id;
output Branch_id;
output MemtoReg_id;
output[2:0] ALUCode_id;
 
//其他输出
output[31:0] Imm_id;//符号拓展
output[31:0] RsData_id;//寄存器堆输出1
output[31:0] RtData_id;//寄存器堆输出2
output[4:0] RtAddr_id;//rt
output[4:0] RdAddr_id;//rd
 
assign RtAddr_id=inst_id[20:16];//rt
assign RdAddr_id=inst_id[15:11];//rd
assign Imm_id={{16{inst_id[15]}},inst_id[15:0]};//符号扩展成32位立即数
 
/*控制模块*/
CtrlUnit CtrlUnit(
//输入
.inst(inst_id),
//输出
.RegWrite(RegWrite_id),.RegDst(RegDst_id),
.Branch(Branch_id),.MemRead(MemRead_id),.MemWrite(MemWrite_id),
.ALUCode(ALUCode_id),.ALUSrc_B(ALUSrcB_id),
.MemtoReg(MemtoReg_id)
);
 
/*寄存器堆模块*/
RegisterFiles RegisterFiles(
//输入，由WB级来提供
.clk(clk),.rst(reset),.L_S(RegWrite_wb),
.R_addr_A(inst_id[25:21]),.R_addr_B(inst_id[20:16]),
.Wt_addr(RegWriteAddr_wb),.wt_data(RegWriteData_wb),
//输出
.rdata_A(RsData_id),.rdata_B(RtData_id)
);
 
 
endmodule