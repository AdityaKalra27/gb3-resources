/*

Finley Blaine 2025
Part of GB3 RISC-V Project

Implemented 2025-05-28

Initialization delay


*/

// Divide by 2N
module init_delay
    (input clk_in, output clk_out);

    reg [7:0] count;

    initial begin
        count = 8'b00000000;
    end

    always @ (posedge clk_in) begin
        // count from 0 to N-1
        if (count != 8'hFF) count <= count + 1;
    end

    assign clk_out = clk_in & (count == 8'hFF);
endmodule