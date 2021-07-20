`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/29 14:37:06
// Design Name: 
// Module Name: sysu_74LS164
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


module sysu_74LS164(
    input DSA,DSB,CP,MR_n,
    output Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7
    );
    
    reg [7:0]Q_r;
    
    always@(posedge CP,negedge MR_n)begin
        if(!MR_n)
            Q_r <= 8'b0;
        else begin
            Q_r = Q_r << 1;
            Q_r[0] = DSA && DSB;
        end
    end
    
    assign {Q7,Q6,Q5,Q4,Q3,Q2,Q1,Q0} = Q_r;
    
endmodule
