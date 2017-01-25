/*
** my_strlen.c for  in /home/puente_t/rendu/PSU/PSU_2015_minishell1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Jan 21 13:08:37 2016 Timothée Puentes
** Last update Thu Jan 21 13:08:38 2016 Timothée Puentes
*/

#include <stdlib.h>

int	my_strlen(char *str)
{
  int	n;

  if (str == NULL)
    return (0);
  n = 0;
  while (str[n] != '\0')
    n++;
  return (n);
}
