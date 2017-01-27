/*
** main.c for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:33 2017 Timothee Puentes
** Last update Fri Jan 27 10:43:32 2017 timothee.puentes
*/

#include <stdio.h>
#include "malloc.h"

t_malloc_header	*__malloc_head;

void			*calloc(size_t		nmemb,
				size_t		size)
{
  char			*ptr;
  size_t		it;

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

void				show_alloc_mem_()
{
  t_malloc_header		*ptr;

  my_putstr("Print :\n");
  my_put_nbr((long)sbrk(0));
  my_putchar('\n');
  ptr = __malloc_head;
  while (ptr)
    {
      my_put_nbr((long)ptr + 1);
      my_putstr(" - ");
      my_put_nbr(((long)ptr + 1) + ptr->size);
      my_putstr(" : ");
      my_put_nbr((long)ptr->size);
      if (ptr->free)
	my_putstr(" freed");
      my_putchar('\n');
      ptr = ptr->next;
    }
}

void				show_alloc_mem()
{
  t_malloc_header		*ptr;

  ptr = __malloc_head;
  printf("break: %p\n", sbrk(0));
  while (ptr)
    {
      if (!ptr->free)
	printf("%p - %p : %ld bytes\n",
	       ptr + 1, (void*)((long)ptr + sizeof(*ptr) + ptr->size)
	       , ptr->size);
      else
	printf("%p - %p : %ld bytes freed\n",
	       (void*)((long)ptr + sizeof(*ptr)),
	       (void*)((long)ptr + sizeof(*ptr) + ptr->size)
	       , ptr->size);
      ptr = ptr->next;
    }
}

void				*malloc_at_end(size_t		size,
					       t_malloc_header	*ptr)
{
  size_t			nb_pages;
  t_malloc_header		*ptr2;
  t_malloc_header		*end;

  if (ptr && ptr->free)
    nb_pages = size - ptr->size;
  else
    nb_pages = (sizeof(*ptr) + size);
  nb_pages /= getpagesize();
  nb_pages += 1;
  if (!(ptr2 = sbrk(nb_pages * getpagesize())))
    return (NULL);
  end = (void*)((long)ptr2 + (nb_pages * getpagesize()));
  if (ptr && ptr->free)
    {
      ptr2 = ptr;
      ptr = ptr->previous;
    }
  //    ptr2 = (void*)((long)ptr2 - sizeof(*ptr) - ptr->size);
  ptr2->free = false;
  ptr2->previous = ptr;
  if (ptr == NULL)
    __malloc_head = ptr2;
  else
    ptr->next = ptr2;
  if ((size_t)end > sizeof(*ptr2) + (long)ptr2 + sizeof(*ptr2) + size)
    {
      ptr2->size = size;
      ptr = (void*)((long)ptr2 + sizeof(*ptr2) + ptr2->size);
      ptr2->next = ptr;
      ptr->previous = ptr2;
      ptr->next = NULL;
      ptr->free = true;
      ptr->size = (long)end - (long)(ptr + 1);
    }
  else
    ptr2->size = (long)end - ((long)ptr2 + sizeof(*ptr2));
  return (ptr2 + 1);
}

void				*malloc(size_t	size)
{
  t_malloc_header		*ptr;
  t_malloc_header		*ptr2;

  ptr = __malloc_head;
  while (ptr != NULL && ptr->next != NULL && !(ptr->size >= size && ptr->free))
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

void				free(void	*ptr)
{
  t_malloc_header		*header;
  t_malloc_header		*end;
  t_malloc_header		*start;
  size_t			leftover;
  size_t			nb_pages;
  size_t			size;

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
      size = ((long)sbrk(0) - (long)start);
      if ((nb_pages = size / getpagesize()))
	{
	  leftover = size % getpagesize();
	  start->size = leftover;
	  if ((leftover == 0 && start->previous) || (leftover <= sizeof(t_malloc_header) && start->previous))
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
      start->size = ((long)(end + 1) + end->size - ((long)start + sizeof(*start)));
      start->next = NULL;
      return ;
    }
  start->size = ((long)end - ((long)start + sizeof(*start)));
  start->next = end;
  end->previous = start;
}
