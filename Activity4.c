#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void binaryFromDecimal(int decimal, char* bits)
{
	int i = 0;
	int result = decimal;
	while (result != 0)
	{
		int remainder = result % 2;
		
		if (remainder > 0)
        {
			bits[i] = '1';
		}
		else{
			bits[i] = '0';
		}
		result = result / 2;
		i++;
	}
}
void printBinary(char* bits)
{
	for (int i = 0; i < 32; i++)
    {
		printf("%s", &bits[32-i]);
	}
	printf("\n");
}

void clearBits(char* bits)
{
	for (int i = 0; i < 32; i++){
		bits[i] = '0';
	}
}

void convertAndPrintBinary(int number, char* bits)
{
	clearBits(&bits[0]);
	binaryFromDecimal(number, &bits[0]);
	printBinary(&bits[0]);
}

int main(int argc, const char *argv[])
{
	int num;
    bool ok = false;
	char bits[32] = 
    {
        '0', '0', '0', '0', '0', '0', '0', '0', 
        '0', '0', '0', '0', '0', '0', '0', '0', 
        '0', '0', '0', '0', '0', '0', '0', '0', 
        '0', '0', '0', '0', '0', '0', '0', '0'
    };
	
	while (!ok)
    {
		printf("Enter a number from 0 to 1000...\n");
		scanf("%d", &num);
		if (num < 0 || num > 1000)
        {
			printf("Number needs to be between 0 and 1000\n");
		}
		else{
			ok = true;
		}
	}
	
	//number dispalyed as a 32 bit binary number
	printf("The number converted to binary: ");
	convertAndPrintBinary(num, &bits[0]);

    //number as a 32 bit hexidecimal
	printf("The number converted to hexidecimal: 0x%08X\n", num);
	
    //number shifts 10 bits to the left
	int result = ((num << 10) & 0xFFFFFc00) | 0x03FF;
	
	printf("Decimal result is: %d\n", result);
	printf("Hexadecimal result is: 0x%08X\n", result);
	printf("Binary result is: ");
    
	convertAndPrintBinary(result, &bits[0]);
}