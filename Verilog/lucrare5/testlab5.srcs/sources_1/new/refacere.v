`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/26/2021 07:38:16 PM
// Design Name: 
// Module Name: refacere
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


module refacere(exp1, exp2, mant1, mant2, mantise, exponenti);

    input [7:0] exp1, exp2;
    input [23:0] mant1, mant2;
    output [15:0] exponenti;
    output [47:0] mantise;
    
    assign exponenti[15:8] = exp1;
    assign exponenti[7:0] = exp2;
    
    assign mantise[47:24] = mant1;
    assign mantise[23:0] = mant2;
    
    
endmodule
