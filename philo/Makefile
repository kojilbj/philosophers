CC=cc
FLAGS=-Werror -Wall -Wextra
#FLAGS+=-g -fsanitize=thread
NAME=philo
SRC=main.c init.c seating_philos.c \
	philo_action.c write.c validate.c get_time.c \
	threads.c check.c sleep.c
OBJS=$(SRC:.c=.o)

all:$(NAME)
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
