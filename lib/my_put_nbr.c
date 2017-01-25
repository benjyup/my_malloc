/*
** my_put_nbr.c for  in /home/puente_t/rendu/PSU/PSU_2015_minishell1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Jan 21 13:09:45 2016 Timothée Puentes
** Last update Thu Jan 21 13:09:45 2016 Timothée Puentes
*/

#include "my.h"

int	get_intlenght(int nb, int base)
{
  int	c;

  c = 0;
  if (nb < 0)
    nb = nb * -1;
  while (nb >= 1)
    {
      nb = nb / base;
      c++;
    }
  return (c);
}

int	my_put_nbr(int nb)
{
  int	lenght;
  int	s;
  char	number;

  lenght = get_intlenght(nb, 10);
  s = lenght;
  if (nb == -2147483648)
    return (my_putstr("-2147483648"));
  if (nb == 0)
    return (my_putstr("0"));
  if (nb < 0)
    {
      nb = -1 * nb;
      my_putchar(45);
      s++;
    }
  while (lenght != 0)
    {
      number = nb / my_power_it(10, lenght - 1);
      my_putchar(number + 48);
      nb = nb % my_power_it(10, lenght - 1);
      lenght = lenght - 1;
    }
  return (s);
}

int	my_put_nbr_error(int nb)
{
  int	lenght;
  int	s;
  char	number;

  lenght = get_intlenght(nb, 10);
  s = lenght;
  if (nb == -2147483648)
    {
      my_putstr_error("–2147483648");
      return (11);
    }
  if (nb < 0)
    {
      nb = -1 * nb;
      my_putchar_error(45);
    }
  while (nb >= 10)
    {
      number = nb / my_power_it(10, lenght - 1);
      my_putchar_error(number + 48);
      nb = nb % my_power_it(10, lenght - 1);
      lenght = lenght - 1;
    }
  my_putchar_error(nb + 48);
  return (s);
}
