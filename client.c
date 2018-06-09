//A sample client for intal.h

//Expected output for this client:
/*
First intal: 4999
Second intal: 2001
Two intals after increment and decrement:
5000
2000
Max of two intals: 5000
Sum: 7000
Diff: 3000
Product: 10000000
Quotient: 2
*/

#include <stdio.h>
#include "intal.h"

void main()
{
	char *str1 = "4999";
	char *str2 = "2001";

	void *intal1;
	void *intal2;
	void *sum;
	void *diff;
	void *product;
	void *quotient;

	intal1 = intal_create(str1);
	intal2 = intal_create(str2);

	printf("First intal: %s\n", intal2str(intal1)); //4999
	printf("Second intal: %s\n", intal2str(intal2)); //2001

	intal1 = intal_increment(intal1); //5000
	intal2 = intal_decrement(intal2); //2000

	printf("Two intals after increment and decrement:\n");
	printf("%s\n", intal2str(intal1)); //5000
	printf("%s\n", intal2str(intal2)); //2000

	printf("Max of two intals: %s\n", //5000
		(intal_compare(intal1, intal2) > 0) ? intal2str(intal1) : intal2str(intal2));

	sum = intal_add(intal1, intal2); //7000
	printf("Sum: %s\n", intal2str(sum));

	diff = intal_diff(intal1, intal2); //3000
	printf("Diff: %s\n", intal2str(diff));

	product = intal_multiply(intal1, intal2); //10000000
	printf("Product: %s\n", intal2str(product));

	quotient = intal_divide(intal1, intal2); //2
	printf("Quotient: %s\n", intal2str(quotient));


	//Make sure you destroy all the intals created.
	
	intal_destroy(quotient);
	intal_destroy(sum);
	intal_destroy(diff);
	intal_destroy(product);
	intal_destroy(intal1);	
	intal_destroy(intal2);
}
