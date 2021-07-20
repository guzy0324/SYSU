`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:42:25
// Design Name: 
// Module Name: sysu_two_input_or_gate
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


module sysu_or2#(parameter Delay = 0)(
 input A,
   input B,
   output Y
   );
   or #Delay (Y,A,B);
endmodule
