`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 15:10:05
// Design Name: 
// Module Name: chip_74ls160
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


module sysu_74LS160(
P0, P1, P2, P3, Q0, Q1, Q2, Q3,
    PE_N, CET, CEP, R_N, TC, CP);
	input wire CP, P0, P1, P2, P3, R_N, CET, CEP, PE_N;
	output wire Q0, Q1, Q2, Q3, TC;
	reg[3:0] Q;
	
	initial 
		begin
			Q <= 0;
		end
	
	always @(posedge CP or negedge R_N)
		begin
			if(!R_N)
				Q <= 0;
			else
				begin
					if(!PE_N)
						begin
							Q[0] <= P0;
							Q[1] <= P1;
							Q[2] <= P2;
							Q[3] <= P3;
						end
					else if(CET && CEP)
						begin
							if(Q >= 9)
								Q <= 0;
							else
								Q <= Q+1;
						end
					else
						Q <= Q;
				end
		end
	
	
	assign Q0 = Q[0];
	assign Q1 = Q[1];
	assign Q2 = Q[2];
	assign Q3 = Q[3];
	assign TC = CET & Q3 & (~Q2) & (~Q1) & Q0;
	
endmodule