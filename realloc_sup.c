/*
** realloc_sup.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Fri Jan 27 11:06:39 2017 timothee.puentes
** Last update Wed Feb  8 10:44:02 2017 timothee.puentes
*/

#include "malloc.h"

t_malloc_header		*gl_malloc_head;
size_t			gl_pageSize;
void			*gl_break;
pthread_mutex_t		gl_malloc_mutex;

static void			copy_data(t_malloc_header	*ptr,
					  t_malloc_header	*ptr2)
{
  char				*ptrIt;
  char				*ptr2It;
  size_t			c;
  size_t			size;
  
  c = 0;
  size = ptr2->size;
  ptrIt = (void*)(ptr + 1);
  ptr2It = (void*)(ptr2 + 1);
  while (c < size)
    {
      ptrIt[c] = ptr2It[c];
      c++;
    }
}

static void			realloc_free_around_setup_free_space(size_t		size,
								     size_t		sizeAviable,
								     t_malloc_header	*start,
								     t_malloc_header	*end)
{
  t_malloc_header		*freePart;
  
  if (sizeAviable - size > sizeof(*start))
    {
      freePart = (void*)((long)start + sizeof(*start) + size);
      start->next = freePart;
      if (end)
	end->previous = freePart;
      freePart->free = false;
      freePart->next = end;
      freePart->previous = start;
      freePart->size = sizeAviable - size - sizeof(*start);
      pthread_mutex_unlock(&gl_malloc_mutex);
      free(freePart + 1);
    }
  else
    {
      start->size = sizeAviable;
      start->next = end;
      if (end)
	end->previous = start;
      pthread_mutex_unlock(&gl_malloc_mutex);
    }
}

static void			*realloc_free_around(t_malloc_header	*ptr,
						     size_t		size,
						     size_t		sizeAviable)
{
  t_malloc_header		*start;
  t_malloc_header		*end;

  start = ((ptr->previous && ptr->previous->free) ?
	   (ptr->previous) : (ptr));
  end = ((ptr->next && ptr->next->free) ?
	 (ptr->next->next) : (ptr->next) );
  if (start != ptr)
    copy_data(start, ptr);
  start->size =size;
  start->free = false;
  realloc_free_around_setup_free_space(size, sizeAviable, start, end);
  return (start + 1);
}

static void			*realloc_at_end(void			*ptrOri,
						t_malloc_header		*ptr,
						size_t			sizeAviable,
						size_t			size)
{
  t_malloc_header		*ptr2;

  sizeAviable = size - ((long)gl_break - (long)(ptr + 1));
  sizeAviable = ((sizeAviable / gl_pageSize) + 1) * gl_pageSize;
  if (!(gl_break = sbrk(sizeAviable)))
    return (NULL);
  gl_break = (void*)((long)gl_break + sizeAviable);
  ptr->size = size;
  ptr2 = (void*)((long)(ptr + 1) + ptr->size);
  sizeAviable = (long)gl_break - (long)ptr2;
  if (sizeAviable <= sizeof(*ptr))
    {
      ptr->size = size + sizeAviable;
      ptr->next = NULL;
    }
  else
    {
      ptr->next = ptr2;
      ptr2->next = NULL;
      ptr2->previous = ptr;
      ptr2->free = true;
      ptr2->size = (long)gl_break - (long)(ptr2 + 1);
    }
  pthread_mutex_unlock(&gl_malloc_mutex);
  return (ptrOri);
}

void				*realloc_malloc(size_t			size)
{
  pthread_mutex_unlock(&gl_malloc_mutex);
  return (malloc(size));
}

void				*realloc_size_superior(void		*ptrOri,
						       t_malloc_header	*ptr,
						       size_t		size)
{
  void				*newPtr;
  size_t			sizeAviable;
  
  if ((ptr->previous && ptr->previous->free) ||
      (ptr->next && ptr->next->free))
    {
      sizeAviable = ptr->size;
      sizeAviable += ((ptr->next && ptr->next->free)
		      ? (ptr->next->size + sizeof(*ptr)) : (0));
      sizeAviable += ((ptr->previous && ptr->previous->free)
		      ? (ptr->previous->size + sizeof(*ptr)) : (0));
      if (sizeAviable >= size)
	return (realloc_free_around(ptr, size, sizeAviable));
    }
  if (!ptr->next)
    return (realloc_at_end(ptrOri, ptr, sizeAviable, size));
  else if (!(newPtr = realloc_malloc(size)))
    return (NULL);
  copy_data((void*)((long)newPtr - sizeof(t_malloc_header)), ptr);
  free(ptrOri);
  return (newPtr);
}
