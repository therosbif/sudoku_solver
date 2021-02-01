NAME	= sudoku

CC	= g++

RM	= rm -f

SRCS	= ./src/main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS = -I ./include/
CPPFLAGS += -Wall -Wextra -g3

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
