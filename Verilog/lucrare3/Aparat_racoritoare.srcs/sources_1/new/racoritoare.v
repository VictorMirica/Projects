`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2022 06:40:09 PM
// Design Name: 
// Module Name: racoritoare
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


module racoritoare(clk, reset, B1, B5, B10, rest ,doza);
    
    input clk, reset, B1, B5, B10;
    output rest, doza;
    reg [2:0] rest, doza;
    reg [2:0] currentState, nextState;
    
    always @(posedge clk)
    begin
        if (!reset) 
            begin
                currentState <= 3'b000;
            end
        else currentState <= nextState;
    end
    
    always @(currentState, B1, B5, B10)
        case({currentState, B1, B5, B10})
          6'b000_100: begin //se introduce un leu
            nextState <= 3'b001; rest = 3'b000; doza = 0;
            end
          6'b001_100: begin //se introduce un leu
            nextState <= 3'b010; rest = 3'b000; doza = 0;
            end
          6'b010_100: begin //se introduce un leu, nu exista rest
            nextState <= 3'b011; rest = 3'b000; doza = 0;
            end
          6'b011_000: begin //se da doza
            nextState <= 3'b000; rest = 3'b000; doza = 1;
            end
          6'b000_010: begin //se introduc 5 lei
            nextState <= 3'b100; rest = 3'b000; doza = 0;
            end
          6'b100_000: begin //se dau rest 2 lei
            nextState <= 3'b011; rest = 3'b010; doza = 0;
            end
          6'b000_001: begin //se introduc 10 lei
            nextState <= 3'b101; rest = 3'b000; doza = 0;
            end
          6'b101_000: begin //se dau rest 7 lei
            nextState <= 3'b011; rest = 3'b111; doza = 0;
            end
          default: begin
             nextState = currentState; doza = 0;
             end
    endcase
endmodule
