#include "devscc.h"
#include "sf-types.h"
#include "sh7708.h"

#include "e-types.h"

// Program to test all instructions

#define CYCLES_MULT 200000

#define LED_ON *(volatile unsigned int*)0x2000=0xFF
#define LED_OFF *(volatile unsigned int*)0x2000=0x00

// inline void led_on() {
// 	*gDebugLedsMemoryMappedRegister = 0xFF;
// }

// inline void led_off() {
// 	*gDebugLedsMemoryMappedRegister = 0x00;
// }

void delay_u(int units) {
	int loops = units * CYCLES_MULT;
	volatile int decoy = 0;
	for (int i = 0; i < loops; ++i) {	
		decoy = 1;
	}
}

// typedef enum {
// 	M_Dot,
// 	M_Dash,
// 	M_End
// } Morse_Symbols;

// void morse(const char* pattern) {
// 	for (int i = 0; pattern[i] != M_End; ++i) {
// 		if (pattern[i] == M_Dot) {
// 			LED_ON;
// 			delay_u(1);
// 			LED_OFF;
// 			delay_u(1);
// 		}
// 		else if (pattern[i] == M_Dash) {
// 			LED_ON;
// 			delay_u(2);
// 			LED_OFF;
// 			delay_u(2);
// 		}
// 	}
// }

// Error
// For some reason looped approach doesn't work, here's a hard coded approach
void SOS(int error_code) {
	// const char SOS_pattern[] = {M_Dot, M_Dot, M_Dot, M_Dash, M_Dash, M_Dash, M_Dot, M_Dot, M_Dot, M_End};

	while(1) {
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);
		LED_ON;
		delay_u(2);
		LED_OFF;
		delay_u(2);
		LED_ON;
		delay_u(2);
		LED_OFF;
		delay_u(2);
		LED_ON;
		delay_u(2);
		LED_OFF;
		delay_u(2);
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);

		// morse(SOS_pattern);

		
		delay_u(6);

		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(1);

		for (int i = 7; i >= 0; --i) {
			if (error_code & 1 << i) {
				LED_ON;
			}
			delay_u(3);
			LED_OFF;
			delay_u(1);
		}

		LED_ON;
		delay_u(1);
		LED_OFF;
		
		delay_u(10);
	}
}

void Success() {
	while (1) {
		LED_ON;
		delay_u(1);
		LED_OFF;
		delay_u(9);
	}
}

int main(void) {
	// Success();
	// SOS();

	//----------ARITHMETIC TESTS----------//

	volatile register int testreg1 = 100;
	volatile register int testreg2 = 90;
	volatile register int testreg3 = 80;

	// Test ADDI
	// Sets testreg1 to 5
	__asm("addi %0, zero, 5": "=r" (testreg1));

	// Test ADD
	// Adds testreg1 testreg2 and assigns to testreg1
	// testreg1 <= 95
	__asm("add %0, %0, %1": "+r" (testreg1): "r" (testreg2));

	// Test SUB
	// Subtracts testreg3 from testreg1 and assigns to testreg2
	// testreg2 <= 15
	__asm("sub %0, %1, %2": "=r" (testreg2): "r" (testreg1), "r" (testreg3));

	if (testreg2 != 15) SOS(1); // ERROR CODE 1

	//----------BITWISE TESTS----------//

	testreg1 = 0xADADADAD; // 0b10101101 times 4
	testreg2 = 0xBEBEBEBE; // 0b10111110 times 4
	testreg3 = 0x00000000;

	// Test AND
	// Ands testreg1 and testreg2 => testreg3
	// testreg3 <= 0xACACACAC
	__asm("and %0, %1, %2": "=r" (testreg3): "r" (testreg1), "r" (testreg2));

	if (testreg3 != 0xACACACAC) SOS(2); // ERROR CODE 2

	// Test ANDI
	// Ands testreg1 and 0xFE
	// Immediate value is 12 bit sign extended so
	// testreg3 <= 0x000000AC
	__asm("andi %0, %1, 0x0FE": "=r" (testreg3): "r" (testreg1));

	if (testreg3 != 0x000000AC) SOS(3); // ERROR CODE 3

	// Test OR
	// Ors testreg1 and testreg2 => testreg3
	// testreg3 <= 0xBFBFBFBF
	__asm("or %0, %1, %2": "=r" (testreg3): "r" (testreg1), "r" (testreg2));

	if (testreg3 != 0xBFBFBFBF) SOS(4); // ERROR CODE 4

	// Test ORI
	// Ors testreg1 and 0xFE
	// Immediate value is 12 bit sign extended so
	// testreg3 <= 0x000000FE
	__asm("ori %0, %1, 0x0FE": "=r" (testreg3): "r" (testreg2));

	if (testreg3 != 0xBEBEBEFE) SOS(5); // ERROR CODE 5

	// Test XOR
	// Xors testreg1 and testreg2 => testreg3
	// testreg3 <= 0x13131313
	__asm("xor %0, %1, %2": "=r" (testreg3): "r" (testreg1), "r" (testreg2));

	if (testreg3 != 0x13131313) SOS(6); // ERROR CODE 6

	// Test XORI
	// Xors testreg1 and 0xBE
	// Immediate value is 12 bit sign extended so
	// testreg3 <= 0xADADAD13
	__asm("xori %0, %1, 0x0BE": "=r" (testreg3): "r" (testreg1));

	if (testreg3 != 0xADADAD13) SOS(7); // ERROR CODE 7

	//----------SHIFT TESTS----------//

	testreg1 = 0xADADADAD; // 0b10101101 times 4
	testreg2 = 7;
	testreg3 = 0x00000000;

	// Test SLL and SLLI
	// Logically shfits left by 7 and 9 bits respectively
	// testreg3 <= 0xADAD0000
	__asm("sll %0, %1, %2\n"
	"slli %0, %0, 9\n"
	: "+r" (testreg3): "r" (testreg1), "r" (testreg2));

	if (testreg3 != 0xADAD0000) SOS(8); // ERROR CODE 8

	// Test SRL and SRLI
	// Logically shifts right by 7 and 9 bits respectively
	// testreg3 <= 0x0000ADAD
	__asm("srl %0, %1, %2\n"
		"srli %0, %0, 9\n"
		: "+r" (testreg3): "r" (testreg1), "r" (testreg2));

	if (testreg3 != 0x0000ADAD) SOS(9); // ERROR CODE 9

	// Test SRA and SRAI
	// Arithmetically shifts right by 7 and 9 bits respectively
	// testreg3 <= 0xFFFFADAD
	__asm("sra %0, %1, %2\n"
	"srai %0, %0, 9\n"
	: "+r" (testreg3): "r" (testreg1), "r" (testreg2));

	if (testreg3 != 0xFFFFADAD) SOS(10); // ERROR CODE 10

	//----------LOAD IMMEDIATE TESTS----------//
	// Exclude AUIPC as it's basically a jump instruction

	// Test LUI
	__asm("lui %0, 12345": "=r" (testreg3));

	if (testreg3 != 50565120) SOS(11); // ERROR CODE 11

	//----------LOAD AND STORE TESTS----------//

	volatile int testmem1 = 0x67676767;
	volatile int testmem2 = 0;
	testreg2 = (int)&testmem1;
	testreg3 = (int)&testmem2;

	// Test LW and SW
	// Loads word located in testmem1 into testreg1
	// Then stores into testmem2
	__asm("lw %0, 0(%1)\n"
		"sw %0, 0(%2)"
		: "=r" (testreg1): "r" (testreg2), "r" (testreg3));

	if (testmem2 != 0x67676767) SOS(12); // ERROR CODE 12

	testmem1 = 0x68686868;

	// Test LH and SH
	// Loads word located in testmem1 into testreg1
	// Then stores into testmem2
	__asm("lh %0, 0(%1)\n"
		"sh %0, 2(%2)"
		: "=r" (testreg1): "r" (testreg2), "r" (testreg3));

	if (testmem2 != 0x68686767) SOS(13); // ERROR CODE 13

	// Test LB and SB
	// Loads word located in testmem1 into testreg1
	// Then stores into testmem2
	__asm("lb %0, 0(%1)\n"
		"sb %0, 1(%2)"
		: "=r" (testreg1): "r" (testreg2), "r" (testreg3));

	if (testmem2 != 0x68686867) SOS(14); // ERROR CODE 14

	Success();

	while (1) {
	}

	return 0;
}