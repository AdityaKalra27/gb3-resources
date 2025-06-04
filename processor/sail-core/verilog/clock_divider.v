/*

Finley Blaine 2025
Part of GB3 RISC-V Project

Implemented 2025-05-28

Clock Dividers


*/

// Divide by 2N
module clock_divider_2N
    #(parameter N = 4)
    (input clk_in, output clk_out);

    // Counter for divide by 2N (up to N=16)
    reg [3:0] count;

    // Initialize counter to zero
    initial begin
        count = 4'b0000;
    end

    always @ (posedge clk_in) begin
        // count from 0 to N-1
        if (count == N - 1) count <= 0;
        else count <= count + 1;

        // Toggle
        if (count == 0) clk_out <= ~clk_out;
    end
endmodule