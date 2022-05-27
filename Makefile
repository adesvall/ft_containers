FT			= ft_stl
STD			= std_stl

SRCS		= official_main.cpp

CFLAGS		= -std=c++98 -Wall -Wextra -Werror -I.

all:		FT STD

FT:		$(SRCS) vector.hpp map.hpp stack.hpp
			c++ $(CFLAGS) $(SRCS) -o $(FT)

STD:		$(SRCS) vector.hpp map.hpp stack.hpp
			c++ $(CFLAGS) -D STD $(SRCS) -o $(STD)

fclean:		
			rm -f $(FT) $(STD)

re:			fclean all

.PHONY:		all clean fclean re