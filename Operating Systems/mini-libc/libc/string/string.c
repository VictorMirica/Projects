// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	char* aux = destination;
	while (*source != '\0') {
		*aux = *source;
		aux++;
		source++;
	}

	*aux = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
    char* aux = destination;

	while (len > 0 && *source != '\0') {
		len--;
		*aux = *source;
		aux++;
		source++;
	}

	while (len > 0) {
		len--;
		*aux = '\0';
		aux++;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
    char* aux = destination;

	while (*aux != '\0') {
		aux++;
	}

	while(*source != '\0') {
		*aux = *source;
		aux++;
		source++;
	}

	*aux = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
    char* aux = destination;

	while (*aux != '\0') {
		aux++;
	}

	while(len > 0 && *source != '\0') {
		len--;
		*aux = *source;
		aux++;
		source++;
	}

	*aux = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
    while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2)
			break;
		
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return 0;
	
	if (*str1 > *str2)
		return 1;

	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
    while (*str1 != '\0' && *str2 != '\0' && len > 0) {
		len--;
		if (*str1 != *str2)
			break;
		
		str1++;
		str2++;
	}

	if (*str1 == *str2 || len == 0)
		return 0;
	
	if (*str1 > *str2)
		return 1;

	return -1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
    while(*str != '\0') {
		if (*str == c)
			return (char*)str;
		
		str++;
	}

	if (*str == c)
		return (char*)str;

	return NULL;
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
    char* ret = NULL;

	while(*str != '\0') {
		if (*str == c)
			ret = (char*)str;
		
		str++;
	}

	if (*str == c)
		ret = (char*)str;

	if (ret != NULL)
		return ret;

	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
    while (*haystack != '\0') {

		char* aux1 = (char*)haystack;
		char* aux2 = (char*)needle;

		while (*aux1 != '\0' && *aux2 != '\0') {

			if (*aux1 != *aux2)
				break;

			aux1++;
			aux2++;
		}

		if (*aux2 == '\0')
			return (char*)haystack;

		haystack++;
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
    char* ret = NULL;

	while (*haystack != '\0') {

		char* aux1 = (char*)haystack;
		char* aux2 = (char*)needle;

		while (*aux1 != '\0' && *aux2 != '\0') {

			if (*aux1 != *aux2)
				break;

			aux1++;
			aux2++;
		}

		if (*aux2 == '\0')
			ret = (char*)haystack;

		haystack++;
	}

	if (ret != NULL) 
		return ret;

	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
    char* dest = (char*) destination;
    const char* src = (const char*) source;

	for (size_t i = 0; i < num; i++) {
		dest[i] = src[i]; 
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
    char* dest = (char*) destination;
    const char* src = (const char*) source;

	if (dest < src) {
		for (size_t i = 0; i < num; i++) {
			dest[i] = src[i]; 
		}
	} else {
		for (int i = num - 1; i >= 0; i--) {
			dest[i] = src[i];
		}
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
    const unsigned char* p1 = (const unsigned char*) ptr1;
	const unsigned char* p2 = (const unsigned char*) ptr2;

	while (num > 0) {
		if (*p1 != *p2) {
			break;
		}

		num--;
		p1++;
		p2++;
	}

	if (num == 0)
		return 0;

	if (*p1 > *p2)
		return 1;

	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
    unsigned char* src = (unsigned char*)source;
	while (num > 0) {
		num--;

		*src = (unsigned char)value;

		src++;
	}

	return source;
}