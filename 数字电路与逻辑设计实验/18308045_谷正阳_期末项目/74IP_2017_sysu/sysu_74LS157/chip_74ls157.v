`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:07:10
// Design Name: 
// Module Name: chip_74ls157
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


module sysu_74LS157(
	input A1,
	input B1,
	input A2,
	input B2,
	input A3,
	input B3,
	input A4,
	input B4,
	input S,
	input G,
	output Y1,
	output Y2,
	output Y3,
	output Y4
);
  
		assign Y1= S? (B1&(~G)):(A1&(~G));
		assign Y2= S? (B2&(~G)):(A2&(~G));
		assign Y3= S? (B3&(~G)):(A3&(~G));
		assign Y4= S? (B4&(~G)):(A4&(~G));


endmodule

