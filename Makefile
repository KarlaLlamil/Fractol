NAME := fractol

SRC_FILES := fractol.c main.c handling_events.c parse_arguments.c
OBJ_FILES := $(SRC_FILES:%.c=%.o)
HEADERS := fractol.h

CC := cc
CFLAGS := -g3 -Wall -Wextra -Werror
CPPFLAGS := -Imlx
LDFLAGS:= -Lmlx
LDLIBS := -lmlx -lXext -lX11 -lm

all : $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o:%.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(OBJ_FILES)
	rm $(NAME)