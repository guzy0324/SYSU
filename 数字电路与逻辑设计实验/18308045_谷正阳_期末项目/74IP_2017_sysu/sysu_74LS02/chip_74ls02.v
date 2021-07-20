`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/04 13:11:09
// Design Name: 
// Module Name: chip_74ls02
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


module sysu_74LS02 #(parameter Delay = 0)(
    input wire A1,B1,A2,B2,A3,B3,A4,B4,
    output wire Y1,Y2,Y3,Y4
    );
    
    nor #Delay (Y1,A1,B1);
    nor #Delay (Y2,A2,B2);
    nor #Delay (Y3,A3,B3);
    nor #Delay (Y4,A4,B4);
    
endmodule