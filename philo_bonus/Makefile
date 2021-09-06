NAME	= philo_bonus

SRCS	= main_bonus.c			\
	  execute_philos_bonus.c	\
	  wait_philos_bonus.c		\
	  action_philo_bonus.c		\
	  ph_utils_bonus.c

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
