`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/08 12:08:13
// Design Name: 
// Module Name: sysu_74ls48
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


module sysu_74LS48(
    input LT_n,RBI_n,BCD_A,BCD_B,BCD_C,BCD_D,
    output a,b,c,d,e,f,g,
    inout BI_RBO_n
    );
    
    wire [3:0]BCD;
    reg [6:0]a_to_g;
    wire RBO_buffer;
	wire BI_RBO;
    
     assign  BI_RBO_n=~ BI_RBO;
    assign BCD = {BCD_D,BCD_C,BCD_B,BCD_A};
    
    always@(*)begin
        if(!BI_RBO_n)
            a_to_g <= 7'b000_0000;
        else if(!LT_n)
            a_to_g <= 7'b111_1111;
        else if(RBI_n & BCD == 4'b0000)
                a_to_g <= 7'b111_1110; //0
            else
            case(BCD)
                4'b0001: a_to_g <= 7'b011_0000; //1
                4'b0010: a_to_g <= 7'b110_1101; //2
                4'b0011: a_to_g <= 7'b111_1001; //3
                4'b0100: a_to_g <= 7'b011_0011; //4
                4'b0101: a_to_g <= 7'b101_1011; //5
                4'b0110: a_to_g <= 7'b101_1111; //6
                4'b0111: a_to_g <= 7'b111_0000; //7
                4'b1000: a_to_g <= 7'b111_1111; //8
                4'b1001: a_to_g <= 7'b111_1011; //9
                4'b1010: a_to_g <= 7'b000_1101; //10
                4'b1011: a_to_g <= 7'b001_1001; //11
                4'b1100: a_to_g <= 7'b010_0011; //12
                4'b1101: a_to_g <= 7'b100_1011; //13
                4'b1110: a_to_g <= 7'b000_1111; //14
                4'b1111: a_to_g <= 7'b000_0000; //15
            endcase
				
    end
    
    assign a = a_to_g[6];
    assign b = a_to_g[5];
    assign c = a_to_g[4];
    assign d = a_to_g[3];
    assign e = a_to_g[2];
    assign f = a_to_g[1];
    assign g = a_to_g[0];
    
    assign RBO_buffer = (LT_n&(~RBI_n)&(~BCD_A)&(~BCD_B)&(~BCD_C)&(~BCD_D));
     assign BI_RBO =((~LT_n) || (RBO_buffer)) ? RBO_buffer : 1'bz;

endmodule
