/*
** free.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Fri Jan 27 10:50:55 2017 timothee.puentes
** Last update Mon Jan 30 15:44:02 2017 timothee.puentes
*/

#include "malloc.h"

t_malloc_header		*__malloc_head;
size_t			__pageSize;
void			*__break;
pthread_mutex_t		__malloc_mutex;

static void			free_sbrk(t_malloc_header	*start,
					  size_t		size)
{
  size_t			leftover;

  leftover = size % __pageSize;
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
  __break = sbrk(-(size - leftover));
  __break = (void*)((long)__break - (size - leftover));
}

static void			free_end(t_malloc_header	*start,
					 t_malloc_header	*end)
{
  size_t			size;

  size = ((long)__break - (long)start);
  if (size / __pageSize != 0)
    {
      free_sbrk(start, size);
      return ;
    }
  start->size = ((long)(end + 1) + end->size -
		 ((long)start + sizeof(*start)));
  start->next = NULL;
}

void				free_middle(t_malloc_header		*start,
					    t_malloc_header		*end)
{
  start->size = ((long)end - ((long)start + sizeof(*start)));
  start->next = end;
  end->previous = start;
}

void				free(void	*ptr)
{
  t_malloc_header		*header;
  t_malloc_header		*end;
  t_malloc_header		*start;

  if (ptr == NULL)
    return ;
  pthread_mutex_lock(&__malloc_mutex);
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
    free_end(start, end);
  else
    free_middle(start, end);
  pthread_mutex_unlock(&__malloc_mutex);
}
