`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/26 09:17:11
// Design Name: 
// Module Name: sysu_SRAM_4X4
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


module sysu_SRAM_4X4(I3,I2,I1,I0,A1,A0,en,WR,RD,D3,D2,D1,D0
 );
input I3,I2,I1,I0,A1,A0,en,WR,RD;
output D3,D2,D1,D0;
reg [3:0]R3;
reg [3:0]R2;
reg [3:0]R1;
reg [3:0]R0;
reg [3:0]out;
wire [1:0]A;
assign A = {A1,A0};
wire [3:0]I;
assign I={I3,I2,I1,I0};
reg D3,D2,D1,D0;
wire wr1;
wire rd1;
assign wr1=WR||en ;
assign rd1=RD||en ;
always@(negedge wr1)
     begin
         case(A)
             2'b00 :R0=I;
             2'b01 :R1=I;
             2'b10 :R2=I;
             2'b11 :R3=I;
         endcase
    end
always@(negedge rd1)
	begin
         case(A)
             2'b00 :out=R0;
             2'b01 :out=R1;
             2'b10 :out=R2;
             2'b11 :out=R3;
         endcase
    end
always@(en)
	begin 
	if(!en)
		begin
			D3=out[3];
			D2=out[2];
			D1=out[1];
			D0=out[0];
		end
	else
		begin
			D3=1'bz;
			D2=1'bz;
			D1=1'bz;
			D0=1'bz;	
		end
	end
endmodule