DESIGN	= sail
GB3_ROOT = /gb3-resources

sail-nextpnr:
	mkdir -p $(GB3_ROOT)/build
	cp programs/data.hex verilog/
	cp programs/program.hex verilog/
	yosys $(GB3_ROOT)/processor/yscripts/$(DESIGN).ys > yosys.log
	nextpnr-ice40 --up5k --package uwg30 --json $(DESIGN).json --pcf pcf/$(DESIGN).pcf --asc $(DESIGN).asc --log device_util.log --pcf-allow-unconstrained
	icetime -p pcf/sail.pcf -P uwg30 -d up5k -t sail.asc
	icepack $(DESIGN).asc design.bin
	cp design.bin $(GB3_ROOT)/build/

clean:
	rm -f *.json *.blif *.asc *.bin
	rm -f programs/*.hex
	rm -f verilog/*.hex
