/*
** realloc.c for Project-Master in /home/puente_t/rendu/PSU_2016_malloc
** 
** Made by timothee.puentes
** Login   <timothe.puentes@epitech.eu>
** 
** Started on  Tue Jan 24 16:59:53 2017 timothee.puentes
** Last update Sun Feb 12 22:04:07 2017 peixot_b
*/

#include "malloc.h"

pthread_mutex_t		gl_malloc_mutex;

static void			*realloc_size_inferior(void *ptrOri,
						       t_malloc_header *ptr,
						       size_t size)
{
  t_malloc_header		*ptr2;
  
  if (ptr->size - size <= sizeof(t_malloc_header))
    {
      pthread_mutex_unlock(&gl_malloc_mutex);
      return (ptrOri);
    }
  ptr2 = (void*)((long)ptr + sizeof(*ptr) + size);
  ptr2->size = ptr->size - size - sizeof(t_malloc_header);
  ptr->size = size;
  ptr2->next = ptr->next;
  ptr->next = ptr2;
  if (ptr->next)
    ptr->next->previous = ptr2;
  ptr2->previous = ptr;
  ptr2->free = false;
  pthread_mutex_unlock(&gl_malloc_mutex);
  free(ptr2 + 1);
  return (ptr + 1);
}

void				*realloc(void *ptrOri,
					 size_t size)
{
  t_malloc_header		*ptr;
  void				*tmp;
  
  if (size <= 0)
    {
      free(ptrOri);
      return (NULL);
    }
  if (ptrOri == NULL)
    return (malloc(size));
  ptr = (void*)((long)ptrOri - sizeof(*ptr));
  if (size != ptr->size)
    pthread_mutex_lock(&gl_malloc_mutex);
  if (size < ptr->size)
    tmp = realloc_size_inferior(ptrOri, ptr, size);
  else if (size > ptr->size)
    tmp = realloc_size_superior(ptrOri, ptr, size);
  else
    tmp = ptrOri;
  return (tmp);
}
