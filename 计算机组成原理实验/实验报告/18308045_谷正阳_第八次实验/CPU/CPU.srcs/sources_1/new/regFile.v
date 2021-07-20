`timescale 1ns / 1ps
module regFile( 
    input clk,
    input reset,
    input [31:0] regWriteData, //д�Ĵ�����ֵ
    input [4:0] regWriteAddr, //д�Ĵ���ʱ�Ĵ����ĵ�ַ����д�ĸ��Ĵ����� 
    input regWriteEn,	//д�Ĵ���ʹ��
    input [4:0] RsAddr,	//�ĸ��Ĵ�����Ϊ RS �Ĵ��� 
    input [4:0] RtAddr,		//�ĸ��Ĵ�����Ϊ RT �Ĵ��� 
    input [31:0] hiData, //��λ�Ĵ���ֵ
    input multordiv, //д��λ��λ�Ĵ���ʹ��
    input writeHi, //����λ�Ĵ���ʹ��
    input writeLo, //����λ�Ĵ���ʹ��
    output [31:0] RsData,			//RS �μĴ�����ֵ
    output [31:0] RtData,  //RT �Ĵ�����ֵ
    output [31:0] ra, 
    output [31:0] hiReg, 
    output [31:0] resDis //������ʾ���
);
//�Ĵ�����ַ���� 5 λ������������Ϊ�Ĵ���ֻ�� 32 ����5 λ���ܱ�ʾ���мĴ���
reg[31:0]regs[0:31]; // �Ĵ�����
reg[31:0] hi;//��λ�Ĵ���
reg[31:0] lo;//��λ�Ĵ���
assign ra = regs[31];
assign hiReg = hi;
assign resDis = writeHi ? hi :
                writeLo ? lo : regWriteData;
//  ���ݵ�ַ���� Rs��Rt �Ĵ�������
assign RsData = (RsAddr == 5'b0 ) ? 32'b0 : regs[RsAddr]; 
assign RtData = (RtAddr == 5'b0 ) ? 32'b0 : regs[RtAddr];
integer i;
always @( posedge clk ) // ʱ�������ز���
begin
    if(!reset) 
    begin
        if(multordiv == 1) 
        begin
            hi = hiData;
            lo = regWriteData;
        end
        if(regWriteEn == 1) //  дʹ���ź�Ϊ 1 ʱд����
            if(writeHi)
                regs[regWriteAddr] = hi;
            else if(writeLo)
                regs[regWriteAddr] = lo;
            else
                regs[regWriteAddr] = regWriteData; // д������
    end
    else
    begin
        for(i = 0; i < 32; i = i + 1)
            regs[i] = 0; //  ����ʱ���мĴ�����ֵΪ 0����λ
            hi = 0;
            lo = 0;
    end
end
endmodule
