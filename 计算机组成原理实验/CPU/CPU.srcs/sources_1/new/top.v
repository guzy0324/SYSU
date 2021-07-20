`timescale 1ns / 1ps
module top( 
    input clkin, 
    input reset, 
    output [31:0] pc, 
    output [31:0] inst, 
    output [31:0] RsData, 
    output [31:0] RtData, 
    output alu_src_a, 
    output [1:0] alu_src_b, 
    output [31:0] mux9, 
    output [31:0] mux8, 
    output [31:0] mux6, 
    output [31:0] mux2, 
    output [2:0] aluop, 
    output [3:0] aluCtr, 
    output [31:0] aluRes, 
    output jal, 
    output [4:0] mux10, 
    output [31:0] resDis, 
    output [31:0] ra, 
    output [31:0] hiReg, 
    output [31:0] hi
    /*input clk, 
    input upper, 
    output [3:0] sm_wei, 
    output [6:0] sm_duan*/
); 
// ָ��Ĵ���pc 
reg[31:0] pc, add4; 
wire choose4; 
// �������ź���
wire[31:0] expand2, mux2, mux3, mux4, mux5, address, jmpaddr, inst; 
wire[4:0] mux1; 
wire[31:0] mux6, mux7, mux8, mux9;
wire[4:0] mux10; 
// CPU�����ź���
wire reg_dst, jmp, branch, memwrite, memtoreg;
wire/*[1:0]*/[2:0] aluop; 
wire /*alu_src, */regwrite;
wire alu_src_a, jal, jr, lui, bne, bltz, bgtz, imm_expand, Write_hi, Write_lo, mult_or_div;
wire[1:0] alu_src_b, flag;
// ALU�ź���
wire zero; 
wire[31:0] aluRes; 
wire negtive;
wire[31:0] hi;
// ALU�����ź���
wire[3:0] aluCtr;
// �ڴ��ź���
wire[31:0] memreaddata; 
// �Ĵ����ź���
wire[31:0] RsData, RtData; 
// ��չ�ź���
wire[31:0] expand; 
// չʾ����
wire [31:0] resDis;
always @(negedge clkin) // ʱ���½��ز���
begin 
    if(!reset) 
    begin
        //pc = mux5; // ������һ��pc���޸�pc 
        pc = mux8; // ������һ��pc���޸�pc 
        add4 = pc + 4; 
    end 
    else 
    begin
        pc = 32'b0; // ��λʱpcд0 
        add4 = 32'h4; 
    end 
end 
// ʵ����������ģ��
ctr mainctr( 
    .opCode(inst[31:26]), 
    .funct(inst[5:0]), 
    .regDst(reg_dst), 
    .aluSrcA(alu_src_a), 
    .aluSrcB(alu_src_b),
    .memToReg(memtoreg), 
    .regWrite(regwrite), 
    .memWrite(memwrite), 
    .branch(branch), 
    .aluop(aluop), 
    .jmp(jmp), 
    .jal(jal), 
    .jr(jr), 
    .lui(lui), 
    .bne(bne),
    .bltz(bltz),
    .bgtz(bgtz),
    .imm_expand(imm_expand),
    .flag(flag),
    .Write_hi(Write_hi),
    .Write_lo(Write_lo),
    .multordiv(mult_or_div)
); 
// ʵ����ALUģ��
alu alu(
    //.input1(RsData), 
    .input1(mux6), 
    .input2(mux2), 
    .aluCtr(aluCtr), 
    .zero(zero), 
    .aluRes(aluRes), 
    .negtive(negtive), 
    .hi(hi)
);
// ʵ����ALU����ģ��
aluctr aluctr1( 
    .ALUOp(aluop), 
    .funct(inst[5:0]), 
    .ALUCtr(aluCtr)
); 
// ʵ����ramģ��
dram dmem( 
    /*.a(aluRes[7:2]), 
    .d(RtData), 
    .clk(!clkin), 
    .we(memwrite), 
    .spo(memreaddata)*/
    .reset(reset), 
    .clk(!clkin),
    .we(memwrite),
    .flag(flag),//00-> byte 01->half word  1x->word
    .a(aluRes[7:0]), 
    .wd(RtData),
    .rd(memreaddata) 
); 
// ʵ����romģ��
/*
irom imem(
    .a(pc[7:2]), 
    .clk(clkin), 
    .spo(inst)
);*/
imem imem(
    .clkin(clkin),
    .pc(pc[7:0]),
    .inst(inst)
);
// ʵ�����Ĵ���ģ��
regFile regfile( 
    .RsAddr(inst[25:21]), 
    .RtAddr(inst[20:16]), 
    .clk(!clkin), 
    .reset(reset), 
    //.regWriteAddr(mux1), 
    .regWriteAddr(mux10), 
    //.regWriteData(mux3), 
    .regWriteData(mux9), 
    .regWriteEn(regwrite), 
    .hiData(hi), 
    .multordiv(mult_or_div), 
    .writeHi(Write_hi), 
    .writeLo(Write_lo), 
    .RsData(RsData), 
    .RtData(RtData), 
    .ra(ra), 
    .hiReg(hiReg), 
    .resDis(resDis)
); 
// ʵ����������չģ��
signext signext(
    .inst(inst[15:0]), 
    .imm_expand(imm_expand), 
    .data(expand)
); 
// ʵ����ѡ����ģ��
MUX5_2_1 MUX1(
    .A(inst[20:16]), 
    .B(inst[15:11]), 
    .Sel(reg_dst), 
    .O(mux1)
);
MUX32_4_1 MUX2(
    .A(RtData),
    .B(expand),
    .C({27'b0, inst[10:6]}), 
    .D(RsData), 
    .Sel(alu_src_b),
    .O(mux2)
);
MUX32_2_1 MUX3(
    .A(aluRes),
    .B(memreaddata),
    .Sel(memtoreg),
    .O(mux3)
);
MUX32_2_1 MUX4(
    .A(add4),
    .B(address),
    .Sel(choose4),
    .O(mux4)
);
MUX32_2_1 MUX5(
    .A(mux4),
    .B(jmpaddr),
    .Sel(jmp),
    .O(mux5)
);
MUX32_2_1 MUX6(
    .A(RsData),
    .B(RtData),
    .Sel(alu_src_a),
    .O(mux6)
);
MUX32_2_1 MUX7(
    .A(mux3),
    .B(add4),
    .Sel(jal),
    .O(mux7)
);
MUX32_2_1 MUX8(
    .A(mux5),
    .B(RsData),
    .Sel(jr),
    .O(mux8)
);
MUX32_2_1 MUX9(
    .A(mux7), 
    .B({inst[15:0], 16'b0}), 
    .Sel(lui), 
    .O(mux9)
);
MUX5_2_1 MUX10(
    .A(mux1),
    .B(5'b11111),
    .Sel(jal),
    .O(mux10)
);
// ʵ������ʾ��
smg_ip_model smg_ip_model(
    .clk(clk),
    .data(resDis),
    .upper(upper),
    .sm_wei(sm_wei),
    .sm_duan(sm_duan)
);
// ���������ź��ߣ���ַ��������չ
/*
assign mux1 = reg_dst ? inst[15:11] : inst[20:16]; 
assign mux2 = alu_src ? expand : RtData; 
assign mux3 = memtoreg ? memreaddata : aluRes; 
assign mux4 = choose4 ? address : add4; 
assign mux5 = jmp ? jmpaddr : mux4;*/
assign choose4 = (bgtz & ~(zero | negtive)) | (bltz & negtive) | (branch & (bne ^ zero));
assign expand2 = expand << 2; 
assign jmpaddr = {add4[31:28], inst[25:0], 2'b00}; 
assign address = add4 + expand2; 
endmodule 