`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:55:24
// Design Name: 
// Module Name: two_input_and_gate
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


module sysu_and2 #(parameter Delay = 0)(
    input wire A,B,
    output wire Y
    );
    
    and #Delay (Y,A,B);
  
endmodule
