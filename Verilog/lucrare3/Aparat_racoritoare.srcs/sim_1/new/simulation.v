`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2022 07:17:30 PM
// Design Name: 
// Module Name: simulation
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


module simulation();
    reg clk, reset, B1, B5, B10;
    wire doza;
    wire [2:0] rest;
    racoritoare r(clk, reset, B1, B5, B10, rest, doza);
    
    always #5 clk = !clk;
    
    initial begin
    #0 reset = 0; B1 = 0; B5 = 0; B10 = 0; clk = 0;
    #10 reset = 1; B1 = 1;
    #30 B1 = 0;
    #10 B5 = 1;
    #10 B5 = 0;
    #30 B10 = 1;
    #10 B10 = 0;
    #20 $finish;
    end   
        
endmodule
