/*
** main.c for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:33 2017 Timothee Puentes
** Last update Thu Feb  2 10:42:11 2017 Timothee Puentes
*/

#include "malloc.h"

t_malloc_header		*__malloc_head;
size_t			__pageSize;
void			*__break;
pthread_mutex_t		__malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

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

static void			*malloc_at_end_list(t_malloc_header	*ptr,
						    t_malloc_header	*ptr2,
						    size_t		size)
{
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
  pthread_mutex_unlock(&__malloc_mutex);
  return (ptr2 + 1);
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
    {
      pthread_mutex_unlock(&__malloc_mutex);
      return (NULL);
    }
  __break = (void*)((long)ptr2 + (nb_pages * __pageSize));
  return (malloc_at_end_list(ptr, ptr2, size));
}

static void			*malloc_reuse_space(t_malloc_header	*ptr,
						    size_t		size)
{
  t_malloc_header		*ptr2;

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
  pthread_mutex_unlock(&__malloc_mutex);
  return (ptr + 1);
}

void				*malloc(size_t	size)
{
  t_malloc_header		*ptr;

  if (__pageSize == 0)
    __pageSize = getpagesize();
  pthread_mutex_lock(&__malloc_mutex);
  ptr = __malloc_head;
  while (ptr != NULL && ptr->next != NULL &&
	 !(ptr->size >= size && ptr->free))
    ptr = ptr->next;
  if (ptr == NULL || ptr->next == NULL)
    return (malloc_at_end(size, ptr));
  return (malloc_reuse_space(ptr, size));
}
