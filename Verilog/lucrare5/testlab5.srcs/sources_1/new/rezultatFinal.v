`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/26/2021 07:54:42 PM
// Design Name: 
// Module Name: rezultatFinal
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


module rezultatFinal(exponent, mantisa, result);

    input [7:0] exponent;
    input [23:0] mantisa;
    output [31:0] result;
    
    assign result[31] = mantisa[23];
    assign result[30:23] = exponent;
    assign result[22:0] = mantisa[22:0];
endmodule
