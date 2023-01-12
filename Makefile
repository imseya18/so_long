NAME		:= so_long
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		:= ./MLX42
FTPRINTF	:= ./printf

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(FTPRINTF)/libftprintf.a $(LIBMLX)/libmlx42.a -lglfw -L "/Users/mmorue/.brew/opt/glfw/lib/" -lm 
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

ftprintf:
	@$(MAKE) -C $(FTPRINTF)

libmlx:
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) ftprintf 
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(FTPRINTF) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(FTPRINTF) clean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx