NAME = push_swap
BONUS_NAME = checker
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c sort.c state.c quick_sort.c
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = checker_bonus.c checker_state_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
$(OBJS): push_swap.h

bonus: $(BONUS_NAME)
$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS)
$(BONUS_OBJS): checker_bonus.h

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
