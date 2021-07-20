`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/09/07 14:57:58
// Design Name: 
// Module Name: chip_74LS138
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


module sysu_74LS138(
    input wire A0,A1,A2,E1,E2_n,E3_n,
    output wire Y0_n,Y1_n,Y2_n,Y3_n,Y4_n,Y5_n,Y6_n,Y7_n
    );
    
    reg [7:0]y;
    integer i;
    
    always@*
        if({E1,E2_n,E3_n} == 3'b100)
            for(i=0; i<=7; i=i+1)
                if({A2,A1,A0} == i)
                    y[i]=0;
                else
                    y[i]=1;
        else
            y = 8'hff;
            
    assign Y0_n = y[0];            
    assign Y1_n = y[1];            
    assign Y2_n = y[2];            
    assign Y3_n = y[3];            
    assign Y4_n = y[4];            
    assign Y5_n = y[5];            
    assign Y6_n = y[6];            
    assign Y7_n = y[7];
                
endmodule

