`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/24 10:58:22
// Design Name: 
// Module Name: sysu_tri_gate
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


module sysu_tri_gate( din,en,dout
   );
input din;
input en;
output dout;
reg dout;

always@(din,en)
    if(en)
      dout = 1'bz;
    else
      dout = din;

endmodule