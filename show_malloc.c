/*
** show_malloc.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sat Jan 28 10:28:29 2017 timothee.puentes
** Last update Mon Feb  6 20:45:19 2017 timothee.puentes
*/

#include "malloc.h"

void				show_alloc_mem()
{
  t_malloc_header		*ptr;

  ptr = __malloc_head;
  if (__break == NULL)
    __break = sbrk(0);
  printf("break: %p\n", __break);
  while (ptr)
    {
      if (!ptr->free)
	printf("%p - %p : %ld bytes\n",
	       ptr + 1, (void*)((long)ptr + sizeof(*ptr) + ptr->size)
	       , ptr->size);
      ptr = ptr->next;
    }
}

