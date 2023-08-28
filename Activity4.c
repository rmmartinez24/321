#include <stdio.h>
#include <stdbool.h>

int main(int argc, const char * argv[])
{
    int number = 0;
    bool ok = false;
    char bits[32] = 
    {
        '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0'
    };

    while(!ok)
    {
        printf("\nEnter a numbere between 0 through 1000: ");
        scanf ("%d", &number);

        if(number < 0 || number > 1000)
        {
            printf("Number needs to be between 0 through 1000\n");
        }
        else
        {
            ok = true;
        }
    }

    // Number displayed as a 32 bit binary number
    printf("The number in binary is: ");
    convertPrintBinary(number, &bits[0]);
    
    // Number as a 32 bit hexidecimal number
    printf("Number in Hexidecimal is: 0x%08X\n", number);

    //Shift number 10 bits to the left
    int result = ((number << 10) & 0xFFFFFC00) | 0x03FF;

    // Display results 
    printf("Decimal result is: ", result);
    printf("Hexidecimal result is: 0x%08X\n", result);
    printf("Binary result is: ");
    convertPrintBinary(result, &bits[0]);

    return 0;
}

void printBinary(char* bits)
{
    //print all binary bits 
    for (int i = 31; i >= 0; --i)
    {
        printf("%c", bits[i]);
    }
    printf("\n");
}

//clears all binary bits to 0
void clearBinaryBits(char* bits) 
{
    decimalToBinary(0, &bits[0]);
}

//converts number from decimal to binary 
/**
 * @param number decimal to convert
 * @param bits output array
*/
void conPrintBinary(int number, char* bits)
{
    clearBinaryBits(&bits[0]);
    decimalToBinary(number, &bits[0]);
    printBinary(&bits[0]);
}


/**
 * @param number of decimal to convert
 * @param bits output array
*/
void decToBinary(int number, char* bits)
{
    int index = 0;
    int result = number; 

    while(result !=0)
    {
        int remainder = result % 2;

        if (remainder > 0)
            bits[index] = '1';

        result = result/2;
        ++index;
    }
}
