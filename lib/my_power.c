/*
** my_power_rec.c for  in /home/puente_t/rendu/PSU/PSU_2015_minishell1
**
** Made by Timothée Puentes
** Login   <puente_t@epitech.net>
**
** Started on  Thu Jan 21 13:09:36 2016 Timothée Puentes
** Last update Thu Jan 21 13:09:36 2016 Timothée Puentes
*/

int		my_power_it(int nb, int power)
{
  int		c;
  int		result;

  c = 0;
  result = 1;
  while (c != power)
    {
      result = result * nb;
      c++;
    }
  return (result);
}

unsigned long	my_power_uit(int nb, int power)
{
  int		c;
  unsigned long	result;

  c = 0;
  result = 1;
  while (c != power)
    {
      result = result * nb;
      c++;
    }
  return (result);
}

int		loop_power(int nb, int power, int c)
{
  if (c == power)
    return (nb);
  c++;
  nb = loop_power(nb, power, c);
  return (nb);
}

int		my_power_rec(int nb, int power)
{
  int		c;
  int		result;

  result = 1;
  c = 0;
  result = loop_power(nb , power, c);
  return (result);
}
