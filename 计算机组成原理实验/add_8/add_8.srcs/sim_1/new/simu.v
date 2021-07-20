`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2019/11/05 22:22:18
// Design Name: 
// Module Name: simu
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

module simu(
    );
    // Inputs
        reg [7:0] A;
        reg [7:0] B;
        reg C0;
    // Outputs
        wire C8;
        wire [7:0] F;
    // Instantiate the Unit Under Test (UUT)
      add_8 uut 
               (.a(A), 
              .b(B), 
              .cin(C0), 
              .s(F),
              .co(C8)
                 );
     initial begin
            // Initialize Inputs
                    C0 = 0;
            // Wait 100 ns for global reset to finish
            #100;
    // Add stimulus here
        begin A = 'B10111100;B='B00101011;C0 = 0;end
            #100;
            begin A = 'B10101011;B='B00101101;C0 = 0;end
            #100;
        end
endmodule
