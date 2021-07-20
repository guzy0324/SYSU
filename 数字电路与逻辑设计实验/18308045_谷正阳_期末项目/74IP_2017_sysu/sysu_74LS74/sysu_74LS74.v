`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/09 09:21:32
// Design Name: 
// Module Name: sysu_74LS74
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


module sysu_74LS74(
    input D0,
	input RD0_n,
	input SD0_n,
	input CP0,
	input D1,
	input RD1_n,
	input SD1_n,
	input CP1,
	output Q0,
	output Q0_n,
	output Q1,
	output Q1_n
);
	DFF dff1(.D(D0),.RD_n(RD0_n),.SD_n(SD0_n),.CP(CP0),.Q(Q0),.Q_n(Q0_n));
	DFF dff2(.D(D1),.RD_n(RD1_n),.SD_n(SD1_n),.CP(CP1),.Q(Q1),.Q_n(Q1_n));

endmodule

module DFF(
	input D,
	input RD_n,
	input SD_n,
	input CP,
	output reg Q,
	output Q_n
);
	assign Q_n = ~Q;
	
	always @(posedge CP or negedge SD_n or negedge RD_n)
		begin
			if(!SD_n)
				Q <= 1'b1;
			else
				begin
					if(!RD_n)
						Q <= 1'b0;
					else
						Q <= D;
				end
		end
		
endmodule
