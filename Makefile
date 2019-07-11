# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msidqi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 00:08:25 by msidqi            #+#    #+#              #
#    Updated: 2019/05/14 16:02:41 by msidqi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft.a
LIBMLXL = libmlx.a
LIBFTL = src/libft/libft.a
GLIB = libgl.a
LIBMLXL = src/minilibx_macos/libmlx.a
NAME = RTv1
SRC_PATH = src/
SRC = connect_dots.c drawline.c ft_event_system_mlx.c ft_events_keyboard.c ft_multi_thread.c ft_utils_func.c interface.c drawsquares.c ft_image_setup_mlx.c ft_palette.c ft_vector_operations.c ft_matrix_operations.c ft_get_config.c
INCLUDE = include
OBJ = $(SRC:.c=.o)
GLIB = libgl.a
CC = gcc -Wall -Wextra -Werror 
FLAGS = -framework OpenGl -framework Appkit

all : $(NAME)

$(GLIB) : 
	@$(CC) -c $(addprefix $(SRC_PATH),$(SRC)) -I $(INCLUDE)
	@ar rc $(GLIB) $(OBJ)
	@ranlib $(GLIB)
$(LIBFTL) : 
	@make re -C $(SRC_PATH)libft
	#@make re -C $(SRC_PATH)minilibx_macos	
$(NAME) : $(LIBFTL) $(GLIB)
	@$(CC) -o $(NAME) $(SRC_PATH)main.c $(GLIB) $(LIBFTL)  -I $(INCLUDE) $(FLAGS) -lmlx
	#$(LIBMLXL)

clean : 
	@rm -rf $(OBJ) $(GLIB) $(LIBFTL)
	@make clean -C $(SRC_PATH)libft
	#@make clean -C $(SRC_PATH)minilibx_macos
fclean : clean
	@rm -rf $(NAME)
	@make fclean -C $(SRC_PATH)libft
re : fclean all
