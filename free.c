/*
** free.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Fri Jan 27 10:50:55 2017 timothee.puentes
** Last update Sun Feb 12 22:00:53 2017 peixot_b
*/

#include "malloc.h"

t_malloc_header		*gl_malloc_head;
size_t			gl_pageSize;
void			*gl_break;
pthread_mutex_t		gl_malloc_mutex;

static void			free_sbrk(t_malloc_header *start,
					  size_t size)
{
  size_t			leftover;

  leftover = size % gl_pageSize;
  start->size = leftover;
  if ((leftover == 0 && start->previous) ||
      (leftover <= sizeof(t_malloc_header) && start->previous))
    start->previous->next = NULL;
  else if (leftover == 0)
    gl_malloc_head = NULL;
  if (leftover <= sizeof(t_malloc_header) && start->previous)
    start->previous->size += leftover;
  else
    start->size -= sizeof(t_malloc_header);
  start->next = NULL;
  gl_break = sbrk(-(size - leftover));
  gl_break = (void*)((long)gl_break - (size - leftover));
}

static void			free_end(t_malloc_header *start,
					 t_malloc_header *end)
{
  size_t			size;

  size = ((long)gl_break - (long)start);
  if (size / gl_pageSize != 0)
    {
      free_sbrk(start, size);
      return ;
    }
  start->size = ((long)(end + 1) + end->size -
		 ((long)start + sizeof(*start)));
  start->next = NULL;
}

void				free_middle(t_malloc_header *start,
					    t_malloc_header *end)
{
  start->size = ((long)end - ((long)start + sizeof(*start)));
  start->next = end;
  end->previous = start;
}

void				free(void *ptr)
{
  t_malloc_header		*header;
  t_malloc_header		*end;
  t_malloc_header		*start;

  if (ptr == NULL)
    return ;
  pthread_mutex_lock(&gl_malloc_mutex);
  header = ptr - sizeof(*header);
  header->free = true;
  end = header;
  while (end->next != NULL && end->free)
    end = end->next;
  start = header;
  while (start->previous != NULL && start->previous->free)
    start = start->previous; 
  if (start->previous == NULL && (end == NULL || end->next == NULL))
    gl_malloc_head = NULL;
  if (!end->next && end->free)
    free_end(start, end);
  else
    free_middle(start, end);
  pthread_mutex_unlock(&gl_malloc_mutex);
}
