`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:52:00
// Design Name: 
// Module Name: sysu_two_input_nand_gate
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


module sysu_nand2 #(parameter Delay = 0)(
    input A,
    input B,
    output Y
    );
    nand #Delay (Y,A,B);
endmodule
