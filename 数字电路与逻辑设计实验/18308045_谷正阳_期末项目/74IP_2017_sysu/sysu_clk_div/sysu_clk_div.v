`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/09 13:04:50
// Design Name: 
// Module Name: sysu_clk_div
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


module sysu_clk_div #(parameter F = 1)(
    input clk_in,
    output reg clk_out
    );
    
    reg [31:0]count;
    always@(posedge clk_in)
     begin
        if(count <( 50000000/F))
         count <= count + 1'b1;
        else
            begin
                   count <= 0;
                    clk_out <= ~clk_out;
            end
      end

endmodule

