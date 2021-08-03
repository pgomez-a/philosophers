NAME	= philo

SRCS	= main.c		\
	  philo.c		\
	  init_philo.c		\
	  action_philo.c	\
	  ph_utils.c

OBJS	= ${SRCS:.c=.o}

CC	= gcc

CFLAGS = -Wall -Wextra -Werror

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@ $(RM) $(OBJS)

fclean:		clean
	@ $(RM) $(NAME)

re:		fclean all
