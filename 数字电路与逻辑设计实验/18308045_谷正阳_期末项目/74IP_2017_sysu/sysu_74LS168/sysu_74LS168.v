`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/19 09:58:37
// Design Name: 
// Module Name: sysu_74LS168
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


module sysu_74LS168(

	input wire D0, D1, D2, D3, CP,LD_n, U_D,ENT_n, ENP_n, 
	output wire Q0, Q1, Q2, Q3, TC
);
	reg[3:0] Q;
	
	initial 
		begin
			Q <= 0;
		end
	
	always @(posedge CP)
		begin
			if(!LD_n)
				begin
					Q[0] <= D0;
					Q[1] <= D1;
					Q[2] <= D2;
					Q[3] <= D3;
				end
			else if((~ENT_n) && (~ENP_n))
				begin
					if (U_D)
						begin
							if(Q >= 9)
								Q <= 0;
							else
								Q <= Q+1;
						end
					else
					    begin
						if(Q <= 0)
							Q <= 9;
						else
							Q <= Q-1;
                        end
				end
				else
					Q <= Q;
				
		end
	
	
	assign Q0 = Q[0];
	assign Q1 = Q[1];
	assign Q2 = Q[2];
	assign Q3 = Q[3];
	assign TC = (~(U_D & Q3 & (~Q2) & (~Q1) & Q0)) && (~((~U_D) & (~Q3) & (~Q2) & (~Q1) & (~Q0)));
	
endmodule
