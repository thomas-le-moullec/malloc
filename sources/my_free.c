#include "my_malloc.h"

pthread_mutex_t global_mutex_free_lock;

void	group_free_blocks(t_header *header)
{
  t_header	*tmp_next;

  tmp_next = header->_next;
  if (header->_next->_next)
    header->_next = header->_next->_next;
  else
    {
      header->_next = NULL;
      global_tail = header;
    }
  header->_size += tmp_next->_size;
}

void	free(void *ptr)
{
  t_header      *header;

  pthread_mutex_lock(&global_mutex_free_lock);
  if (!ptr)
    {
      pthread_mutex_unlock(&global_mutex_free_lock);
      return;
    }
  header = (t_header *)ptr - 1;
  header->_free = TRUE;
  if (header->_next)
    if (header->_next->_free == TRUE)
      {
	group_free_blocks(header);
	pthread_mutex_unlock(&global_mutex_free_lock);
	return ;
      }
  pthread_mutex_unlock(&global_mutex_free_lock);
}
