#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int vp1[0];
int vp2[0];
int vp3[0];
int pp1[0];
int pp2[0];

void binaryFromDecimal(int decimal, char* bits)
{
	int i = 0;
	int result = decimal;
	while (result != 0)
	{
		int remainder = result % 2;
		
		if (remainder > 0){
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
	for (int i = 0; i < 16; i++)
    {
		printf("%s", &bits[32-i]);
	}

	printf("\n");
}

void clearBits(char* bits)
{
	for (int i = 0; i < 32; i++)
    {
		bits[i] = '0';
	}
}

void convertAndPrintBinary(int number, char* bits)
{
	clearBits(&bits[0]);
	binaryFromDecimal(number, &bits[0]);
	printBinary(&bits[0]);
}

void createPages(int num)
{

	vp1[num];
	vp2[num];
	vp3[num];
	pp1[num];
	pp2[num];

	for (int i = 0; i < num; i++)
	{
		pp1[i] = num - i;
	}
	for (int i = 0; i < num; i++)
	{
		pp2[i] = i;
	}
	for (int i = 0; i < num; i++)
	{
		vp1[i] = num - i;
	}
	for (int i = 0; i < num; i++)
	{
		vp2[i] = i;
	}
	for (int i = 0; i < num; i++)
	{
		vp3[i] = i;
	}
	
}

int TLB(int virtualPage, int offset)
{
	int data;

	if (virtualPage == 1)
    {
		printf("Virtual page 1 translated to Physical Page 2 with offset of %d\n", offset);
		data = pp2[offset];
	}
	if (virtualPage == 2)
    {
		printf("Virtual page 2 translated to Physical Page 1 with offset of %d\n", offset);
		data = pp1[offset];
	}
	else
    {
		printf("Data not found. Must Search physical address ");
		data = 0;
	}
	
	return data;
}

int main(int argc, const char *argv[])
{
	char bits[16] = 
    {
        '0', '0', '0', '0', '0', 
        '0', '0', '0', '0', '0', 
        '0', '0', '0', '0', '0', 
        '0'
    };

    int num;
	bool improper = true;
	
	//Get Page Size
	printf("Enter a page size (4095 or 8191 reccomended)\n");
	scanf("%d", &num);
	
	//Converted to Binary
	printf("Page size of %d converted to binary: \n", num);
	convertAndPrintBinary(num, &bits[0]);
	
	//Converted to Hexidecimal
	printf("Page size converted to hexidecimal: 0x%08X\n", num);
	
	//Create pages of "num" space
	//2 physical and 2 virtual
	createPages(num);
	printf("Pages of %d size created\n", num);
	
	//Convert virtual to physical addresses
	
	printf("Searching for virtual page 1, offset 15 \n");
	printf("Data: %d\n", TLB(1, 15));
	
	printf("Searching for virtual page 1, offset 12 \n");
	printf("Data: %d\n", TLB(1, 12));
	
	printf("Searching for virtual page 2, offset 5 \n");
	printf("Data: %d\n", TLB(2, 55));
	
	printf("Searching for virtual page 2, offset 90 \n");
	printf("Data: %d\n", TLB(2, 90));
	
	printf("Searching for virtual page 1, offset 100 \n");
	printf("Data: %d\n", TLB(1, 100));
	

	return 0;
}