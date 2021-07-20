`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/06 15:23:12
// Design Name: 
// Module Name: display
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


//数码管 ip 核
 
//数码管 ip 核
 
module display(clk,data,sm_wei,sm_duan); 
input clk;
 
input [15:0] data; 
output [3:0] sm_wei; 
output [6:0] sm_duan;

//----------------------------------------------------------
 
//分频 
integer clk_cnt;
 
reg clk_400Hz; always @(posedge clk)
 
if(clk_cnt==32'd100000)
 
begin clk_cnt <= 1'b0; clk_400Hz <= ~clk_400Hz;
end else clk_cnt <= clk_cnt + 1'b1; 
//----------------------------------------------------------
//位控制
 
reg [3:0]wei_ctrl=4'b1110; always @(posedge clk_400Hz)
 
wei_ctrl <= {wei_ctrl[2:0],wei_ctrl[3]}; 
//段控制 
reg [3:0]duan_ctrl;
 
always @(wei_ctrl, data)
case(wei_ctrl) 
4'b1110:duan_ctrl=data[3:0]; 
4'b1101:duan_ctrl=data[7:4]; 
4'b1011:duan_ctrl=data[11:8];
4'b0111:duan_ctrl=data[15:12];
default:duan_ctrl=4'hf;
 endcase
 
//----------------------------------------------------------
 
//解码模块 
reg [7:0]duan;
 
always @(duan_ctrl) 
case(duan_ctrl) 
4'h0:duan=7'b100_0000;//0
4'h1:duan=7'b111_1001;//1
4'h2:duan=7'b010_0100;//2
4'h3:duan=7'b011_0000;//3
4'h4:duan=7'b001_1001;//4
4'h5:duan=7'b001_0010;//5
4'h6:duan=7'b000_0010;//6
4'h7:duan=7'b111_1000;//7
4'h8:duan=7'b000_0000;//8
4'h9:duan=7'b001_0000;//9 
4'ha:duan=7'b000_1000;//a 
4'hb:duan=7'b000_0011;//b 
4'hc:duan=7'b100_0110;//c 
4'hd:duan=7'b010_0001;//d 
4'he:duan=7'b000_0111;//e       
4'hf:duan=7'b000_1110;//f
 
// 4'hf:duan=7'b111_1111;//不显示 
default : duan = 7'b100_0000;//0
endcase
 
//----------------------------------------------------------
 
assign sm_wei = wei_ctrl; 
assign sm_duan = duan; 
endmodule

