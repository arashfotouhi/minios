#include "string.h"

int strlen (char str[])
{
	int count = 0;
	while(str[count] != '\0') {
		count++;
	}
	return count;
}


void reverse (char str[])
{
	int temp, i, j;
	for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

void int_to_ascii (int n, char str[]) 
{
	int i, sign;
	if((sign=n) < 0) n = -n;
	i = 0;
	do {
		str[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if(sign < 0) str[i++] = '-';
	str[i] = '\0';

	reverse(str);
}

void hex_to_ascii (int n, char str[])
{
	int i, sign;
	if((sign=n) < 0) n = -n;
	i = 0;
	do {
		if (n % 16 <= 9) {
			str[i++] = n % 16 + '0';
		} else {
			str[i++] = n % 16 + 'A';
		}
	} while ((n /= 16) > 0);

	if(sign < 0) str[i++] = '-';
	str[i] = '\0';

	reverse(str);
}

void backspace (char str[])
{
	int len = strlen(str);
	str[len-1] = '\0';
}

void append (char str[], char letter)
{
	int len = strlen(str);
	str[len] = letter;
	str[len+1] = '\0';
}

int strcmp (char s1[], char s2[])
{
	int i;
	for (i=0; s1[i] == s2[i]; i++)
		if (s1[i] == '\0')
			return 0;
	return s1[i] - s2[i];
}
