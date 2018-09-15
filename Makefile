DETAILS     	= yes

DEBUG       	= no

RM      	= rm -rf

CC      	= gcc

SRCSPATH    	= ./sources/

SRCS        	=	$(SRCSPATH)my_malloc.c			\
	      	  	$(SRCSPATH)my_free.c			\
		  	$(SRCSPATH)my_realloc.c			\
			$(SRCSPATH)show_alloc_mem.c		\
			$(SRCSPATH)my_calloc.c			\

NAMELIB     	= libmy_malloc.so

FLAGS1      	+= -W -Wall -Werror -Wextra

FLAGSINC    	= -I ./includes/

ifeq ($(DEBUG),yes)
        FLAGS1  += -g
endif

OBJ    	 	= $(SRCS:.c=.o)

all:        $(NAMELIB)

$(NAMELIB):

ifeq ($(DETAILS),yes)
	$(CC) -c $(FLAGS1) $(FLAGSINC) -fpic $(SRCS)
	$(CC) -shared -o $(NAMELIB) *.o

else
	@echo "Compiling with Position Independent Code..."
	@$(CC) -c $(FLAGS1) $(FLAGSINC) -fpic $(SRCS)
	@echo "Creating a shared library from an object file..."
	@$(CC) -shared -o $(NAMELIB) *.o

endif

clean:
	@echo "Cleaning object files ..."
	@$(RM) *.o
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning files ..."
	@$(RM) $(NAMELIB)
	@echo "Files cleaned."

re: fclean all
