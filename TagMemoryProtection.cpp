// TagMemoryProtection.cpp : 
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

void* TAG_MALLOC(size_t size)
{
	static const size_t ptr_size = min(sizeof(void*), (size_t)8);
	size = size <= 0 ? 1 : size;
	size += ptr_size;
	char *ptr = (char *)malloc(size);
	memcpy(ptr, "TAG_MALLOC", ptr_size);
	return ptr + ptr_size;
}

void TAG_FREE(void *ptr)
{
	static const size_t ptr_size = min(sizeof(void*), (size_t)8);
	if (ptr == nullptr)
		return;
	char *sptr = (char *)ptr;
	sptr = sptr - ptr_size;
	// has been freed.
	if (0 != strncmp(sptr, "TAG_MALLOC", ptr_size))
		return;
	memset(sptr, 0, ptr_size);
	free(sptr);
}

int main()
{
	//int * data = (int*)malloc(sizeof(int) * 10);
	//free(data);
	//free(data);

	int * data = (int*)TAG_MALLOC(sizeof(int) * 10);

	TAG_FREE(data);
	TAG_FREE(data);
    return 0;
}

