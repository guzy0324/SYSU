`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 14:14:46
// Design Name: 
// Module Name: chip_74ls30
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


module one_8_input_nand_gate #(parameter Delay = 0)(
    input wire A,B,C,D,E,F,G,H,
    output wire Y
    );
    
    nand #Delay (Y,A,B,C,D,E,F,G,H);
    
endmodule
