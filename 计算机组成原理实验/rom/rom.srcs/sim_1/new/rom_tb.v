`timescale 1ns / 1ps
`define clk_period 10
module rom_tb;
 
// Inputs
    reg Clk;
    reg  Rst;
    // Outputs
    wire [15:0] dout;
   
    rom_top rom_top(
    .Clk(Clk),
    .Rst(Rst),
    .data(dout));
    initial 
    begin
    Clk = 1;
    Rst=0;
    end
    always #(`clk_period/2)Clk = ~Clk;
        initial begin
              Rst=1'b1;
              #(`clk_period*3); 
               Rst=1'b0;
               #(`clk_period*1000); 
              
               $stop;
            end
endmodule
