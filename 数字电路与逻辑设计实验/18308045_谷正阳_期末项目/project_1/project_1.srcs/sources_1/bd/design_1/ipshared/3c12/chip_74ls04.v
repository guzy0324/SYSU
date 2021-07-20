`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/04 13:14:55
// Design Name: 
// Module Name: chip_74ls04
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


module sysu_74LS04 #(parameter Delay = 0)(
    input wire A1,A2,A3,A4,A5,A6,
    output wire Y1,Y2,Y3,Y4,Y5,Y6
    );
    
    not #Delay (Y1,A1);
    not #Delay (Y2,A2);
    not #Delay (Y3,A3);
    not #Delay (Y4,A4);
    not #Delay (Y5,A5);
    not #Delay (Y6,A6);
    
endmodule
