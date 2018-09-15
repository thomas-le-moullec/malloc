#include "my_malloc.h"

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    write(1, &str[i++], 1);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i]  != '\0')
    i++;
  return (i);
}

void    my_putnbr_base(long nbr, char *str)
{
  long   x;
  long   b;

  x = 1;
  b = my_strlen(str);
  while (nbr / x >= b)
    x = x * b;
  while (x)
    {
      write(1, &str[(nbr / x)], 1);
      nbr = nbr % x;
      x = x / b;
    }
}

void	show_alloc_mem()
{
  t_header	*block;

  my_putstr("break : 0x");
  my_putnbr_base((long)(void *)sbrk(0), "0123456789abcdef");
  my_putstr("\n");
  block = global_head;
  while (block && (block != global_tail || block == global_head))
    {
      my_putstr("0x");
      my_putnbr_base(((long)(void *)(block + 1)), "0123456789abcdef");
      my_putstr(" - 0x");
      my_putnbr_base(((long)(void *)(block + 1) + block->_size), \
		     "0123456789abcdef");
      my_putstr(" : ");
      my_putnbr_base((long)block->_size, "0123456789");
      my_putstr(" bytes\n");
      block = block->_next;
    }
}
