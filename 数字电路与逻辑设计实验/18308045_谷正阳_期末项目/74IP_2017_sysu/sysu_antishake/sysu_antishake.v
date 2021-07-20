`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/10 12:07:41
// Design Name: 
// Module Name: sysu_antishake
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


module sysu_antishake(
	input clk100Mhz,
	input button_in,
	output button_out
);
	reg delay1,delay2,delay3;
	reg [20:0]count;
	reg clk50Hz;
	
//clk50Hz	
    always@(posedge clk100Mhz)
     begin
        if(count <999999)
         count <= count + 1'b1;
        else
            begin
                   count <= 0;
                   clk50Hz <= ~clk50Hz;
            end
      end
	  
//antishake	  
	always@( posedge clk50Hz)
		 begin
			delay1  <= ~button_in; 
			delay2  <= delay1;
			delay3  <= delay2;
		 end

	assign button_out =~( delay1&delay2&delay3);
	
endmodule
