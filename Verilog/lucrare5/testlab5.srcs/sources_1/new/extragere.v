`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/26/2021 07:29:52 PM
// Design Name: 
// Module Name: extragere
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


module extragere(number1, number2, exp1, exp2, mant1, mant2);

    input [32:0] number1;
    input [32:0] number2;
    output [7:0] exp1;
    output [7:0] exp2;
    output [23:0] mant1;
    output [23:0] mant2;
    
    assign exp1[7:0] = number1[30:23];
    assign exp2[7:0] = number2[30:23];
    
    assign mant1[23] = number1[31];
    assign mant1[22:0] = number1[22:0];
    assign mant2[23] = number2[31];
    assign mant2[22:0] = number2[22:0];
endmodule
