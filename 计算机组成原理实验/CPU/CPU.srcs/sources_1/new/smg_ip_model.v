`timescale 1ns / 1ps
module smg_ip_model(clk,data,upper,sm_wei,sm_duan);
input clk;
//input [15:0] data;
input [31:0] data;
input upper;
output [3:0] sm_wei;
//output [7:0] sm_duan;
output [6:0] sm_duan;
//---------------------------------------------------------
//分频 
integer clk_cnt;
 
reg clk_400Hz;
always @(posedge clk)
 
if(clk_cnt==32'd100000)
 
begin clk_cnt <= 1'b0; clk_400Hz <= ~clk_400Hz;
end else clk_cnt <= clk_cnt + 1'b1; 

//位控制
reg [3:0]wei_ctrl=4'b1110; //0的那个是亮的那个
always @(posedge /*clk_1000Hz*/clk_400Hz)
    wei_ctrl <= {wei_ctrl[2:0],wei_ctrl[3]}; //段控制 ,就是把最左边的一位弄到最右边
reg [3:0]duan_ctrl; 
/*
always @(wei_ctrl) 
case(wei_ctrl)
4'b1110:duan_ctrl=data[3:0]; 
4'b1101:duan_ctrl=data[7:4]; 
4'b1011:duan_ctrl=data[11:8]; 
4'b0111:duan_ctrl=data[15:12];
default:duan_ctrl=4'hf;
endcase*/
always @(wei_ctrl, upper) 
case({wei_ctrl, upper})
5'b1110_0:duan_ctrl=data[3:0]; 
5'b1101_0:duan_ctrl=data[7:4]; 
5'b1011_0:duan_ctrl=data[11:8]; 
5'b0111_0:duan_ctrl=data[15:12];
5'b1110_1:duan_ctrl=data[19:16]; 
5'b1101_1:duan_ctrl=data[23:20]; 
5'b1011_1:duan_ctrl=data[27:24]; 
5'b0111_1:duan_ctrl=data[31:28];
default:duan_ctrl=4'hf;
endcase
//----------------------------------------------------------
//解码模块
//reg [7:0]duan;
reg [6:0]duan;
always @(duan_ctrl)
case(duan_ctrl) //让数码管相应的显示单元亮
/*
4'h0:duan=8'b1100_0000;//0
4'h1:duan=8'b1111_1001;//1
4'h2:duan=8'b1010_0100;//2
4'h3:duan=8'b1011_0000;//3
4'h4:duan=8'b1001_1001;//4
4'h5:duan=8'b1001_0010;//5
4'h6:duan=8'b1000_0010;//6
4'h7:duan=8'b1111_1000;//7
4'h8:duan=8'b1000_0000;//8
4'h9:duan=8'b1001_0000;//9 
4'ha:duan=8'b1000_1000;//a 
4'hb:duan=8'b1000_0011;//b 
4'hc:duan=8'b1100_0110;//c 
4'hd:duan=8'b1010_0001;//d 
4'he:duan=8'b1000_0110;//e 
4'hf:duan=8'b1000_1110;//f
// 4'hf:duan=8'b1111_1111;//不显示
default : duan = 8'b1100_0000;//0 */
4'h0:duan=8'b100_0000;//0
4'h1:duan=8'b111_1001;//1
4'h2:duan=8'b010_0100;//2
4'h3:duan=8'b011_0000;//3
4'h4:duan=8'b001_1001;//4
4'h5:duan=8'b001_0010;//5
4'h6:duan=8'b000_0010;//6
4'h7:duan=8'b111_1000;//7
4'h8:duan=8'b000_0000;//8
4'h9:duan=8'b001_0000;//9 
4'ha:duan=8'b000_1000;//a 
4'hb:duan=8'b000_0011;//b 
4'hc:duan=8'b100_0110;//c 
4'hd:duan=8'b010_0001;//d 
4'he:duan=8'b000_0110;//e 
4'hf:duan=8'b000_1110;//f
// 4'hf:duan=8'b111_1111;//不显示
default : duan = 8'b100_0000;//0 
endcase
//----------------------------------------------------------
assign sm_wei = wei_ctrl; 
assign sm_duan = duan;
endmodule

