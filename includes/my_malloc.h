#ifndef MY_MALLOC_H_
#define	MY_MALLOC_H_

#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define TRUE	1
#define FALSE	2

typedef struct          s_header
{
  struct s_header       *_next;
  unsigned int          _size;
  char                  _free;
  char			_data[3];
}			t_header;

extern t_header        *global_head;
extern t_header        *global_tail;

#define ALLOC_SIZE sizeof(struct s_header)

void            *malloc(size_t);
t_header        *get_available_block(size_t);
void		free(void *);
void            *realloc(void *, size_t);
void		*calloc(size_t, size_t);
void		show_alloc_mem();
size_t          my_align(size_t);
void		my_putstr(char *);
void		my_putnbr_base(long, char *);

#endif
