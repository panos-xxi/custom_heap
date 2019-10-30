/*
 * custom_heap.h
 *
 *  Created on: Oct 25, 2019
 *      Author: panos
 */

#ifndef CUSTOM_HEAP_CUSTOM_HEAP_H_
#define CUSTOM_HEAP_CUSTOM_HEAP_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>

typedef struct elem_header_
{
	struct custom_heap_elem_* prev_elem;
	struct custom_heap_elem_* next_elem;
	uint32_t alloced_size;
	uint32_t free_size_to_next_elem;
}elem_header_t;

typedef struct custom_heap_elem_
{
	elem_header_t header;
	uint8_t data[];
}custom_heap_elem_t;

typedef struct custom_heap_
{
	uint32_t total_size;
	uint32_t free_size;
	uint32_t total_elems;

	custom_heap_elem_t start_elem;
}custom_heap_t;




custom_heap_t* Custom_heap_create(uint32_t size, void*(*malloc_fxn)(size_t));
void Custom_heap_destroy( custom_heap_t* h, void(*free_fxn)(void*));

void* Custom_heap_malloc(custom_heap_t* h,size_t size);
void Custom_heap_free(custom_heap_t* h, void* ptr);


#endif /* CUSTOM_HEAP_CUSTOM_HEAP_H_ */
