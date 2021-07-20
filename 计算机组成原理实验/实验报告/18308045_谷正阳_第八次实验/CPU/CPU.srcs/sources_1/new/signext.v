`timescale 1ns / 1ps
module signext( 
    input [15:0] inst, // ����16λ
    input imm_expand, //!SEXT
    output reg [31:0] data // ���32λ
); 
// ���ݷ��Ų������λ
// �������λΪ1���򲹳�16��1����16'h ffff 
// �������λΪ0���򲹳�16��0 
always @(*)
begin
    if (!imm_expand)
    begin
        data = inst[15:15]?{16'hffff,inst}:{16'h0000,inst}; 
    end
    // 0��չ
    else
    begin
        data = {16'h0000,inst};
    end
end    
endmodule 