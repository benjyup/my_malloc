/*
** realloc.c for Project-Master in /home/puente_t/rendu/PSU_2016_malloc
** 
** Made by timothee.puentes
** Login   <timothe.puentes@epitech.eu>
** 
** Started on  Tue Jan 24 16:59:53 2017 timothee.puentes
** Last update Thu Jan 26 18:32:14 2017 timothee.puentes
*/

#include <stdio.h>
#include "malloc.h"

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


static void			*realloc_free_around(t_malloc_header	*ptr,
						     size_t		size,
						     size_t		sizeAviable)
{
  t_malloc_header		*start;
  t_malloc_header		*end;
  t_malloc_header		*freePart;

  start = ((ptr->previous && ptr->previous->free) ?
	   (ptr->previous) : (ptr));
  end = ((ptr->next && ptr->next->free) ?
	 (ptr->next->next) : (ptr->next) );
  if (start != ptr)
    copy_data(start, ptr);
  start->size =size;
  start->free = false;
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
      free(freePart + 1);
    }
  else
    {
      start->size = sizeAviable;
      start->next = end;
      if (end)
	end->previous = start;
    }
  return (start + 1);
}

void				*realloc(void	*ptrOri,
					 size_t	size)
{
  void				*newPtr;
  t_malloc_header		*ptr;
  t_malloc_header		*ptr2;
  size_t			sizeAviable;

  if (size <= 0)
    {
      free(ptrOri);
      return (NULL);
    }
  if (ptrOri == NULL)
    return (malloc(size));
  ptr = (void*)((long)ptrOri - sizeof(*ptr));
  if (size < ptr->size)
    {
      if (ptr->size - size <= sizeof(t_malloc_header))
	return (ptrOri);
      ptr2 = (void*)((long)ptr + sizeof(*ptr) + size);
      ptr2->size = ptr->size - size - sizeof(t_malloc_header);
      ptr->size = size;
      ptr2->next = ptr->next;
      ptr->next = ptr2;
      if (ptr->next)
	ptr->next->previous = ptr2;
      ptr2->previous = ptr;
      ptr2->free = false;
      free(ptr2 + 1);
      return (ptr + 1);
    }
  else if (size > ptr->size)
    {
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
	{
	  sizeAviable = size - ptr->size;
	  if (!sbrk(sizeAviable / getpagesize() + 1))
	    return (NULL);
	  sizeAviable %= getpagesize();
	  ptr2 = (void*)((long)(ptr + 1) + ptr->size);
	  if (sizeAviable <= sizeof(*ptr))
	    {
	      ptr->size = size + sizeAviable;
	      ptr2->next = NULL;
	      ptr->next = ptr2;
	      ptr2->previous = ptr;
	      ptr2->free = true;
	      ptr2->size = sizeAviable - sizeof(*ptr);
	    }
	  else
	    ptr->size = size;
	  return (ptrOri);
	}
      else if (!(newPtr = malloc(size)))
	return (NULL);
      copy_data((void*)((long)newPtr - sizeof(*newPtr)), ptr);
      free(ptrOri);
      return (newPtr);
    }
  return (ptrOri);
}
  
