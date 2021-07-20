`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:02:44
// Design Name: 
// Module Name: chip_74ls153
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


module sysu_74LS153(
    input A,B,E1_n,E2_n,D10,D11,D12,D13,D20,D21,D22,D23,
    output Y1,Y2
    );
	assign Y1=((~B&~A&D10)|(~B&A&D11)|(B&~A&D12)|(B&A&D13))&(~E1_n);
	assign Y2=((~B&~A&D20)|(~B&A&D21)|(B&~A&D22)|(B&A&D23))&(~E2_n);
endmodule

