
#include "my_malloc.h"

size_t     my_align(size_t size)
{
  size_t   res;
  size_t   mod;

  res = size;
  mod = res % 4;
  if (mod != 0)
    res += 4 - mod;
  return (res);
}

void            *realloc(void *ptr, size_t size)
{
  t_header      *infos;
  void          *newAllocation;

  if (!ptr || !size)
    return (malloc(size));
  if (size <= 0 && ptr)
    {
      free(ptr);
      return (NULL);
    }
  infos = (t_header *)ptr - 1;
  if (infos->_size >= size)
    return ptr;
  newAllocation = malloc(size);
  if (newAllocation != NULL)
    {
      memcpy(newAllocation, ptr, infos->_size);
      free(ptr);
    }
  return (newAllocation);
}
