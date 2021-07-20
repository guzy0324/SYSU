`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 14:03:49
// Design Name: 
// Module Name: chip_74ls20
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


module two_4_input_nand_gate#(parameter Delay = 0)(
    input wire A1,B1,C1,D1,A2,B2,C2,D2,
    output wire Y1,Y2
    );
    
    nand #Delay (Y1,A1,B1,C1,D1);
    nand #Delay (Y2,A2,B2,C2,D2);
    
endmodule