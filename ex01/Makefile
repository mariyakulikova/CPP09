NAME    = RPN
CXX     = c++
CXXFLAGS= -Wextra -Wall -Werror -std=c++98 -MMD
RM      = rm -f

SRCS    = main.cpp RPN.cpp
OBJS    = $(SRCS:.cpp=.o)
DEPS    = $(OBJS:.o=.d)
-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL := all
