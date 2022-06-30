`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:21:26 PM
// Design Name: 
// Module Name: concatenare
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


module concatenare(inn, comp, outt);
    input[47:0] inn;
    input[8:0] comp;
    output[56:0] outt;
    reg[56:0] outt;
    
    always @(*)
        begin
            outt[56:48] <= comp[8:0];   
            outt[47:0] <= inn[47:0]; 
        end
endmodule
