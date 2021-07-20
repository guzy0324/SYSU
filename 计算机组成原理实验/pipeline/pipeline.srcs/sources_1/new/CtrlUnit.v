`timescale 1ns / 1ps
module CtrlUnit(inst,RegWrite,RegDst,
Branch,MemRead,
MemWrite,ALUCode,
ALUSrc_B,
MemtoReg
);
input[31:0] inst;
output RegWrite;
output RegDst;
output Branch;
output MemRead;
output MemWrite;
output[2:0] ALUCode;
output ALUSrc_B;
output MemtoReg;//1:来自mem
 
wire[5:0] op;
wire[5:0] func;
wire[4:0] rt;
assign op=inst[31:26];//op字段
assign func=inst[5:0];//func字段
 
//R指令
parameter R_type_op=6'b000000;
parameter ADD_func=6'b100000;
parameter AND_func=6'b100100;
parameter XOR_func=6'b100110;
parameter OR_func=6'b100101;
parameter NOR_func=6'b100111;
parameter SUB_func=6'b100010;
 
//R_type
wire ADD,AND,NOR,OR,SUB,XOR,R_type;
assign ADD=(op==R_type_op)&&(func==ADD_func);
assign AND=(op==R_type_op)&&(func==AND_func);
assign NOR=(op==R_type_op)&&(func==NOR_func);
assign OR=(op==R_type_op)&&(func==OR_func);
assign SUB=(op==R_type_op)&&(func==SUB_func);
assign XOR=(op==R_type_op)&&(func==XOR_func);
assign R_type=ADD||AND||NOR||OR||SUB||XOR;
 
//Branch
parameter BEQ_op=6'b000100;
parameter BNE_op=6'b000101;
wire BEQ,BNE,Branch;
assign BEQ=(op==BEQ_op);
assign BNE=(op==BNE_op);
assign Branch=BEQ||BNE;
 
// I_type instruction decode
parameter ADDI_op=6'b001000;
parameter ANDI_op=6'b001100;
parameter XORI_op=6'b001110;
parameter ORI_op=6'b001101;
wire ADDI,ANDI,XORI,ORI,I_type;
assign ADDI=(op== ADDI_op);
assign ANDI=(op==ANDI_op);
assign XORI=(op==XORI_op);
assign ORI=(op==ORI_op);
assign I_type=ADDI||ANDI||XORI||ORI;
 
// SW ,LW instruction decode
parameter SW_op=6'b101011;
parameter LW_op=6'b100011;
wire SW,LW;
assign SW=(op==SW_op);
assign LW=(op==LW_op);
 
// Control Singal
assign RegWrite=LW||R_type||I_type;//要写寄存器
assign RegDst=R_type;//RegDst=1，选择rd，只有R指令这样
assign MemWrite=SW;
assign MemRead=LW;
assign MemtoReg=LW;
assign ALUSrc_B=LW||SW||I_type;
 
// ALUCode
//自己定义的，只要能在ALU里对应的上就行
parameter alu_add=3'b010;
parameter alu_sub=3'b110;
parameter alu_and=3'b000;
parameter alu_or=3'b001;
parameter alu_xor=3'b100;
parameter alu_nor=3'b101;
 
reg[2:0] ALUCode;
always@(*)begin
if(op==R_type_op
)begin
case(func)
ADD_func: ALUCode<=alu_add;
AND_func: ALUCode<=alu_and;
XOR_func: ALUCode<=alu_xor;
OR_func: ALUCode<=alu_or;
NOR_func: ALUCode<=alu_nor;
SUB_func: ALUCode<=alu_sub;
default: ALUCode<=alu_add;
endcase
end
else
begin
case(op)
BEQ_op: ALUCode<=alu_sub;
BNE_op: ALUCode<=alu_sub;
ADDI_op: ALUCode<=alu_add;
ANDI_op: ALUCode<=alu_and;
XORI_op: ALUCode<=alu_xor;
ORI_op: ALUCode<=alu_or;
SW_op: ALUCode<=alu_add;
LW_op: ALUCode<=alu_add;
default: ALUCode<=alu_add;
endcase
end
end
 
endmodule

