NAME = philo
INCLUDE = ./include
SRC = src/check.c  src/exit.c src/init.c src/simulation.c src/utils.c src/main.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g $(OBJ) -fsanitize=thread -lpthread -o $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
