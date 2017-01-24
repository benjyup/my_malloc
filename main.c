/*
** main.c for  in /home/puente_t/rendu/PSU_2017_malloc/lib
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Mon Jan 23 13:48:13 2017 Timothee Puentes
** Last update Tue Jan 24 18:01:00 2017 timothee.puentes
*/

#include "lib/malloc.h"
#include <stdio.h>

int		main(void)
{
  char		*str0;
  char		*str1;
  char		*str2;
  char		*str3;

  printf("sizeof(%ld)\n", sizeof(t_malloc_header));
  show_alloc_mem();

  str0 = malloc(100); str0[0] = 0;
  str1 = malloc(15); str1[0] = 0;
  str2 = malloc(1000); str2[0] = 0;
  str3 = malloc(10); str3[0] = 0;
  
  printf("str0 %p %ld\n", str0, (long)str0);
  printf("str1 %p %ld\n", str1, (long)str1);
  printf("str2 %p %ld\n", str2, (long)str2);
  printf("str3 %p %ld\n", str3, (long)str3);

  show_alloc_mem();

  free(str0);
  free(str1);
  free(str2);
  free(str3);

  show_alloc_mem();

  //return (1);

  str0 = malloc(11); str0[0] = 0;
  str1 = malloc(560); str1[0] = 0;
  str2 = malloc(12); str2[0] = 0;
  str3 = malloc(13); str3[0] = 0;
  
  //return (1);
  
  show_alloc_mem();

  printf("str0 %p %ld\n", str0, (long)str0);
  printf("str1 %p %ld\n", str1, (long)str1);
  printf("str2 %p %ld\n", str2, (long)str2);
  printf("str3 %p %ld\n", str3, (long)str3);

  char		**ptr;
  int		c = 0;
  
  ptr = malloc(sizeof(char*) * 10);
  c = 0;
  while (c < 10)
    {
      ptr[c] = malloc((c + 1) * 100);
      c++;
    }

  show_alloc_mem();
  
  c = 0;
  while (c < 10)
    {
      free(ptr[c]);
      c++;
    }
  free(ptr);
  free(str0);
  free(str1);
  free(str2);
  free(str3);
  
  show_alloc_mem();

  write(1, "\n\n\n", 3);

  str0 = malloc(100); str0[99] = 0;
  
  show_alloc_mem();
  
  str0 = realloc(str0, 50); str0[49] = 0;

  show_alloc_mem();

  str1 = malloc(150);
  
  str0 = realloc(str0, 75); str0[74] = 0;

  show_alloc_mem();

  free(str1);

  show_alloc_mem();

  str2 = malloc(175); str2[174] = 0;

  show_alloc_mem();
  
  free(str0);
  
  show_alloc_mem();

  free(str2);
  
  return (0);
}
