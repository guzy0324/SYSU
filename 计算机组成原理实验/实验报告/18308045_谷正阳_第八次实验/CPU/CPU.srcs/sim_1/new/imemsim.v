`timescale 1ns / 1ps
module imemsim;
reg clkin;
reg [7:0] pc;
wire [31:0] inst;

imem uutimem (
    .clkin(clkin),
    .pc(pc),
    .inst(inst)
);  
initial begin 
// Initialize Inputs 
clkin = 0; 
pc = 0;
end 
parameter PERIOD = 20; 
always begin 
clkin = 1'b0; 
#(PERIOD / 2) 
clkin = 1'b1;
#(PERIOD / 2)
pc = pc + 4;
end 
endmodule 