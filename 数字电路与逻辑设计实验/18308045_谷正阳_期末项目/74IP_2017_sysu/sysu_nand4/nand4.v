`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:27:28
// Design Name: 
// Module Name: nand4
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


module sysu_nand4 #(parameter DELAY = 3)(
    input a,
    input b,
    input c,
    input d,
    output y
    );
    
    nand #DELAY (y,a,b,c,d);
    
endmodule
