`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:16:35
// Design Name: 
// Module Name: chip_74ls194
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


module sysu_74LS194(
    input A,
	input B,
	input C,
	input D,
	input S0,
	input S1,
	input CR_n,
	input CP,
	input DSR,
	input DSL,
	output QA,
	output QB,
	output QC,
	output QD
);
	wire [3:0] in = {A,B,C,D};
	reg [3:0] o_buf;
	wire [1:0] select;
	
	assign select = {S1,S0};
	assign QA = o_buf[3];
	assign QB = o_buf[2];
	assign QC = o_buf[1];
	assign QD = o_buf[0];
	
	
	always@(posedge CP or negedge CR_n)
		begin
			if (!CR_n)
				o_buf <= 4'b0;
			else 
				case (select)
					2'b00 : o_buf <= o_buf;
					2'b01 :	o_buf <= {DSR,o_buf[3:1]};
					2'b10 : o_buf <= {o_buf[2:0],DSL};
					default:o_buf <= in;			
				endcase
		end
endmodule
