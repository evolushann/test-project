#include <stdio.h>

void convert(int, int);

int main() {
	int num;
	int base = 0;
	printf("Enter number to convert: ");
	scanf("%i", &num);

	do {
		printf("Enter base: ");
		scanf("%i", &base);
	} while(base > 30 || base < 2);
	
	printf("Converted number: ");
	convert(num, base);
	printf("\n");
	return 0;
}

void convert(int num, int base) {
	if(num < base) {
		if(num >= 10)
			printf("%c", num + 55);
		else
			printf("%c", num + 48);
	}

	else {
		convert(num/base, base);
		
		int rem = num%base;
		
		if(rem >= 10)
			printf("%c", rem + 55);
		else
			printf("%c", rem + 48);
	}
}