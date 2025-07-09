NAME = RPN
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp RPN.cpp
OBJ_F = ./obj
obj = $(SRC:%.cpp=$(OBJ_F)/%.o )
RM = rm -rf

all: $(NAME)

$(NAME): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $(NAME) 

$(OBJ_F)/%.o: %.cpp
	@mkdir -p $(OBJ_F)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ_F) $(obj)

fclean: clean
	$(RM) $(NAME) 

re: fclean all

.Phony: clean fclean re all
