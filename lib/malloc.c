/*
** main.c for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:33 2017 Timothee Puentes
** Last update Fri Jan 27 11:50:43 2017 timothee.puentes
*/

#include "malloc.h"

t_malloc_header		*__malloc_head;
size_t			__pageSize;
void			*__break;

void				*calloc(size_t		nmemb,
					size_t		size)
{
  char				*ptr;
  size_t			it;

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

static void			add_free_space(t_malloc_header	*ptr2,
					       t_malloc_header	*ptr,
					       size_t		size)
{
  if ((size_t)__break > sizeof(*ptr2) + (long)ptr2 + sizeof(*ptr2) + size)
    {
      ptr2->size = size;
      ptr = (void*)((long)ptr2 + sizeof(*ptr2) + ptr2->size);
      ptr2->next = ptr;
      ptr->previous = ptr2;
      ptr->next = NULL;
      ptr->free = true;
      ptr->size = (long)__break - (long)(ptr + 1);
    }
  else
    ptr2->size = (long)__break - ((long)ptr2 + sizeof(*ptr2));
}

static void			*malloc_at_end(size_t		size,
					       t_malloc_header	*ptr)
{
  size_t			nb_pages;
  t_malloc_header		*ptr2;

  nb_pages = ((ptr && ptr->free) ? (size - ptr->size) :
	      (sizeof(*ptr) + size));
  nb_pages = (nb_pages / __pageSize) + 1;
  if (!(ptr2 = sbrk(nb_pages * __pageSize)))
    return (NULL);
  __break = (void*)((long)ptr2 + (nb_pages * __pageSize));
  if (ptr && ptr->free)
    {
      ptr2 = ptr;
      ptr = ptr->previous;
    }
  ptr2->free = false;
  ptr2->previous = ptr;
  if (ptr == NULL)
    __malloc_head = ptr2;
  else
    ptr->next = ptr2;
  add_free_space(ptr2, ptr, size);
  return (ptr2 + 1);
}

void				*malloc(size_t	size)
{
  t_malloc_header		*ptr;
  t_malloc_header		*ptr2;

  if (__pageSize == 0)
    __pageSize = getpagesize();
  ptr = __malloc_head;
  while (ptr != NULL && ptr->next != NULL &&
	 !(ptr->size >= size && ptr->free))
    ptr = ptr->next;
  if (ptr == NULL || ptr->next == NULL)
    return (malloc_at_end(size, ptr));
  if (size + sizeof(t_malloc_header) < ptr->size)
    {
      ptr2 = (void*)((long)(ptr + 1) + size);
      ptr2->free = true;
      ptr2->previous = ptr;
      ptr2->size = ptr->size - size - sizeof(*ptr2);      
      ptr2->next = ptr->next;
      if (ptr2 && ptr2->next)
	ptr2->next->previous = ptr2;
      ptr->next = ptr2;
      ptr->size = size;
    }
  ptr->free = false;
  return (ptr + 1);
}
