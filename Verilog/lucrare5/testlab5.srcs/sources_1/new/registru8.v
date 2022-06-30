`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:57:14 PM
// Design Name: 
// Module Name: registru8
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


module registru8(inn, outt, clear, load, clk);
    output[7:0] outt;
    reg[7:0] outt;
    input[7:0] inn;
    input clear, load, clk;
    
    always @(posedge clk)
        if (clear)
            outt <= 0;
        else if (load)
            outt <= inn;
    
endmodule

