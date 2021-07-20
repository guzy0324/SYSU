`timescale 1ns / 1ps
module dram (
    input clk, we,
    input reset,
    input [1:0] flag,//00-> byte 01->half word  1x->word
    input [7:0] a, 
    input [31:0] wd,
    output [31:0] rd
);
			 	 
reg [7:0] RAM[255:0]; 

//read
assign rd=flag[1]? { {RAM[a+3]},{RAM[a+2]},{RAM[a+1]},{RAM[a+0]}} : ( flag[0]?{ {16{RAM[a+1][7]}} ,{RAM[a+1]},{RAM[a]} }:{ {24{RAM[a][7]}} ,RAM[a]} );

//write flag作为字节或字半字操作的标志
integer i;
always @ (posedge clk,posedge reset)
begin
    if(reset)begin
        for(i = 0; i < 256; i = i + 1) 
            RAM[i]=0;       
    end	
    else if (we) begin
        if(flag==2'b00)
        begin
            RAM[a]=wd[7:0];
        end
        else if(flag==2'b01 )
        begin
            { {RAM[a+1]},{RAM[a]} }=wd[15:0];
        end
        else if(flag==2'b11 )
        begin
            { {RAM[a+3]},{RAM[a+2]},{RAM[a+1]},{RAM[a+0]}}=wd;
        end           
    end  
end
    
    
endmodule
