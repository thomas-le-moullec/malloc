#include "my_malloc.h"

t_header	*global_head = NULL;
t_header	*global_tail = NULL;
pthread_mutex_t global_mutex_malloc_lock;

t_header	*get_available_block(size_t size)
{
  t_header	*block;

  block = global_head;
  while (block)
    {
      if (block->_free == TRUE && block->_size >= size)
	return (block);
      block = block->_next;
    }
  return (NULL);
}

void		*use_existing_header(t_header *header, size_t size)
{
  t_header	*new;
  unsigned int	tmp_size;

  tmp_size = header->_size;
  header->_size = size;
  header->_free = FALSE;
  if (tmp_size > header->_size + ALLOC_SIZE + 1)
    {
      new = (void *)(header + 1) + header->_size;
      new->_size = tmp_size - size - ALLOC_SIZE;
      new->_next = header->_next;
      new->_free = TRUE;
      header->_next = new;
      if (global_tail != NULL && header == global_tail)
	{
	  global_tail = new;
	  global_tail->_next = NULL;
	}
    }
  pthread_mutex_unlock(&global_mutex_malloc_lock);
  return (void *)(header + 1);
}

unsigned int	size_to_alloc(size_t size)
{
  unsigned int	totalsize;
  unsigned int	twpagesize;

  twpagesize = (int)getpagesize() * 20;
  totalsize = twpagesize;
  while (totalsize <= size + ALLOC_SIZE + ALLOC_SIZE + 1)
    totalsize += twpagesize;
  return (totalsize);
}

void		*allocate_new(t_header *header, size_t size)
{
  t_header	*new;
  unsigned int	totalsize;

  totalsize = size_to_alloc(size);
  header = sbrk(totalsize);
  if (header == (void*) - 1)
    return (NULL);
  header->_size = size;
  header->_free = FALSE;
  new = (void *)(header + 1) + header->_size;
  new->_size = totalsize - ALLOC_SIZE - size - ALLOC_SIZE;
  new->_next = NULL;
  new->_free = TRUE;
  header->_next = new;
  if (global_tail)
    global_tail->_next = header;
  global_tail = new;
  return (header);
}

void		*malloc(size_t size)
{
  t_header	*header;

  pthread_mutex_lock(&global_mutex_malloc_lock);
  if (!size)
    {
      pthread_mutex_unlock(&global_mutex_malloc_lock);
      return (NULL);
    }
  size = my_align(size);
  header = get_available_block(size);
  if (header)
    return (use_existing_header(header, size));
  else
    header = allocate_new(header, size);
  if (!global_head)
    global_head = header;
  pthread_mutex_unlock(&global_mutex_malloc_lock);
  return (void *)(header + 1);
}
