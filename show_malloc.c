/*
** show_malloc.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sat Jan 28 10:28:29 2017 timothee.puentes
** Last update Wed Feb  8 10:42:54 2017 timothee.puentes
*/

#include "malloc.h"

t_malloc_header		*gl_malloc_head;
void			*gl_break;

void				show_alloc_mem()
{
  t_malloc_header		*ptr;

  ptr = gl_malloc_head;
  if (gl_break == NULL)
    gl_break = sbrk(0);
  printf("break: %p\n", gl_break);
  while (ptr)
    {
      if (!ptr->free)
	printf("%p - %p : %ld bytes\n",
	       ptr + 1, (void*)((long)ptr + sizeof(*ptr) + ptr->size)
	       , ptr->size);
      ptr = ptr->next;
    }
}

