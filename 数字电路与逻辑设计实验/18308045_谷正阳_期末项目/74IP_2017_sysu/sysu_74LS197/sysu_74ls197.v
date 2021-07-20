`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/17 15:20:46
// Design Name: 
// Module Name: sysu_74ls197
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


module sysu_74LS197(
input P0,
	input P1,
	input P2,
	input P3,
	input MR,
	input PL,
	input CP0,
	input CP1,
	output reg Q0,
	output Q1,
	output Q2,
	output Q3

);
	reg [2:0] oct_cnt;
	
	assign Q1 = oct_cnt[0];
	assign Q2 = oct_cnt[1];
	assign Q3 = oct_cnt[2];
	
	always@(negedge CP0 or negedge MR or negedge PL)
		begin
			if(!MR)
				Q0 <= 1'b0;
			else if(!PL)
				Q0 <= P0;
			else 
				Q0 <= !Q0;
		end			
	always@(negedge CP1 or negedge MR or negedge PL)
		begin
			if(!MR)
				oct_cnt <= 3'b000;
			else if(!PL)
				oct_cnt <= {P3,P2,P1};
			else 
				oct_cnt <= oct_cnt+1;
		end

endmodule
