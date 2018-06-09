/*
Functions List.
1.  void intal_destroy(void* intal);
2.  void* intal_create(const char* str);
3.  char* intal2str(void* intal);
4.  int intal_compare(void* intal1, void* intal2);
5.  void* intal_increment(void* intal);
6.  void* intal_decrement(void* intal);
7.  void* intal_add(void* intal1, void* intal2);
8.  void* intal_diff(void* intal1, void* intal2);
9.  void* intal_multiply(void* intal1, void* intal2);
10. void* intal_divide(void* intal1, void* intal2);
11. void* intal_pow(void* intal1, void* intal2);

//what data structure??
//maybe many data structures for different functions??

//How To Start?

/*
Data Type             Memory (bytes)          Range                      Format Specifier
short int                   2          -32,768 to 32,767                       %hd
unsigned short int          2           0 to 65,535                            %hu
unsigned int                4           0 to 4,294,967,295                     %u
int                         4          -2,147,483,648 to 2,147,483,647         %d
long int                    4          -2,147,483,648 to 2,147,483,647         %ld
unsigned long int           4           0 to 4,294,967,295                     %lu
long long int               8          -(2^63) to (2^63)-1                     %lld
unsigned long long int      8           0 to 18,446,744,073,709,551,615        %llu
signed char                 1          -128 to 127                             %c 
unsigned char               1           0 to 255                               %c
float                       4                                                  %f
double                      8                                                  %lf
long double                 12                                                 %Lf
*/


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//importing Header Files
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


//Data Structure Used.
struct number
{
	signed long long int x;						//to store certain part of the number
	unsigned long int e;						//to indicate the power of 4.
	char c;										//to check if this is the last part of the number.
};








//Destroy Intal.
void intal_destroy(void *intal)
{
	if(intal == NULL) return;
	free(intal);
}












//To convert interger to a string.
char* itoaDUBLI(int value, char *result, int base)
{
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

//To String Function
//Just a function to specify the data type, because void* does not detect structures.
char* intaltostrDUBLI(struct number *intal)
{
	if(intal == NULL)
	{
		char *s = (char*)malloc(sizeof(char)*4);
		s[0] = 'N';
		s[1] = 'a';
		s[2] = 'N';
		s[3] = '\0';
		return s;
	}

	int count = 0;
	while(1)									//get length of structure array.
		if(intal[count++].c == '1') break;

	char *s = (char*)malloc((count*4 + 1)*sizeof(char));
	s[0] = '\0';
	char temp[5];
	temp[4] = '\0';

	for(int i = count-1; i >= 0; --i)
	{
		itoaDUBLI(intal[i].x, temp, 10);
		//printf("number:%d\n", intal[i].x);
		//printf("%d\n", strlen(temp));
		if(i != (count-1) && strlen(temp) != 4)
		{
			int n = 4;
			int x = n-strlen(temp);
			for(int j = 1; j <= x; ++j)
				for(int i = n-1; i > 0; --i)
				{
					temp[i] = temp[i-1];
				}
			for(int i = 0; i < x; ++i)
				temp[i] = '0';
		}
		strcat(s, temp);
	}

	//Trim Zeros:
	int i, len = strlen(s);
	for(i = 0; i < len-1; ++i)
	{
		if(s[i] != '0') break;
	}

	if(i != 0)
	{
		for(int j = i; j <= len; ++j)
			s[j-i] = s[j];
	}

	s = (char*)realloc(s, sizeof(char)*strlen(s));

	return s;
}

char* intal2str(void *intal)
{
	return intaltostrDUBLI(intal);
}













//Compare Function
int intal_compare(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL) return 0;

	void *a = intal2str(intal1);
	void *b = intal2str(intal2);

	if(strlen(a) > strlen(b)) return 1;
	if(strlen(a) < strlen(b)) return -1;

	int x = strcmp(a, b);

	if(x < 0) return -1;
	else if(x > 0) return 1;
	else return 0;
}















//Create Function
void* intal_create(const char* str)
{
	if(str == NULL || str[0] == '\0') return NULL;

	char buff[strlen(str)+1];
	int z;
	for(z = 0; z < strlen(str)-1; ++z)
		if(str[z] != '0') break;

	int index = 0;
	for(int i = z; i < strlen(str); ++i)
		buff[index++] = str[i];
	buff[index] = '\0';

	int n = index;				//get length of the string.

	int count = 0;
	for(int i = n-1; i >= 0; i = i-4) ++count;	//get length of array if each block consists of 4 digit long numbers at max.

	struct number *intal = (struct number*)malloc(count * sizeof(struct number));

	//Set the Default Values.
	for(int i = 0; i < count-1; ++i)
	{
		intal[i].c = '0';
		intal[i].e = i;
	}
	intal[count-1].e = (count-1);
	intal[count -1].c = '1';

	if(n%4 == 0)
	{
		/*
		This is wrong because of reverse order.
		int m = 0, j = 0;
		char a[5];
		for(int i = 0; i < n; ++i)
		{
			a[m++] = str[i];
			if(m == 4)
			{
				a[4] = '\0';
				intal[j++].x = atoi(a);
				m = 0;
				
			}
		}*/

		int m, i, k = 0;
		char a[5]; a[4] = '\0';
		for(i = n-4; i >= 0; i = i-4)
		{
			m = 0;
			//for(int j = 0; j < 5; ++j)	a[j] = '\0';
			for(int j = 0; j < 4; ++j)
				a[m++] = buff[i+j];

			intal[k].e = k;
			intal[k++].x = atoi(a);
		}
	}
	else
	{
		int m, i, k = 0;
		char a[5];
		for(i = n-4; i >= 0; i = i-4)
		{
			m = 0;
			for(int j = 0; j < 5; ++j)	a[j] = '\0';
			for(int j = 0; j < 4; ++j)
				a[m++] = buff[i+j];

			intal[k].e = k;
			intal[k++].x = atoi(a);
		}

		m = 0;
		for(int j = 0; j < 5; ++j)	a[j] = '\0';
		for(int c = 0; c < i+4; ++c)
				a[m++] = buff[c];

		intal[k].e = k;
		intal[k++].x = atoi(a);
	}

	return intal;
}























//Increment Function
void* intalincrementDUBLI(struct number *intal)
{
	if(intal == NULL) return intal;

	int count = 0;
	while(1)
		if(intal[count++].c == '1') break;

	int carry = 1;
	for(int i = 0; i < count; ++i)
	{
		intal[i].x += carry;
		if((intal[i].x/10000) == 0)
		{
			carry = 0;
			break;
		}
		else
		{
			intal[i].x = intal[i].x % 10000;
		}
	}
	if(carry == 1)
	{
		intal = (struct number*)realloc(intal, sizeof(struct number)*(count+1));
		intal[count-1].c = '0';
		intal[count].c = '1';
		intal[count].e = count;
		intal[count].x = carry;
	}

	return intal;
}

void* intal_increment(void *intal)
{
	if(intal == NULL) return NULL;
	return intalincrementDUBLI(intal);
}






















//Decrement Function
void* intaldecrementDUBLI(struct number *intal)
{
	int count = 0;
	while(1)
		if(intal[count++].c == '1') break;

	if(count == 1 && intal[0].x == 0) return intal;
	if(count == 1)
	{
		intal[0].x -= 1;
		return intal;
	}

	char *str = intal2str(intal);
	int i, len = strlen(str);

	for(i = len-1; i >= 0; --i)
		if(str[i] != '0') break;

	str[i] = ((str[i] - '0') - 1) + '0';
	for(int j = i+1; j < len; ++j)
		str[j] = '9';

	free(intal);
	//printf("string in dec is: %s", str);
	intal = intal_create(str);
	free(str);

	return intal;
}

void* intal_decrement(void* intal)
{
	if(intal2str(intal) == NULL) return intal;
	return intaldecrementDUBLI(intal);
}























//Add Function
void* intaladdDUBLI(struct number *intal1, struct number *intal2)
{
	int count1 = 0, count2 = 0;
	while(1)
		if(intal1[count1++].c == '1') break;
	while(1)
		if(intal2[count2++].c == '1') break;

	int count = (count1 < count2)? count1: count2;
	int x = ((count1 > count2)? count1: count2)+1;

	struct number *sum = (struct number*)malloc(sizeof(struct number)*x);
	for(int j = 0; j < x-1; ++j)
	{
		sum[j].e = j;
		sum[j].c = '0';
	}
	sum[x-1].e = x-1;
	sum[x-1].c = '1';

	int i, carry = 0;
	for(i = 0; i < count; ++i)
	{
		sum[i].x = intal1[i].x + intal2[i].x + carry;
		//printf("loop%d : %ld\n", i, sum[i].x);
		if((sum[i].x/10000) != 0)
		{
			carry = 1;
			sum[i].x %= 10000;
			//printf("loop%d : %ld\n", i, sum[i].x);
		}
		else carry = 0;
	}

	struct number *p;
	if(count == count1) p = intal2;
	else p = intal1;

	for(int j = count; j < x-1; ++j)
	{
		sum[j].x = p[j].x + carry;
		if(sum[j].x/10000 == 0)
		{
			carry = 0;
		}
		else
		{
			sum[j].x %= 10000;
			carry = 1;
		}
	}
	if(carry == 1)
		sum[x].x = 1;
	else
	{
		//sum = (struct number*)realloc(sum, sizeof(struct number)*(x-1));
		sum[x-2].c = '1';
	}

	return sum;
}

void* intal_add(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL) return NULL;
	return intaladdDUBLI(intal1, intal2);
}




























//Difference Function.
void* intaldiffDUBLI(struct number *intal1, struct number *intal2)
{
	int count1 = 0, count2 = 0;
	while(1)
		if(intal1[count1++].c == '1') break;
	while(1)
		if(intal2[count2++].c == '1') break;

	int count = (count1 < count2)? count1: count2;
	int x = ((count1 > count2)? count1: count2);

	struct number *p1, *p2;
	if(count == count1)
	{
		p1 = intal2;
		p2 = intal1;
	}
	else
	{
		p1 = intal1;
		p2 = intal2;
	}

	if(count1 == count2)
	{
		int z = intal_compare(intal1, intal2);
		if(z > 0)
		{
			p1 = intal1;
			p2 = intal2;
		}
		else if(z < 0)
		{
			p1 = intal2;
			p2 = intal1;
		}
		else
			return intal_create("0");
	}

	struct number *diff = (struct number*)malloc(sizeof(struct number)*x);
	for(int j = 0; j < x-1; ++j)
	{
		diff[j].e = j;
		diff[j].c = '0';
	}
	diff[x-1].e = x-1;
	diff[x-1].c = '1';

	int borrow = 0;

	//printf("intal1: %s\nintal2: %s\ncount: %d\nx: %d\n", intal2str(p1), intal2str(p2), count, x);

	for(int i = 0; i < count; ++i)
	{
		diff[i].x = p1[i].x - p2[i].x - borrow;
		//printf("diff%d: %lld\n", i, diff[i].x);

		if(diff[i].x < 0)
		{
			diff[i].x += 10000;
			borrow = 1;		
			//printf("diff%d: %lld\n", i, diff[i].x);
		}
		else
			borrow = 0;
	}

	int i;
	for(i = count; i < x; ++i)
	{
		diff[i].x = p1[i].x - borrow;

		if(diff[i].x < 0)
		{
			diff[i].x += 10000;
			borrow = 1;
		}
		else
			borrow = 0;
	}

	/*char *str = intal2str(diff);
	free(diff);
	diff = intal_create(str);
	free(str);*/

	if(diff[x-1].x == 0)
	{
		diff[x-2].c = '1';
		diff = (struct number*)realloc(diff, (x-1)*sizeof(struct number));
	}

	return diff;
}

void* intal_diff(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL) return NULL;
	return intaldiffDUBLI(intal1, intal2);
}
































//Divide Function.
struct number* intaldivideDUBLI(struct number *x, struct number *y)
{
	
	char *intal1 = intal2str(x);
	char *intal2 = intal2str(y);

	int len1 = strlen(intal1);
	int len2 = strlen(intal2);

	char q[len1+1];
	int qindex = 0;

	char temp[len1+1];
	temp[0] = '0';
	temp[1] = '\0';

	if(intal_compare(y, intal_create(temp)) == 0) return NULL;

	int flag, res, j, i = 0;
	while(i < len1)
	{
		//printf("Loop%d\n", qindex);
		j = 0;
		while(j < len2 && (i+j)<len1)
		{
			char character[2] = {intal1[i+j], '\0'};
			strcat(temp, character);
			++j;
			//printf("loop%d: %s\n", j, temp);
			void *a = intal_create(temp);
			if(intal_compare(a, y) >= 0)
			{
				free(a);
				break;
			}
			//printf("loop%d: %s\n", j, temp);
			q[qindex++] = '0';
		}

		if((i+j-1) >= len1 && j != len2)
		{
			//q[qindex++] = '0';
			break;
		}

		//printf("%s\n", temp);
		res  = 0;
		void *c;
		while(1)
		{
			c = intal_create(temp);
			int z = intal_compare(c, y);
			//printf("z :%d\t", z);
			if(z > 0)
			{
				flag = strlen(temp);
				void *x = intal_diff(c, y);
				char *k = intal2str(x);
				strcpy(temp, k);
				temp[flag] = '\0';
				free(x);
				free(c);
				free(k);
				++res;
				//printf("%d %s\n", res, temp);
			}
			else if(intal_compare(c, y) == 0)
			{
				temp[0] = '0';
				temp[1] = '\0';
				++res;
				free(c);
				break;
			}
			else
			{
				//printf("quit at %s:", intal2str(c));
				free(c);
				break;
			}
		}

		if(res != 0) q[qindex++] = res + '0';
		q[qindex] = '\0';
		//printf("res: %d\nQuoi: %s\n", res, q);

		i = i + j;
	}

	q[qindex] = '\0';
	//printf("answer: %s", q);
	void *ans =  intal_create(q);

	return ans;
}

void* intal_divide(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL) return NULL;
	return intaldivideDUBLI(intal1, intal2);
}























//Multiply Function.
void addforkarat(struct number **sum, struct number *a)
{
	struct number *x = intal_add(*sum, a);
	free(*sum);
	*sum = x;
}

void* bottomupkarat(struct number *a1, struct number *a2, struct number *b1, struct number *b2)
{
	long long int p1 = (a1->x)*(b1->x);
	unsigned long int  ep1 = ((a1->e) + (b1->e))*4;

	long long int p2 = (a2->x)*(b2->x);
	unsigned long int  ep2 = ((a2->e) + (b2->e))*4;

	unsigned long int ep3 = ((a1->e) + (b2->e))*4;
	long long int p3 = ((a1->x) + (a2->x)) * ((b1->x)+(b2->x));

	long long int x = p3 -p2 -p1;

	//printf("exp b1:%lu\nexp b2:%lu\n", b1->e, b2->e);
	//printf("p1:%lld	p2:%lld	p3:%lld	x:%lld\n", p1, p2, p3, x);

	char s1[10+ep1+1];
	char s2[10+ep2+1];
	char s3[10+ep3+1];

	s1[10+ep1] = '\0';
	s2[10+ep2] = '\0';
	s3[10+ep3] = '\0';

	itoaDUBLI(p1, s1, 10);
	itoaDUBLI(p2, s2, 10);
	itoaDUBLI(x, s3, 10);

	//printf("term1: %s\nterm2: %s\nterm3: %s\n", s1, s2, s3);
	//printf("ep1: %lu	ep2:%lu	ep3:%lu\n", ep1, ep2, ep3);

	char append1[ep1+1];
	char append2[ep2+1];
	char append3[ep3+1];
	for(int i = 0; i < ep1; ++i) append1[i] = '0';
	for(int i = 0; i < ep2; ++i) append2[i] = '0';
	for(int i = 0; i < ep3; ++i) append3[i] = '0';
	append1[ep1] = '\0';
	append2[ep2] = '\0';
	append3[ep3] = '\0';

	strcat(s1, append1);
	strcat(s2, append2);
	strcat(s3, append3);

	//printf("term1: %s\nterm2: %s\nterm3: %s\n", s1, s2, s3);

	void *n1 = intal_create(s1);
	void *n2 = intal_create(s2);
	void *n3 = intal_create(s3);

	//printf("n1:%s\nn2:%s\nn3:%s\n", intal2str(n1), intal2str(n2), intal2str(n3));
	
	void *xyz = intal_add(n1, n2);
	void *sum = intal_add(xyz, n3);

	//printf("xyz:%s\nsum:%s\n", intal2str(xyz), intal2str(sum));

	free(n1);
	free(n2);
	free(n3);
	free(xyz);

	return sum;
}

void* bottomupmultiplyusingkarat(struct number *intal1, struct number *intal2)
{
	int count1 = 0, count2 = 0;
	while(1)
		if(intal1[count1++].c == '1') break;
	while(1)
		if(intal2[count2++].c == '1') break;

	//printf("count1: %d\ncount2: %d\n", count1, count2);
	struct number *x = (struct number*)malloc((count1)*sizeof(struct number));
	struct number *y = (struct number*)malloc((count2)*sizeof(struct number));

	for(int i = 0; i < count1; ++i)
	{
		x[i].x = intal1[i].x;
		x[i].e = i;
		x[i].c = intal1[i].c;
	}

	for(int i = 0; i < count2; ++i)
	{
		y[i].x = intal2[i].x;
		y[i].e = i;
		y[i].c = intal2[i].c;
	}

	//printf("intal1: %s\nintal2: %s\n", intal2str(x), intal2str(y));

	if((count1%2) != 0)
	{
		x = (struct number*)realloc(x, (count1 + 1)*sizeof(struct number));
		x[count1].c = '1';
		x[count1-1].c = '0';
		x[count1].e = count1;
		x[count1].x = 0;
		++count1;
	}
	if((count2%2) != 0)
	{
		y = (struct number*)realloc(y, (count2 + 1)*sizeof(struct number));
		y[count2].c = '1';
		y[count2-1].c = '0';
		y[count2].e = count2;
		y[count2].x = 0;
		++count2;
	}

	//printf("intal1: %s\nintal2: %s\n", intal2str(x), intal2str(y));
	//printf("intal1: %s\nintal2: %s\n", intal2str(intal1), intal2str(intal2));

	int count = (count1 < count2)? count1: count2;
	struct number *p1, *p2;

	if(count == count2)
	{
		p1 = x;
		p2 = y;
	}
	else
	{
		p1 = y;
		p2 = x;
	}

	struct number *a;
	struct number *sum = intal_create("0");
	int min = count;
	int max = (count1 > count2)? count1: count2;

	//printf("min: %d max: %d\n", min, max);

	for(int i = 0; i < min-1; i = i+2)
	{
		for(int j = 0; j < max-1; j = j+2)
		{
			a = bottomupkarat(&(p1[j+1]), &(p1[j]), &(p2[i+1]), &(p2[i]));
			//printf("res: %s", intal2str(a));
			addforkarat(&sum, a);
			free(a);
		}
	}

	free(x);
	free(y);

	return sum;
}

void* intal_multiply(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL) return NULL;

	void *zero = intal_create("0");
	if(intal_compare(intal2, zero) == 0 || (intal_compare(intal2, zero) == 0)) return zero;
	else free(zero);

	return bottomupmultiplyusingkarat(intal1, intal2);
}























/*
//Power Function
struct number* dcfpow(struct number *intal1, struct number *intal2)
{
	if(intal2[0].c == '1' && intal2[0].x == 1)
	{
		void *c = intal2str(intal1);
		void *x = intal_create(c);
		free(c);
		return x;
	}
	
	void *two = intal_create("2"); 
	void *x = dcfpow(intal1, intal_divide(intal2, two));
	void *y = intal_multiply(x, x);

	if((intal2[0].x)%2 != 0)
	{
		void *z = intal_multiply(y, intal1);
		free(y);
		y = z;
	}

	free(two);
	free(x);

	return y;
}

void* intal_pow(struct number *intal1, struct number *intal2)
{
	if(intal1 == NULL || intal2 == NULL) return NULL;

	void  *one = intal_create("1");
	void *zero = intal_create("0");
	if(intal_compare(intal2, zero) == 0)
	{
		free(zero);
		return one;
	}

	free(one);
	free(zero);

	return dcfpow(intal1, intal2);
}
*/



void* intal_pow(void *intal1, void *intal2)
{
	if(intal1 == NULL || intal2 == NULL) return NULL;

	void *str = intal2str(intal2);
	void *power = intal_create(str);
	free(str);

	void *zero = intal_create("0");
	void *res = intal_create("1");

	while(intal_compare(power, zero) != 0)
	{
		//printf("hello\n");
		void *z = intal_multiply(res, intal1);
		free(res);
		res = z;
		power = intal_decrement(power);
	}

	free(power);
	free(zero);

	return res;
}
