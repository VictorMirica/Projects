`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2021 07:26:16 PM
// Design Name: 
// Module Name: adun_scad
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


module adun_scad(inn, op, outt);
    output reg[25:0] outt;
    input[47:0] inn;
    input op;
    reg[25:0] tmp;
    reg[22:0] mant1, mant2;
    reg sign1, sign2;
    
    always @(*)
        begin
        mant1 = inn[46:24];
        mant2 = inn[22:0];
        sign1 = inn[47];
        sign2 = inn[23];
        if (op == 1)
            // scadere
            begin
            if (sign1 == 1)
                if (sign2 == 1)
                    begin
                    if (mant1 >= mant2)
                        // -30 - (-10) = 10 - 30 = -(30 - 10)
                        begin
                        outt[23:0] = {1'b0, mant1} - {1'b0, mant2};
                        outt[24] = outt[23];
                        outt[23] = 1;   
                        end 
                    else
                        // -10 - (-30) = 30 - 10
                        begin
                        outt[23:0] = {1'b0, mant2} - {1'b0, mant1};
                        outt[24] = outt[23];
                        outt[23] = 0;
                        end
                    end
                else
                    // -30 - 10 = - (30 + 10)
                    begin
                    outt[23:0] = {1'b0, mant1} + {1'b0, mant2};
                    outt[24] = outt[23];
                    outt[23] = 1;
                    end
            else
                begin
                if (sign2 == 1)
                    // 10 - (-30) = 10 + 30
                    begin
                    outt[23:0] = {1'b0, mant1} + {1'b0, mant2};
                    outt[24] = outt[23];
                    outt[23] = 0;
                    end
                else
                    begin
                    if (mant1 >= mant2)
                        // 30 - 10
                        begin
                        outt[23:0] = {1'b0, mant1} - {1'b0, mant2};
                        outt[24] = outt[23];
                        outt[23] = 0;
                        end
                    else
                        // 10 - 30 = - (30 - 10)
                        begin
                        outt[23:0] = {1'b0, mant2} - {1'b0, mant1};
                        outt[24] = outt[23];
                        outt[23] = 1;
                        end
                    end
                end
            end
        else
            // adunare
            begin
            if (sign1 == 1)
                begin
                if (sign2 == 1)
                    // -30 + (-10) = - (30 + 10)
                    begin
                    outt[23:0] = {1'b0, mant1} + {1'b0, mant2};
                    outt[24] = outt[23];
                    outt[23] = 1;
                    end
                else
                    begin
                    if (mant1 >= mant2)
                        // -30 + 10 = -(30 - 10)
                        begin
                        outt[23:0] = {1'b0, mant1} - {1'b0, mant2};
                        outt[24] = outt[23];
                        outt[23] = 1;
                        end
                    else
                        // -10 + 30 = (30 - 10)
                        begin
                        outt[23:0] = {1'b0, mant2} - {1'b0, mant1};
                        outt[24] = outt[23];
                        outt[23] = 0;
                        end
                    end
                end
            else
                begin
                if (sign2 == 1)
                    begin
                    if (mant1 >= mant2)
                        // 30 + (-10) = 30 - 10
                        begin
                        outt[23:0] = {1'b0, mant1} - {1'b0, mant2};
                        outt[24] = outt[23];
                        outt[23] = 0;
                        end
                    else
                        // 10 + (-30) = - (30 - 10)
                        begin
                        outt[23] = 1;
                        outt[22:0] = mant2 - mant1;
                        outt[24] = outt[23];
                        end
                    end
               else
                   // 30 + 10
                   outt[23:0] = {1'b0, mant1} + {1'b0, mant2};
                   outt[24] = outt[23];
                   outt[23] = 0;
               end
            end
        if ({outt[24], outt[22:0]} == 0)
            outt[25] = 1;
        else
            outt[25] = 0;
        end
endmodule
