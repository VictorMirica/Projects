`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:49:18 PM
// Design Name: 
// Module Name: registru57
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


module registru57(inn, outt, clear, load, clk);
    output[56:0] outt;
    reg[56:0] outt;
    input[56:0] inn;
    input clear, load, clk;
    
    always @(posedge clk)
        if (clear)
            outt <= 0;
        else if (load)
            outt <= inn;
endmodule
