#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum year{Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec}; 

int main() { 

	char* str = malloc(1000);
	str = strcpy(str, "bbb");
	int x = 10;
	printf("%s",str);
	printf("\n");
	str= strcat(str, (char)x);
	printf("%s",str);
	printf("\n");
} 
