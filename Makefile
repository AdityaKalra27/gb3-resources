.PHONY: \
	softwareblink \
	hardwareblink \
	bubblesort \
	stresstest \
	2025-competition-benchmark \
	clean

softwareblink:
	cd softwareblink; make clean; make; make install
	cd processor; make

hardwareblink:
	cd hardwareblink; make clean; make;

bubblesort:
	cd bubblesort; make clean; make; make install
	cd processor; make

stresstest:
	cd stresstest; make clean; make; make install
	cd processor; make

2025-competition-benchmark:
	cd 2025-competition-benchmark; make clean; make; make install
	cd processor; make

clean:
	cd softwareblink; make clean
	cd hardwareblink; make clean
	cd bubblesort; make clean
	cd processor; make clean
	rm -f build/*.bin
