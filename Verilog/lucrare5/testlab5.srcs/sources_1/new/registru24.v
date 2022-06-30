`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 08:09:22 PM
// Design Name: 
// Module Name: registru24
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


module registru24(inn, outt, clear, load, clk);
    output[23:0] outt;
    reg[23:0] outt;
    input[23:0] inn;
    input clear, load, clk;
    
    always @(posedge clk)
        if (clear)
            outt <= 0;
        else if (load)
            outt <= inn;
endmodule
