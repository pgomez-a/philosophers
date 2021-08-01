NAME	= philo

SRCS	= srcs/main.c		\
	  srcs/philo.c		\
	  srcs/init_philo.c	\
	  srcs/action_philo.c	\
	  srcs/ph_utils.c

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
