`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/14/2022 07:26:36 PM
// Design Name: 
// Module Name: sum_16B
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


module sum_16B(
    input [15:0] A,
    input [15:0] B,
    input c_in,
    output [15:0] S,
    output c_out
    );
    
    wire P0, P1, P2, P3, G0, G1, G2, G3;
    wire C1, C2, C3;
    
    sum_4B sum_0(A[3:0], B[3:0], c_in, S[3:0], P0, G0);
    assign #5 C1 = G0 + (P0 & c_in);
    
    sum_4B sum_1(A[7:4], B[7:4], C1, S[7:4], P1, G1);
    assign #5 C2 = G1 + (P1 & G0) + (P1 & P0 & c_in);
    
    sum_4B sum_2(A[11:8], B[11:8], C2, S[11:8], P2, G2);
    assign #5 C3 = G2 +  (P2 & G1) + (P2 & P1 & G0) + (P2 & P1 & P0 & c_in);
    
    sum_4B sum_3(A[15:12], B[15:12], C3, S[15:12], P3, G3);
    assign #5 c_out = G3 + (P3 & G2) + (P3 & P2 & G1) + (P3 & P2 & P1 & G0) + (P3 & P2 & P1 & P0 & c_in);
endmodule
