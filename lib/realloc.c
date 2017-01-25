/*
** realloc.c for Project-Master in /home/puente_t/rendu/PSU_2016_malloc
** 
** Made by timothee.puentes
** Login   <timothe.puentes@epitech.eu>
** 
** Started on  Tue Jan 24 16:59:53 2017 timothee.puentes
** Last update Wed Jan 25 17:41:23 2017 timothee.puentes
*/

#include <stdio.h>
#include "malloc.h"

void				copy_data(t_malloc_header	*ptr,
					  t_malloc_header	*ptr2)
{
  char				*ptrIt;
  char				*ptr2It;
  size_t			c;
  size_t			size;
  
  c = 0;
  size = ptr2->size;
  ptrIt = (void*)((long)ptr + sizeof(*ptr));
  ptr2It = (void*)((long)ptr2 + sizeof(*ptr2));
  while (c < size)
    {
      ptrIt[c] = ptr2It[c];
      c++;
    }
}


void				*realloc_free_around(t_malloc_header	*ptr,
						     size_t		size,
						     size_t		sizeAviable)
{
  t_malloc_header		*start;
  t_malloc_header		*end;
  t_malloc_header		*freePart;

  start = ((ptr->previous && ((t_malloc_header*)ptr->previous)->free) ?
	   (ptr->previous) : (ptr));
  end = ((ptr->next && ((t_malloc_header*)ptr->next)->free) ?
	 (((t_malloc_header*)ptr->next)->next) : (ptr->next) );
  if (start != ptr)
    copy_data(start, ptr);
  start->size = size;
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
      write(1, "2\n", 2);
      free((void*)((long)freePart + sizeof(*freePart)));
    }
  else
    {
      start->size = sizeAviable;
      start->next = end;
      if (end)
	end->previous = start;
    }
  return ((void*)((long)start + sizeof(*start)));
}

void				*realloc(void	*ptrOri,
					 size_t	size)
{
  void				*newPtr;
  t_malloc_header		*ptr;
  t_malloc_header		*ptr2;
  size_t			sizeAviable;
  
  if (ptrOri == NULL)
    return (malloc(size));
  ptr = (void*)((long)ptrOri - sizeof(*ptr));
  if (size < ptr->size)
    {
      if (ptr->size - size <= sizeof(t_malloc_header))
	{
	  return ((void*)((long)ptr + sizeof(*ptr)));
	}
      ptr2 = (void*)((long)ptr + sizeof(*ptr) + size);
      ptr2->size = ptr->size - size - sizeof(t_malloc_header);
      
      ptr->size = size;

      ptr2->next = ptr->next;
      ptr->next = ptr2;
      if (ptr->next)
	((t_malloc_header*)ptr->next)->previous = ptr2;
      ptr2->previous = ptr;
      ptr2->free = false;
      free((void*)((long)ptr2 + sizeof(*ptr2)));
      return ((void*)((long)ptr + sizeof(*ptr)));
    }
  else if (size > ptr->size)
    {
      if ((ptr->previous && ((t_malloc_header*)ptr->previous)->free) ||
	  (ptr->next && ((t_malloc_header*)ptr->next)->free))
	{
	  sizeAviable = ptr->size;
	  sizeAviable += ((ptr->next && ((t_malloc_header*)ptr->next)->free)
			  ? (((t_malloc_header*)ptr->next)->size + sizeof(*ptr)) : (0));
	  sizeAviable += ((ptr->previous && ((t_malloc_header*)ptr->previous)->free)
			  ? (((t_malloc_header*)ptr->previous)->size + sizeof(*ptr)) : (0));
	  if (sizeAviable >= size)
	    return (realloc_free_around(ptr, size, sizeAviable));
	}
      if (!ptr->next)
	{
	  sbrk(size - ptr->size);
	  ptr->size = size;
	  return (ptrOri);
	}
      if (!(newPtr = malloc(size)))
	return (NULL);
      copy_data((void*)((long)newPtr - sizeof(*newPtr)), ptr);
      free(ptrOri);
      return (newPtr);
    }
  return (ptrOri);
}
