`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:25:34 PM
// Design Name: 
// Module Name: aliniere
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


module aliniere(inn, outt);
    output [47:0] outt;
    reg [47:0] outt;
    input[56:0] inn;
    wire [7:0] diff;
    
    assign diff = inn[55:48];
    
    always @(*)
        if (inn[56] == 0)
            begin
            outt[23:0] <= inn[23:0];
            outt[47] <= inn[47];  
            outt[46:24] <= inn[46:24] >> diff; 
            end
        else 
            begin
            outt[23] <= inn[23];
            outt[22:0] <= inn[22:0] >> diff;
            outt[47:24] <= inn[47:24];
            end
    
endmodule
