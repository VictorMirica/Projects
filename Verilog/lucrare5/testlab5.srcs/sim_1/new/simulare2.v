`timescale 1ns / 1ps


module simulare2();

    reg[31:0] number1_0, number2_0;
    reg clear_0, clk_0, load_0, op_0;
    wire[31:0] result_0;
    
    always #5 clk_0 = ~clk_0;

    design_1_wrapper test(clear_0, clk_0, load_0, number1_0, number2_0, op_0, result_0);
    
    initial begin
        number1_0 = 32'b01000011111010110011100000010000; 
        number2_0 = 32'b01000011010101000001000001100010;
        op_0 = 0; clear_0 = 0; clk_0 = 1; load_0 = 1;
    end

    
endmodule
