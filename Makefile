NAME := fractol
SRC_FILES := fractol.c
OBJ_FILES := $(SRC_FILES:%.c=%.o)
HEADERS := fractol.h

CC := cc
C_FLAGS := -g3 -Wall -Wextra -Werror
CPP_FLAGS := $()

all : $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(C_FLAGS)

$(OBJ_FILES):%.o:%.c $(HEADERS)
	$(CC) -c $(CPP_FLAGS) $(C_FLAGS)

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(OBJ_FILES)