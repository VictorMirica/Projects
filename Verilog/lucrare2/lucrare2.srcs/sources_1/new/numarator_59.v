`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/22/2022 07:03:59 PM
// Design Name: 
// Module Name: numarator_59
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


module numarator_59(
    input clk_out_led, reset, pauza,
    output reg carry_out,
    output reg [5:0]valoare_bin
    );
    
    always @(posedge clk_out_led)
        if (!reset)
            begin
                valoare_bin = 0;
                carry_out = 0;
            end 
        else if (!pauza)
            begin
                carry_out = 0;
                valoare_bin = valoare_bin + 1;
                if (valoare_bin == 60)
                    begin
                        valoare_bin = 0;
                        carry_out = 1;
                    end
            end
            
endmodule

