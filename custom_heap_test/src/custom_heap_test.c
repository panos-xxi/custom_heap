/*
 ============================================================================
 Name        : custom_heap_test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "custom_heap/custom_heap.h"

uint8_t vals[] = {0, 1, 2, 3, 4, 5};

int main(void) {
	custom_heap_t* h = Custom_heap_create(210, malloc);


	void* obj0 = Custom_heap_malloc(h,5);
	memcpy(obj0, "msg0",5);

	void* obj1 = Custom_heap_malloc(h,5);
	memcpy(obj1, "msg1",5);

	void* obj2 = Custom_heap_malloc(h,5);
	memcpy(obj2, "msg2",5);

	void* obj3 = Custom_heap_malloc(h,5);
	memcpy(obj3, "msg3",5);

	void* obj4 = Custom_heap_malloc(h,5);
	memcpy(obj4, "msg4",5);

	Custom_heap_free(h, obj2);

	obj2 = Custom_heap_malloc(h,4);
	memcpy(obj2, "msg2",4);


	Custom_heap_free(h, obj3);

	void* obj5 = Custom_heap_malloc(h,6);
	memcpy(obj5, "msg55",6);

	Custom_heap_free(h, obj1);

	Custom_heap_free(h, obj2);

	Custom_heap_free(h, obj5);

	Custom_heap_free(h, obj0);

	Custom_heap_free(h, obj4);




	Custom_heap_destroy(h, free);
	return EXIT_SUCCESS;
}
