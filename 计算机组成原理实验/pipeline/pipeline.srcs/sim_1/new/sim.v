`timescale 1ns / 1ps
module sim; 
reg clk;//100Mhz
reg reset;
wire [31:0] inst_if;//ָ��,�͸������data2
wire [31:0] alu_res_ex;//ALU����͸�data4
wire [31:0] Dout_mem;//memory����͸�data6,����ͼ���Data_in
wire [31:0] RtData_id;//�Ĵ����ѵ����B���͸�data5������ͼ���Data_out
wire [31:0] PC_out;//pc���͸�data7
wire MemRead_mem;
wire MemWrite_mem;
wire [31:0] alu_res_mem;
wire [31:0] RtData_mem;
// Instantiate the Unit Under Test (UUT) 
MipsPipelineCPU uut ( 
.clk(clk),
.reset(reset),
.inst_if(inst_if),
.alu_res_ex(alu_res_ex),
.Dout_mem(Dout_mem),
.RtData_id(RtData_id),
.PC_out(PC_out)
, .MemRead_mem(MemRead_mem),.MemWrite_mem(MemWrite_mem),.alu_res_mem(alu_res_mem),.RtData_mem(RtData_mem)
); 
initial begin 
// Initialize Inputs 
clk = 1; 
reset = 1; 
// Wait 100 ns for global reset to finish 
//#100;
#20; 
reset = 0; 
end 
parameter PERIOD = 20; 
always begin 
clk = 1'b1; 
#(PERIOD / 2) clk = 1'b0; 
#(PERIOD / 2) ; 
end 
endmodule 