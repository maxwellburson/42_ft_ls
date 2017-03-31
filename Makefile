# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburson <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/23 19:31:26 by mburson           #+#    #+#              #
#    Updated: 2017/02/23 19:31:28 by mburson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBFTPRINTF = ./src/ft_printf/libftprintf.a
LIBFTPRINTF_DIR = ./src/ft_printf

SRC = \
	$(addprefix ./src/, \
		entry_lst_sort.c \
		find_widths.c \
		free.c \
		ft_ls.c \
		get_dir_info.c \
		ls_path.c \
		open_paths.c \
		parse_flags.c \
		$(addprefix print/, \
			entry_long_wwidths.c \
			print_directory.c \
			print_long.c \
		) \
	)

OBJ = $(SRC:.c=.o)

HEADERS = -I ./src -I $(LIBFTPRINTF_DIR) -I $(LIBFTPRINTF_DIR)/libft

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIBFTPRINTF)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) $(HEADERS) -c -o $@ $<

$(LIBFTPRINTF): force
	@echo "\033[1mlibftprintf\033[0m"
	cd $(LIBFTPRINTF_DIR) && $(MAKE)

force:
	@true

clean:
	rm -f $(OBJ)
	cd ./$(LIBFTPRINTF_DIR) && $(MAKE) fclean
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
