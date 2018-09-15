#include "my_malloc.h"

void	*calloc(size_t num, size_t nsize)
{
  void *ptr;
  size_t size;

  if (!num || !nsize)
    return NULL;
  size = num * nsize;
  if (nsize != size / num)
    return NULL;
  ptr = malloc(size);
  if (!ptr)
    return NULL;
  memset(ptr, 0, size);
  return (ptr);
}
