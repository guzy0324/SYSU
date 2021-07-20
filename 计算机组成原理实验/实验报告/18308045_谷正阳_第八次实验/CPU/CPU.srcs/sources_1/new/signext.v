`timescale 1ns / 1ps
module signext( 
    input [15:0] inst, // 输入16位
    input imm_expand, //!SEXT
    output reg [31:0] data // 输出32位
); 
// 根据符号补充符号位
// 如果符号位为1，则补充16个1，即16'h ffff 
// 如果符号位为0，则补充16个0 
always @(*)
begin
    if (!imm_expand)
    begin
        data = inst[15:15]?{16'hffff,inst}:{16'h0000,inst}; 
    end
    // 0扩展
    else
    begin
        data = {16'h0000,inst};
    end
end    
endmodule 