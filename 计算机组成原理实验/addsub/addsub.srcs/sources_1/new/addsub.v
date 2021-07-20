`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/01/31 12:46:52
// Design Name: 
// Module Name: addsub
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module addsub
#(parameter WIDTH=8)            //ָ�����ݿ�Ȳ�����ȱʡֵ��8
(
    input [(WIDTH-1):0] a,      // ȱʡλ���ɲ���WIDTH����
    input [(WIDTH-1):0] b,
    input  sub,                // =1Ϊ����
    output [(WIDTH-1):0] sum,
    output cf,                  // ��λ��־
    output ovf,                  // �����־
    output sf,                  // ���ű�־
    output zf                   // Ϊ0��־
    );
    //  ����Լ��Ĵ���
    wire [(WIDTH-1):0] subb,subb1;
       wire cf2;    // ��λ
       assign subb1 = b ^ {WIDTH{sub}};  // ���ڼ�����ȡ��
       assign subb  =  subb1 + sub;   // ���ڼ����Ǽ�1��sub=1��������sub=0���ӷ���
    
        assign {cf2,sum} = a + subb;
        assign sf = sum[WIDTH-1];
        assign zf = (sum == 0) ? 1 : 0 ;
        assign cf = cf2 ^ sub;
        assign ovf = (a[WIDTH-1] ^ sum[WIDTH-1]) & (subb[WIDTH-1] ^ sum[WIDTH-1]);


endmodule
