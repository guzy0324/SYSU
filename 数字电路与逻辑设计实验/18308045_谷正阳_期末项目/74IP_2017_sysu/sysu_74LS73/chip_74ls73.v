`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 14:42:56
// Design Name: 
// Module Name: chip_74ls73
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


module chip_74ls73(
input J0,
	input K0,
	input CLR0_n,
	input CLK0,
	output Q0,
	output Q0_n,
	input J1,
	input K1,
	input CLR1_n,
	input CLK1,
	output Q1,
	output Q1_n
    );
    
    JKFF jkff1(.J(J0),.K(K0),.CLR_n(CLR0_n),.CLK(CLK0),.Q(Q0),.Q_n(Q0_n));
    JKFF jkff2(.J(J1),.K(K1),.CLR_n(CLR1_n),.CLK(CLK1),.Q(Q1),.Q_n(Q1_n));
    
endmodule

module JKFF(
	input J,
	input K,
	input CLR_n,
	input CLK,
	output reg Q,
	output Q_n
);
	assign Q_n = ~Q;
	always @(negedge CLK or negedge CLR_n)
		begin
			if(!CLR_n)
				Q <= 1'b0;
			else
				begin
					if((!J) && K)
						Q <= 1'b0;
					else if(J && (!K))
						Q <= 1'b1;
					else if(J && K)
						Q <= ~Q;
					else
						Q <= Q;
				end
		end

	
endmodule	
