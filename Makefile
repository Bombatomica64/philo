
NAME = philo

CC = cc -g -Wall -Wextra -Werror

SRC = main.c initialize.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "Compiled "$(NAME)" successfully!"

%.o: %.c
	@$(CC) -c $< -o $@

bonus : all

clean:
	@rm -f $(OBJ)
	@echo "Cleaned objects successfully!"
	
fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned "$(NAME)" successfully!"
	
re: fclean all
	make re -C $(FT_PRINTF)


replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIBRARY) -o $(NAME)
	@echo "Let's  gooo!!"

bonus : all

.PHONY: all clean fclean bonus re replay
