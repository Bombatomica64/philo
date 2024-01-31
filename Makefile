NAME = philo

CC = cc -g -Wall -Wextra -Werror
CC_THREAD = cc -fsanitize=thread -g -Wall -Wextra -Werror
SRC =  ft_atoi.c  initialize.c \
 		main.c  print.c  threads.c fork.c death.c time.c \
		info_mutex.c routine.c routine_utils.c ft_strlen.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) -lpthread
	@echo "Compiled "$(NAME)" successfully!"

%.o: %.c
	@$(CC) -c $< -o $@

bonus : 
	@make all -C bonus

all_thread: $(OBJ)
	@$(CC_THREAD)  $(OBJ) -o $(NAME) -lpthread
	@echo "Compiled "$(NAME)" successfully!"

clean:
	@rm -f $(OBJ)
	@make clean -C bonus
	@echo "Cleaned objects successfully!"
fclean: clean
	@rm -f $(NAME)
	@make fclean -C bonus
	@echo "Cleaned "$(NAME)" successfully!"
	
re: fclean all
	@make re -C bonus

replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) -o $(NAME)
	@echo "Let's  gooo!!"

val: re
	@read -p "Enter number of philo: " cmd; \
	read -p "Enter time to die: " cmd2; \
	read -p "Enter time to eat: " cmd3; \
	read -p "Enter time to sleep: " cmd4; \
	read -p "Enter number of times each philo must eat: " cmd5; \
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	./$(NAME) $$cmd $$cmd2 $$cmd3 $$cmd4 $$cmd5

vall: re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes \
	./$(NAME) 3 800 200 200

hell: re
	valgrind  --tool=helgrind \
	./$(NAME) 4 800 200 200 1

.PHONY: all clean fclean bonus re replay