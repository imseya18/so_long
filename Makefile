NAME		:= so_long
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		:= ./MLX42
FTPRINTF	:= ./printf
GNL			:= ./get_next_line
MM 			:= ./memory_manager_2
HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(GNL)/gnl.a $(FTPRINTF)/libftprintf.a $(LIBMLX)/libmlx42.a $(MM)/memory_mng.a -lglfw -L "/Users/mmorue/.brew/opt/glfw/lib/" -lm 
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

gnl:
	@$(MAKE) -C $(GNL)

ftprintf:
	@$(MAKE) -C $(FTPRINTF)

libmlx:
	@$(MAKE) -C $(LIBMLX)

mm:
	@$(MAKE) -C $(MM)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) ftprintf gnl mm
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) 

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(GNL) clean
	@$(MAKE) -C $(FTPRINTF) clean
	@$(MAKE) -C $(LIBMLX) clean
	@$(MAKE) -C $(MM) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(GNL) fclean
	@$(MAKE) -C $(FTPRINTF) fclean
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C $(MM) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx