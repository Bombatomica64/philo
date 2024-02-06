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
	@make all -C ../philo_bonus

all_thread: $(OBJ)
	@$(CC_THREAD)  $(OBJ) -o $(NAME) -lpthread
	@echo "Compiled "$(NAME)" successfully!"

clean:
	@rm -f $(OBJ)
	@make clean -C ../philo_bonus
	@echo "Cleaned objects successfully!"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ../philo_bonus
	@echo "Cleaned "$(NAME)" successfully!"
	
re: fclean all
	@make re -C ../philo_bonus

replay:
	@rm -f $(NAME)
	@$(CC) $(SRC) -o $(NAME)
	@echo "Let's  gooo!!"

.PHONY: all clean fclean bonus re replay
