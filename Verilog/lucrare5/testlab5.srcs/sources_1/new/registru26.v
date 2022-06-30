`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 08:01:55 PM
// Design Name: 
// Module Name: registru26
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


module registru26(inn, outt, clear, load, clk);
    output[25:0] outt;
    reg[25:0] outt;
    input[25:0] inn;
    input clear, load, clk;
    
    always @(posedge clk)
        if (clear)
            outt <= 0;
        else if (load)
            outt <= inn;
endmodule
