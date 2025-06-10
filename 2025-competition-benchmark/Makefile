include /f-of-e-tools/tools/sunflower/conf/setup.conf

GB3_ROOT ?= /gb3-resources
SRFILE    := 2025-competition-benchmark.sr
SREC2HEX  ?= srec2hex
HEXFILES  := program.hex data.hex

.PHONY: all install clean

all: $(HEXFILES)

$(HEXFILES): $(SRFILE)
	$(SREC2HEX) -b 4096 $(SRFILE)

install: all
	mkdir -p $(GB3_ROOT)/processor/programs/
	cp $(HEXFILES) $(GB3_ROOT)/processor/programs/

clean:
	$(RM) $(HEXFILES)
