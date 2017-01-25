/*
** malloc.h for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:49 2017 Timothee Puentes
** Last update Wed Jan 25 12:42:39 2017 timothee.puentes
*/

#ifndef MY_MALLOC_H
# define MY_MALLOC_H

# include <unistd.h>
# include <stdbool.h>

typedef struct	        s_malloc_header
{
  size_t		size;
  char			free;
  void			*next;
  void			*previous;
}			//__attribute__((packed))
  t_malloc_header;

void			*calloc(size_t		nmemb,
				size_t		size);

void			*malloc(size_t		size);

void			*realloc(void		*ptr,
				 size_t		size);

void			free(void		*ptr);

void			show_alloc_mem();

#endif /* MY_MALLOC_H */
