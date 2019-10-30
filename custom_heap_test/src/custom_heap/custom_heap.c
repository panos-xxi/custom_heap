/*
 * custom_heap.c
 *
 *  Created on: Oct 25, 2019
 *      Author: panos
 */

#include "custom_heap.h"

custom_heap_t* Custom_heap_create(uint32_t size, void* (*malloc_fxn)(size_t))
{
	if(size == 0)
		return NULL;

	if (malloc_fxn == NULL)
		return NULL;

	custom_heap_t* h = malloc_fxn(size+sizeof(custom_heap_t));
	h->total_size = size;
	h->free_size  = size;
	h->total_elems = 0;

	h->start_elem.header.prev_elem = NULL;
	h->start_elem.header.next_elem = NULL;
	h->start_elem.header.alloced_size = 0;
	h->start_elem.header.free_size_to_next_elem = size;
	return h;
}

void Custom_heap_destroy( custom_heap_t* h,void (*free_fxn)(void*))
{
	if (h == NULL)
		return;

	free_fxn(h);
}

void* Custom_heap_malloc(custom_heap_t* h, size_t size)
{
	uint32_t needed_size = (size + sizeof(elem_header_t) + 4) & (~(0x03));//alignment at 4

	custom_heap_elem_t* elem = &h->start_elem;
	do
	{
		if(elem->header.free_size_to_next_elem < needed_size)
		{
			elem = elem->header.next_elem;
			continue;
		}

		custom_heap_elem_t* new_elem = (custom_heap_elem_t*)&(elem->data[elem->header.alloced_size]);
		new_elem->header.alloced_size = size;
		new_elem->header.free_size_to_next_elem = elem->header.free_size_to_next_elem - needed_size;
		new_elem->header.next_elem = elem->header.next_elem;
		new_elem->header.prev_elem = elem;

		elem->header.free_size_to_next_elem = 0;

		if(elem->header.next_elem != NULL)
			elem->header.next_elem->header.prev_elem = new_elem;

		elem->header.next_elem = new_elem;
		h->total_elems++;
		h->free_size -= needed_size;

		return &new_elem->data[0];

	}while (elem!=NULL);

	return NULL;
}

void Custom_heap_free(custom_heap_t* h, void* ptr)
{
	custom_heap_elem_t* elem = &h->start_elem;

	custom_heap_elem_t* wanted_ptr = ptr - sizeof(elem_header_t);

	custom_heap_elem_t* new_elem;

	do
	{
		if(elem != wanted_ptr)
		{
			elem = elem->header.next_elem;
			continue;
		}


		//unify existing element

		h->free_size += elem->header.alloced_size;

		elem->header.free_size_to_next_elem += elem->header.alloced_size;
		elem->header.alloced_size = 0;

		//decide where the new element starts

		new_elem = elem;
		if(elem->header.prev_elem != NULL)
		{
			//unify them
			new_elem = elem->header.prev_elem;
			new_elem->header.free_size_to_next_elem += elem->header.free_size_to_next_elem;
			new_elem->header.next_elem = elem->header.next_elem;

			h->total_elems--;

			h->free_size +=
		}


		//check if its the tail block
		if (new_elem->header.next_elem != NULL)//if not
		{
			if (new_elem->header.next_elem->header.alloced_size == 0) //if next block is free
			{
				//unify them
				new_elem->header.free_size_to_next_elem += new_elem->header.next_elem->header.free_size_to_next_elem;
				new_elem->header.next_elem = new_elem->header.next_elem->header.next_elem;

				h->total_elems--;
			}
		}

		return;//we are done

	}while (elem!=NULL);
}
