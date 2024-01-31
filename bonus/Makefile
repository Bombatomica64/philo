NAME = philo_bonus

CC = cc -g -Wall -Wextra -Werror

SRC =  ../ft_atoi.c  initialize_bonus.c \
	../time.c ../routine.c ../routine_utils.c ../ft_strlen.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "Compiled "$(NAME)" successfully!"

clean:
	@rm -f $(OBJ)
	@echo "Cleaned objects successfully!"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned "$(NAME)" successfully!"

re: fclean all

.PHONY: all clean fclean re