`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/09 00:52:15
// Design Name: 
// Module Name: signext
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


module signext( 
input [15:0] inst, // ����16λ
output [31:0] data // ���32λ
); 
// ���ݷ��Ų������λ
// �������λΪ1���򲹳�16��1����16'h ffff 
// �������λΪ0���򲹳�16��0 
assign data = inst[15:15]?{16'hffff,inst}:{16'h0000,inst}; 
endmodule 
