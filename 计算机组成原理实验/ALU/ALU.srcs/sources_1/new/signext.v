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
input [15:0] inst, // 输入16位
output [31:0] data // 输出32位
); 
// 根据符号补充符号位
// 如果符号位为1，则补充16个1，即16'h ffff 
// 如果符号位为0，则补充16个0 
assign data = inst[15:15]?{16'hffff,inst}:{16'h0000,inst}; 
endmodule 
