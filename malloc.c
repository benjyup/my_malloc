/*
** main.c for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:33 2017 Timothee Puentes
** Last update Thu Feb  9 16:26:14 2017 timothee.puentes
*/

#include "malloc.h"

t_malloc_header		*gl_malloc_head;
size_t			gl_pageSize;
void			*gl_break;
pthread_mutex_t		gl_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

static void			add_free_space(t_malloc_header	*ptr2,
					       t_malloc_header	*ptr,
					       size_t		size)
{
  if ((size_t)gl_break > sizeof(*ptr2) + (long)ptr2 + sizeof(*ptr2) + size)
    {
      ptr2->size = size;
      ptr = (void*)((long)ptr2 + sizeof(*ptr2) + ptr2->size);
      ptr2->next = ptr;
      ptr->previous = ptr2;
      ptr->next = NULL;
      ptr->free = true;
      ptr->size = (long)gl_break - (long)(ptr + 1);
    }
  else
    ptr2->size = (long)gl_break - ((long)ptr2 + sizeof(*ptr2));
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
    gl_malloc_head = ptr2;
  else
    ptr->next = ptr2;
  add_free_space(ptr2, ptr, size);
  pthread_mutex_unlock(&gl_malloc_mutex);
  return (ptr2 + 1);
}

static void			*malloc_at_end(size_t		size,
					       t_malloc_header	*ptr)
{
  size_t			nb_pages;
  t_malloc_header		*ptr2;

  nb_pages = ((ptr && ptr->free) ? (size - ptr->size) :
	      (sizeof(*ptr) + size));
  nb_pages = (nb_pages / gl_pageSize) + 1;
  if (!(ptr2 = sbrk(nb_pages * gl_pageSize)))
    {
      pthread_mutex_unlock(&gl_malloc_mutex);
      return (NULL);
    }
  gl_break = (void*)((long)ptr2 + (nb_pages * gl_pageSize));
  return (malloc_at_end_list(ptr, ptr2, size));
}

static void			*malloc_reuse_space(t_malloc_header	*ptr,
						    size_t		size)
{
  t_malloc_header		*ptr2;

  if (ptr->size - size > sizeof(t_malloc_header))
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
  pthread_mutex_unlock(&gl_malloc_mutex);
  return (ptr + 1);
}

void				*malloc(size_t	size)
{
  t_malloc_header		*ptr;

  if (size == 0)
    size = 1;
  if (gl_pageSize == 0)
    gl_pageSize = getpagesize();
  pthread_mutex_lock(&gl_malloc_mutex);
  ptr = gl_malloc_head;
  while (ptr != NULL && ptr->next != NULL &&
	 !(ptr->size >= size && ptr->free))
    ptr = ptr->next;
  if (ptr == NULL || ptr->next == NULL)
    return (malloc_at_end(size, ptr));
  return (malloc_reuse_space(ptr, size));
}
