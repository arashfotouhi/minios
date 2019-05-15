#include "string.h"

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
}

int strlen (char str[])
{
	int count = 0;
	while(str[count] != '\0') {
		count++;
	}
	return count;
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
