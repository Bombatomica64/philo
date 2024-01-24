
NAME = philo

CC = cc -fsanitize=thread -g -Wall -Wextra -Werror

SRC = checks.c  free.c  ft_atoi.c  initialize.c \
 		main.c  print.c  threads.c fork.c death.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME) -lpthread
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

replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) -o $(NAME)
	@echo "Let's  gooo!!"

bonus : all

val: all
	@read -p "Enter number of philo: " cmd; \
	read -p "Enter time to die: " cmd2; \
	read -p "Enter time to eat: " cmd3; \
	read -p "Enter time to sleep: " cmd4; \
	read -p "Enter number of times each philo must eat: " cmd5; \
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	./$(NAME) $$cmd $$cmd2 $$cmd3 $$cmd4 $$cmd5

vall: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	./$(NAME) 3 800 200 200 1

hell: all
	valgrind  --tool=helgrind \
	./$(NAME) 1 800 200 200 1

.PHONY: all clean fclean bonus re replay
