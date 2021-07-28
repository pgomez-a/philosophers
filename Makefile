NAME	= philo

SRCS	= srcs/main.c		\
	  srcs/philo.c		\
	  srcs/init_philo.c	\
	  srcs/action_philo.c	\
	  srcs/ph_utils.c

OBJS	= ${SRCS:.c=.o}

CC	= gcc

#CFLAGS	= -Wall -Werror -Wextra

RM	= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	@ $(CC) $(OBJS) -o $(NAME)

clean:
	@ $(RM) $(OBJS)

fclean:		clean
	@ $(RM) $(NAME)

re:		fclean all
