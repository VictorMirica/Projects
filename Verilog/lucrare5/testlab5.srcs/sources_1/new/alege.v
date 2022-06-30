`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:24:25 PM
// Design Name: 
// Module Name: alege
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


module alege(inn, outt);
    output reg[7:0] outt;
    input[15:0] inn;
    wire[7:0] exp1, exp2;
    
    assign exp1 = inn[15:8];
    assign exp2 = inn[7:0];
    
    always @(*)
        if (exp1 > exp2)
            outt <= exp1;
        else 
            outt <= exp2;
endmodule
