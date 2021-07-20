`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/11/25 09:59:13
// Design Name: 
// Module Name: sysu_ROM_8X8
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


module sysu_ROM_8X8 #(parameter R1 = 8'b0,R2 = 8'b0,R3 = 8'b0,R4 = 8'b0,R5 = 8'b0,R6 = 8'b0,R7 = 8'b0,R8 = 8'b0)(
input A2,A1,A0,
output [7:0]Dout
    );
wire [2:0]A;
reg [7:0]D;
assign A={A2,A1,A0};
always@(A)
    begin
       case(A)
       3'b000:D=R1;
       3'b001:D=R2;
       3'b010:D=R3;
       3'b011:D=R4;
       3'b100:D=R5;
       3'b101:D=R6;
       3'b110:D=R7;
       3'b111:D=R8;
        endcase
    end
 assign Dout=D;   
endmodule
