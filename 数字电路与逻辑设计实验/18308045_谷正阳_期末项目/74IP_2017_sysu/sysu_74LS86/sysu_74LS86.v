`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/29 14:33:22
// Design Name: 
// Module Name: sysu_74LS86
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


module sysu_74LS86 #(parameter Delay = 0)(
    input A1,
    input B1,
    input A2,
    input B2,
    input A3,
    input B3,
    input A4,
    input B4,
    output Y1,
    output Y2,
    output Y3,
    output Y4
    );
    xor #Delay(Y1,A1,B1);
    xor #Delay(Y2,A2,B2);
    xor #Delay(Y3,A3,B3);
    xor #Delay(Y4,A4,B4);
endmodule