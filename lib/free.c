/*
** free.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Fri Jan 27 10:50:55 2017 timothee.puentes
** Last update Fri Jan 27 10:53:56 2017 timothee.puentes
*/

#include "malloc.h"

static void			free_end(t_malloc_header	*start,
					 t_malloc_header	*end)
{
  size_t			leftover;
  size_t			nb_pages;
  size_t			size;

  size = ((long)sbrk(0) - (long)start);
  if ((nb_pages = size / getpagesize()))
    {
      leftover = size % getpagesize();
      start->size = leftover;
      if ((leftover == 0 && start->previous) ||
	  (leftover <= sizeof(t_malloc_header) && start->previous))
	start->previous->next = NULL;
      else if (leftover == 0)
	__malloc_head = NULL;
      if (leftover <= sizeof(t_malloc_header) && start->previous)
	start->previous->size += leftover;
      else
	start->size -= sizeof(t_malloc_header);
      start->next = NULL;
      sbrk(-(size - leftover));
      return ;
    }
  start->size = ((long)(end + 1) + end->size -
		 ((long)start + sizeof(*start)));
  start->next = NULL;
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
  while (start->previous != NULL && start->previous->free)
    start = start->previous; 
  if (start->previous == NULL && (end == NULL || end->next == NULL))
    __malloc_head = NULL;
  if (!end->next && end->free)
    {
      free_end(start, end);
      return ;
    }
  start->size = ((long)end - ((long)start + sizeof(*start)));
  start->next = end;
  end->previous = start;
}
