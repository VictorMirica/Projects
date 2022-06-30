`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:28:53 PM
// Design Name: 
// Module Name: ajustare
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


module ajustare(exp, inn, outt);
    output reg[7:0] outt;
    input[7:0] exp;
    input[8:0] inn;
    wire[7:0] valoare;
    wire index;

    assign valoare = inn[7:0];
    assign index = inn[8];
    
    always @(*)
        if (index == 1)
            begin
            if (exp <= 8'b11111111)
                outt <= exp + 1;
            end
        else
            begin
            if (exp >= valoare)
                outt <= exp - valoare;
            end
endmodule
