NAME = a.out
CXX = clang++
CXXFLAGS = # -Wall -Werror -Wextra -I ./
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
	./a.out

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
