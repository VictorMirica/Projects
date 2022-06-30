`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 07:46:08 PM
// Design Name: 
// Module Name: simulare
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


module simulare( );
    reg[31:0] number1, number2;
    reg clear, clk, load, op;
    wire[31:0] result;
    
    always #5 clk = ~clk;
    
    top_level top(number1, number2, clear, clk, load, op, result);
    
    initial begin
       number1 = 32'b01000000011100000000000000000000; 
        number2 = 32'b01000000111001000000000000000000;
        op = 0; clear = 0; clk = 1; load = 1;
        #100 op = 1;
        #100 op = 0;
        number2 = 32'b11000000111001000000000000000000;
        #100 op = 1;
        #100 number1 = 32'b11000000011100000000000000000000;
        number2 = 32'b01000000111001000000000000000000;
        op = 0;
        #100 op = 1;
        #100 op = 0;
        number2 = 32'b11000000111001000000000000000000;
        #100 op = 1;
    end
endmodule
