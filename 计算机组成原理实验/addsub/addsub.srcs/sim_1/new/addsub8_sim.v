`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/10/24 15:26:57
// Design Name: 
// Module Name: addsub8_sim
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


module addsub8_sim(    );
    // input
    reg [7:0] a = 8'h16;
    reg [7:0] b = 8'h12;
    reg sub = 0;
    
    //output
    wire [7:0] sum;
    wire cf;
    wire ovf;
    wire sf;
    wire zf;
    
    // initial
    addsub U (a,b,sub,sum,cf,ovf,sf,zf);
    initial begin
    #200 sub = 1;
    #200 begin a = 8'h7f; b = 8'h2; sub = 0; end
    #200 begin a = 8'hff; b = 8'h2; sub = 0; end
    #200 begin a = 8'h16; b = 8'h17; sub = 1; end
    #200 begin a = 8'hfe; b = 8'hff; sub = 1; end

    end

endmodule
