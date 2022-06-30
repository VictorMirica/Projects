`timescale 1ns / 1ps


module sum_4B(
    input [3:0] A,
    input [3:0] B,
    input c_in,
    output [3:0] S,
    output P,
    output G
    );
    
    wire [3:0] p, g;
    
    assign p = A | B;
    assign g = A & B;
    
    assign #5 P = p[3] & p[2] & p[1] & p[0];
    assign #5 G = g[3] + (p[3] & g[2]) + (p[3] & p[2] & g[1]) + (p[3] & p[2] & p[1] & g[0]);
    assign #5 S = A + B + c_in;
    
endmodule
