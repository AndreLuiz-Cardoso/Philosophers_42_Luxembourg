NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC_DIR = src/
INCLUDES = -I $(SRC_DIR)

SRC = $(SRC_DIR)main.c \
      $(SRC_DIR)dinner.c \
      $(SRC_DIR)utils.c \
      $(SRC_DIR)init.c \
      $(SRC_DIR)manager.c \
      $(SRC_DIR)validation.c \
      $(SRC_DIR)actions.c 

OBJ = $(SRC:$(SRC_DIR)%.c=$(SRC_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ)

$(SRC_DIR)%.o: $(SRC_DIR)%.c $(SRC_DIR)philo.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SRC_DIR)*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

