`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/24 15:52:53
// Design Name: 
// Module Name: sysu_74LS283
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


module sysu_74LS283(A3,A2,A1,A0,B3,B2,B1,B0,Ci,S3,S2,S1,S0,Co

    );
    input A3,A2,A1,A0,B3,B2,B1,B0,Ci;
    output S3,S2,S1,S0,Co;
	wire C1,C2,C3;
    assign S0=A0^B0^Ci;
    assign C1=~((~(A0&B0))&(~(A0&Ci))&(~(B0&Ci)));
	assign S1=A1^B1^C1;
    assign C2=~((~(A1&B1))&(~(A1&C1))&(~(B1&C1)));
	assign S2=A2^B2^C2;
    assign C3=~((~(A2&B2))&(~(A2&C2))&(~(B2&C2)));
	assign S3=A3^B3^C3;
    assign Co=~((~(A3&B3))&(~(A3&C3))&(~(B3&C3)));
endmodule
