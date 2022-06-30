`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2022 06:39:46 PM
// Design Name: 
// Module Name: sum_16A
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


module sum_16A(
    input [15:0] A,
    input [15:0] B,
    input c_in,
    output [15:0] S,
    output c_out
    );
    
    wire [14:0] C0;
    
    FA fa_0(A[0], B[0], c_in, S[0], C0[0]);
    FA fa_1(A[1], B[1], C0[0], S[1], C0[1]);
    FA fa_2(A[2], B[2], C0[1], S[2], C0[2]);
    FA fa_3(A[3], B[3], C0[2], S[3], C0[3]);
    
    FA fa_4(A[4], B[4], C0[3], S[4], C0[4]);
    FA fa_5(A[5], B[5], C0[4], S[5], C0[5]);
    FA fa_6(A[6], B[6], C0[5], S[6], C0[6]);
    FA fa_7(A[7], B[7], C0[6], S[7], C0[7]);
    
    FA fa_8(A[8], B[8], C0[7], S[8], C0[8]);
    FA fa_9(A[9], B[9], C0[8], S[9], C0[9]);
    FA fa_10(A[10], B[10], C0[9], S[10], C0[10]);
    FA fa_11(A[11], B[11], C0[10], S[11], C0[11]);
    
    FA fa_12(A[12], B[12], C0[11], S[12], C0[12]);
    FA fa_13(A[13], B[13], C0[12], S[13], C0[13]);
    FA fa_14(A[14], B[14], C0[13], S[14], C0[14]);
    FA fa_15(A[15], B[15], C0[14], S[15], c_out);
endmodule
