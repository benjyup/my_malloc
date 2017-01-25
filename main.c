/*
** main.c for  in /home/puente_t/rendu/PSU_2017_malloc/lib
** 
** Made by Timothee Puentes
** Login   <puente_t@epitech.net>
** 
** Started on  Mon Jan 23 13:48:13 2017 Timothee Puentes
** Last update Wed Jan 25 14:50:22 2017 timothee.puentes
*/

#include "lib/malloc.h"
#include <stdlib.h>
#include <stdio.h>

int		main(void)
{
  char		*str0;
  char		*str1;
  char		*str2;
  char		*str3;
  char		**ptr;
  int		c = 0;
  char		*test[150];
  int		testfree[150];
  size_t	size, i;

  srandom(50);
  if (0)
    {
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
      str0 = realloc(str0, 50 * 1000); str0[49] = 0;
      show_alloc_mem();
  
      str1 = malloc(150644);
      str0 = realloc(str0, 75 * 100); str0[74] = 0;
  
      show_alloc_mem();
      free(str1);
      show_alloc_mem();
      str2 = malloc(175); str2[174] = 0;

      show_alloc_mem();
      free(str0);
      free(str2);
    
      show_alloc_mem();
  
      printf("%d\n", getpagesize());
  
      show_alloc_mem();
      c = 0;
      while (c < 150)
	{
	  i = 0;
	  size = (rand() % 6500 + 1) * 1000;
	  test[c] = malloc(size);
	  show_alloc_mem();
	  while (i < size)
	    test[c][i++] = 0;
	  c++;
	}
      show_alloc_mem(); 
      c = 50;
      while (c < 100)
	free(test[c++]);
      show_alloc_mem(); 
      c = 0;
      while (c < 50)
	free(test[c++]);
      show_alloc_mem(); 
      c = 100;
      while (c < 150)
	free(test[c++]);
      show_alloc_mem(); 

      str0 = malloc(120 + 1);
      c = 0;
      while (c < 120)
	{
	  str0[c] = c + 1;
	  c++;
	}
      str0[c] = 0;
      printf("Test %s\n", str0);
      free(str0);
    }

  c = 0;
  while (c < 10)
    {
      test[c] = NULL;
      testfree[c++] = 0;
    }
  while (1)
    {
      c = rand() % 10;
      size = (rand() % 100 + 1) * 10000;
      if (testfree[c] == 0)
	{
	  test[c] = calloc(size + 1, sizeof(*test[c]));
	  testfree[c] = 1;
	  printf("Malloc %p\n", test[c]);
	}
      else if (rand() % 2)
	{
	  test[c] = realloc(test[c], size);
	  size_t		y = 0;
	  while (y < size)
	    test[c][y++] = 0;
	  printf("Realloc %p\n", test[c]); 
	}
      else
	{
	  free(test[c]);
	  testfree[c] = 0;
	  printf("Free %p\n", test[c]); 
	  test[c] = NULL;
	}
      show_alloc_mem(); 
    }
  
  return (0);
}
