NAME = philo_bonus

HEADER = philo.h
INCLUDES = -I.

SRC_PATH = srcs
OBJ_PATH = objs

SRC = main.c parsing.c init.c routine.c monitor.c utils.c utils2.c

SRC := $(addprefix $(SRC_PATH)/, $(SRC))
OBJ = $(patsubst %.c,$(OBJ_PATH)/%.o,$(SRC))

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 $(INCLUDES) -pthread

all: $(NAME)

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : ${OBJ} $(HEADER) Makefile
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean: 
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus