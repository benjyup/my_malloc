/*
** my.h for  in /home/timothee/rendu/PSU_2015_my_printf/lib/my
**
** Made by puente_t
** Login   <timothee@epitech.net>
**
** Started on  Wed Nov  4 16:24:31 2015 puente_t
** Last update Mon Feb  1 11:30:07 2016 Timothée Puentes
*/

#ifndef MY_H_
# define MY_H_

# include <stdarg.h>

# define	IS_NUM(c) ((c >= 32 && c <= 127) ? (1) : (0))
# define	IS_N(c) ((c >= '0' && c <= '9') ? (1) : (0))

int		my_atoi(char *s);
int		my_printf(char *s, ...);
int		sum_stdarg(int i, int nb, ...);
int		disp_stdarg(char *s, ...);
char		*int_tobase(unsigned int nbr, char *base);
void		my_putstrn(char *str);
void		my_putchar(char c);
int		my_put_nbr_error(int nb);
void		my_putstr_error(char *str);
void		my_putchar_error(char c);
int	       	my_isneg(int nb);
int		my_put_nbr(int nb);
int		my_put_unbr(unsigned int nb);
void		my_swap(char *a, char *b);
int		my_putstr(char *str);
int		my_strlen(char *str);
int		my_getnbr(char *str);
int		my_getnbrn(char *str, int n);
int		my_power_rec(int nb, int power);
int		my_power_it(int nb, int power);
unsigned long	my_power_uit(int nb, int power);
int		my_square_root(int nb);
int		my_is_prime(int nb);
int		my_find_prime_sup(int nb);
char		*my_strcpy(char *dest, char *src);
char		*my_strncpy(char *dest, char *src, int n);
char		*my_revstr(char *str);
char		*my_strstr(char *str, char *to_find);
int		my_strcmp(char *s1, char *s2);
int		my_strncmp(char *s1, char *s2, int n);
char		*my_strupcase(char *str);
char		*my_strlowcase(char *str);
char		*my_strcapitalize(char *str);
int		my_str_isalpha(char *str);
int		my_str_isnum(char *str);
int		my_str_islower(char *str);
int		my_str_isupper(char *str);
int		my_str_isprintable(char *str);
int		my_showstr(char *str);
int		my_showmem(char *str, int size);
char		*my_strcat(char *dest, char *src);
char		*my_strncat(char *dest, char *src, int nb);
char		*my_strdup(char *src);
char		*my_strndup(char *src, int n);
void		my_show_wordtab(char **tab);
char		**my_str_to_wordtab(char *str);
int		get_intlenght(int nb, int base);

int		get_ulonglenght(unsigned long nb, int base);
int		my_putulong_printf(unsigned long  nb, int lenght, char *b);
int		my_putnbr_printf(unsigned int nb, int lenght, char *b);

int		print_str(va_list arg, int printed);
int		print_str_unp(va_list arg, int printed);
int		print_int(va_list arg, int printed);
int		print_uint(va_list arg, int printed);
int		print_uint_bi(va_list arg, int printed);
int		print_uint_oct(va_list arg, int printed);
int		print_uint_hexa_l(va_list arg, int printed);
int		print_uint_hexa_c(va_list arg, int printed);
int		print_char(va_list arg, int printed);
int		print_void(va_list arg, int printed);
int		print_assign(va_list arg, int printed);
int		print_error(va_list arg, int printed);

extern int sys_nerr;
extern const char *const sys_errlist[];

#endif /* !MY_H_ */
