`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 13:54:31
// Design Name: 
// Module Name: chip_74ls11
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


module tri_3_input_and_gate#(parameter Delay = 0)(
    input wire A1,B1,C1,A2,B2,C2,A3,B3,C3,
    output wire Y1,Y2,Y3
    );
    
    and #Delay (Y1,A1,B1,C1);
    and #Delay (Y2,A2,B2,C2);
    and #Delay (Y3,A3,B3,C3);
    
endmodule
