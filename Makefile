# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/30 17:00:55 by widraugr          #+#    #+#              #
#    Updated: 2019/08/30 17:13:12 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = count_args.c\
		draw_line_adr.c\
		main.c\
		press_key.c\
		projection.c\
		put_map.c\
		put_pixel_adr.c\
		put_two_line.c\
		working_string.c

SRC_PATH = source/

RC_COMPL = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:%.c=%.o)

FLAGS = -Wextra -Werror -Wall

HFILES = -I /usr/local/include -I ./libft

FLAGSMLX = -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

FLAGSPRINTF = -L ./libft -lftprintf

all: $(NAME)

$(NAME):
	make -C ./libft
	gcc $(FLAGS) $(HFILES) -c $(RC_COMPL)
	gcc $(FLAGS) $(OBJ) $(FLAGSMLX) $(FLAGSPRINTF) -o $(NAME)

clean:
	make clean -C ./libft
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft
	/bin/rm -f $(NAME)
	
re: fclean all
	make re -C ./libft
