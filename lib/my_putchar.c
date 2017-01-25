/*
** my_putchar.c for  in /home/puente_t/rendu/PSU/PSU_2015_minishell1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Jan 21 13:05:54 2016 Timothée Puentes
** Last update Thu Jan 21 13:05:55 2016 Timothée Puentes
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write (1, &c, 1);
}

void	my_putchar_error(char c)
{
  write (2, &c, 1);
}
