/*
** calloc.c for  in /home/puente_t/rendu/PSU_2016_malloc/lib
** 
** Made by timothee.puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sat Jan 28 10:29:02 2017 timothee.puentes
** Last update Wed Feb  8 17:05:48 2017 timothee.puentes
*/

#include "malloc.h"

void				*calloc(size_t		nmemb,
					size_t		size)
{
  char				*ptr;
  size_t			it;

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
