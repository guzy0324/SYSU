`timescale 1ns / 1ps 
module rom_top(Clk,Rst/*,data*/,seg,sm_wei);
  input Clk;//系统时钟
  input Rst;//高电平复位
  output [7:0] addr; 
  output [15:0] data;//输出数据
  //output [6:0] seg;//段码
  //output [3:0] sm_wei;//哪个数码管

wire [7:0] data1;
wire [7:0] data2;
wire [15:0] data;
reg [7:0]addr;//rom地址

integer clk_cnt;
reg clkin;//1.33秒一个时钟周期，以此为cpu的时钟周期	10^8/0.75*10^8=4/3=1.33
always @(posedge Clk)
if(clk_cnt==32'd75_000_000)
begin
clk_cnt <= 1'b0;
clkin <= ~clkin;
end 
else
clk_cnt = clk_cnt + 1'b1;

  always@(posedge clkin/*Clk*/ or negedge Rst)
       if(Rst)
              addr<=8'd0;
        else if(addr == 8'd255)
                addr<=8'd0;
        else 
               //addr<=addr+1'b1;
               addr<=addr+2'b10;
/*               
Ins_Rom Ins_Rom (
                 .clka(clkin/*Clk*//*),    // input wire clka
                 .addra(addr),  // input wire [7 : 0] addra
                 .douta(data)  // output wire [15 : 0] douta
               );*/
Ins_Rom_2 Ins_Rom_1 (
                .clka(clkin/*Clk*/),    // input wire clka
                .ena(1'b1),
                .addra(addr),  // input wire [7 : 0] addra
                .douta(data1)  // output wire [15 : 8] douta
              );
Ins_Rom_2 Ins_Rom_2 (
                  .clka(clkin/*Clk*/),    // input wire clka
                  .ena(1'b1),
                  .addra(addr+1'b1),  // input wire [7 : 0] addra
                  .douta(data2)  // output wire [7 : 0] douta
                );
assign data[15:8] = data1[7:0];
assign data[7:0] = data2[7:0];
/*display dis
                  (.clk(Clk),
                   .data (data),
                   .sm_duan(seg),
                   .sm_wei(sm_wei));*/  
endmodule
