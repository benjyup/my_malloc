/*
** malloc.h for  in /home/puente_t/rendu/test
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Sun Jan 22 15:12:49 2017 Timothee Puentes
** Last update Thu Feb  9 16:43:48 2017 timothee.puentes
*/

#ifndef MY_MALLOC_H
# define MY_MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct			s_malloc_header
{
  size_t			size;
  char				free;
  struct s_malloc_header	*next;
  struct s_malloc_header	*previous;
}				__attribute__((packed)) t_malloc_header;

extern t_malloc_header	*gl_malloc_head;
extern size_t		gl_pageSize;
extern void		*gl_break;
extern pthread_mutex_t 	gl_malloc_mutex;

void			*calloc(size_t		nmemb,
				size_t		size);

void			*malloc(size_t		size);

void			*realloc(void		*ptr,
				 size_t		size);

void			*realloc_size_superior(void		*ptrOri,
					       t_malloc_header	*ptr,
					       size_t		size);

void			free(void		*ptr);

void			show_alloc_mem();

#endif /* MY_MALLOC_H */
