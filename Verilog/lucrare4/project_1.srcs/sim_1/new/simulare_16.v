`timescale 1ns / 1ps

module simulare_16(
    );
    
    reg [15:0] A, B;
    reg c_in;
    wire [15:0] S, S2;
    wire c_out, c_out2;
    
    sum_16A sum(A, B, c_in, S, c_out);
    sum_16B sum2(A, B, c_in, S2, c_out2); 
    
    initial begin
        A = 10; B = 16; c_in = 0;
        #80 A = 20; B = 32;
        #80 A = 30; B = 40;
        #80 $finish;
    end
endmodule
