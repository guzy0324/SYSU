`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/10/29 14:25:23
// Design Name: 
// Module Name: sysu_74LS151
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


module sysu_74LS151(
    input A0,A1,A2, S_n,D0,D1,D2,D3,D4,D5,D6,D7,
    output Q,Q_n
    );
    reg Q_r;
    wire [2:0]A;
    
    assign A = {A2,A1,A0};
    
    always@(*)begin
        if(S_n)
            Q_r <= 1'b0;
        else
            case(A)
                3'b000: Q_r <= D0;
                3'b001: Q_r <= D1;
                3'b010: Q_r <= D2;
                3'b011: Q_r <= D3;
                3'b100: Q_r <= D4;
                3'b101: Q_r <= D5;
                3'b110: Q_r <= D6;
                3'b111: Q_r <= D7;
            endcase
    end
        
    assign Q = Q_r;
    assign Q_n = ~Q;
    
endmodule
