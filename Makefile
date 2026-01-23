NAME = 	gnl.a
SRCS =	get_next_line_single.c get_next_line_utils.c get_next_line_mul.c
OBJS = 	$(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP
DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $^

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)