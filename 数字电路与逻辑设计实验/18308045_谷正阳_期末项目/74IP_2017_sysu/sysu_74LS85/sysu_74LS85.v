`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2020/12/07 09:00:41
// Design Name: 
// Module Name: sysu_74LS85
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


module sysu_74LS85(
input A0,A1,A2,A3,B0,B1,B2,B3,IAgB,IAeB,IAlB,
output QAgB,QAeB,QAlB
    );
    wire[3:0]A;
    wire[3:0]B;
    wire[2:0]I;
    reg [2:0]Q;
    assign A={A3,A2,A1,A0};
    assign B={B3,B2,B1,B0};
    assign I={IAgB,IAeB,IAlB};
    always @(*)
    begin
    if (A>B)
       Q<=3'b100;
       else if (A<B)
                Q<=3'b001;
             else if (I==3'b100)
                      Q<=3'b100;
                   else if (I==3'b010)
                            Q<=3'b010;
                         else if (I==3'b001)
                                  Q<=3'b001;   
                               else if (I==3'b000)
                                        Q<=3'b110;  
                                        else
                                            Q<=3'b000;
      end
      assign QAgB=Q[2];
      assign QAeB=Q[1];
      assign QAlB=Q[0];
endmodule
