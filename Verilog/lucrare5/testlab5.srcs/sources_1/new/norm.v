`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/24/2021 07:43:41 PM
// Design Name: 
// Module Name: norm
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


module norm(inn, out1, out2);
    output [23:0] out1;
    output [8:0] out2;
    reg [23:0] out1;
    reg [8:0] out2;
    input[25:0] inn;
    
    always @(*)
        begin
           if(inn[25] == 1)
                begin
                    out1 = 0;
                    out2 = 0;
                end
           else if(inn[24] == 0)  
            //Fara overflow
                begin   
                    out1 = inn[23:0];
                    out2[7:0] = 0;
                    while(out1[22] == 0 && out1[22:0] != 0)
                        begin
                        out1[22:0]  = out1[22:0] << 1;
                        out2[7:0] = out2[7:0] + 1;
                        end
                    out1[23] = inn[23];
                    out2[8] <= 0;
                end
            else  
            //Overflow 
                begin
                    out1[23] = inn[23];
                    out1[22:0] <= {inn[24],inn[21:0]} >> 1;
                    out2[8] <= 1;
                    out2[7:0] <= 0;
                end 
            end 

endmodule
