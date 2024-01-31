NAME = philo_bonus

CC = cc -g -Wall -Wextra -Werror -pthread

SRC =	death_bonus.c	main.c	routine_bonus.c	time_bonus.c \
		initialize_bonus.c  process.c   semaphores.c ft_atoi_bonus.c \
		../ft_strlen.c

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