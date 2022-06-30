`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:16:23 PM
// Design Name: 
// Module Name: compara
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


module compara(inn, out1, out2);
    output reg[15:0] out1;
    output reg[8:0] out2;
    input[15:0] inn;
    wire[7:0] exp1, exp2, diff;
    
    assign exp1 = inn[15:8];
    assign exp2 = inn[7:0];
    assign diff = exp1 - exp2;
    
    always @(*)
        if ($signed(diff) >= 0)
            begin
                //Primul exp e mai mare - se muta al doilea nr
                out2[8] <= 1;
                out2[7:0] <= diff;
                out1 <= inn;
            end
        else 
            begin
                //Invers - se muta primul nr
                out2[8] <= 0;
                out2[7:0] <= exp2 - exp1;
                out1 <= inn;
            end
    
endmodule
