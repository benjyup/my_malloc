/*
** main.c for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:33 2017 Timothee Puentes
** Last update Thu Jan 26 14:45:30 2017 timothee.puentes
*/

#include <stdio.h>
#include "malloc.h"

t_malloc_header	*__malloc_head;

void			*calloc(size_t		nmemb,
				size_t		size)
{
  char			*ptr;
  size_t		it;

  it = 0;
  if ((ptr = malloc(nmemb * size)))
    {
      while (it < size * nmemb)
	{
	  ptr[it] = 0;
	  it++;
	}
    }
  return ((void*)ptr);
}

void				show_alloc_mem()
{
  t_malloc_header		*ptr;

  ptr = __malloc_head;
  printf("break: %p\n", sbrk(0));
  while (ptr)
    {
      if (!ptr->free)
	printf("%p - %p : %ld bytes\n",
	       (void*)((long)ptr + sizeof(*ptr)),
	       (void*)((long)ptr + sizeof(*ptr) + ptr->size)
	       , ptr->size);
      ptr = ptr->next;
    }
}

void				*malloc(size_t	size)
{
  t_malloc_header		*ptr;
  t_malloc_header		*ptr2;
  
  ptr = __malloc_head;
  while (ptr != NULL && ptr->next != NULL && !(ptr->size >= size && ptr->free))
      ptr = ptr->next;
  if (ptr == NULL || ptr->next == NULL)
    {
      if (!(ptr2 = sbrk(sizeof(*ptr) + size)))
	return (NULL);
      ptr2->free = false;
      ptr2->next = NULL;
      ptr2->previous = ((ptr == NULL) ? (NULL) : (ptr));
      if (ptr == NULL)
	__malloc_head = ptr2;
      else
	ptr->next = ptr2;
      ptr2->size = size;
      return (ptr2 + 1);
    }
  if (size + sizeof(t_malloc_header) < ptr->size)
    {
      ptr2 = (void*)((long)ptr + sizeof(*ptr) + (long)(size));
      ptr2->free = true;
      ptr2->next = ptr->next;
      ptr2->previous = ptr;
      if (ptr2->next)
	((t_malloc_header*)ptr2->next)->previous = ptr2;
      ptr2->size = ptr->size - size - sizeof(*ptr2);
      ptr->next = ptr2;
      ptr->size = size;
    }
  ptr->free = false;
  return (ptr + 1);
}

void				free(void	*ptr)
{
  t_malloc_header		*header;
  t_malloc_header		*end;
  t_malloc_header		*start;

  if (ptr == NULL)
    return ;
  header = ptr - sizeof(*header);
  header->free = true;
  end = header;
  while (end->next != NULL && end->free)
    end = end->next;
  start = header;
  while (start->previous != NULL && ((t_malloc_header*)start->previous)->free)
    start = start->previous; 
  if (start->previous == NULL && (end == NULL || end->next == NULL))
    __malloc_head = NULL;
  if (!end->next && end->free)
    {
      if (start->previous)
	((t_malloc_header*)start->previous)->next = NULL;
      sbrk((long)sbrk(0) - (long)start);
      return ;
    }
  start->size = ((long)end - ((long)start + sizeof(*start)));
  start->next = end;
  end->previous = start;
}
