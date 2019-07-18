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
SRC = connect_dots.c ft_event_system_mlx.c ft_get_plane_config.c \
ft_plane_functions.c ft_vector_sub.c drawline.c ft_events_keyboard.c \
ft_get_ray_to_light.c ft_sphere_functions.c get_next_line.c \
drawsquares.c ft_expect.c ft_get_sphere_config.c ft_utils_func.c interface.c \
ft_atof.c ft_expect_matrix.c ft_image_setup_mlx.c ft_vec_create.c \
ft_camera.c ft_get_camera_config.c ft_light_intersection.c \
ft_vec_cross_dot_prod.c main.c ft_color_operations.c ft_get_cone_config.c \
ft_matrix_operations.c ft_vec_destroy.c ft_cone_functions.c ft_get_config.c \
ft_min_max.c ft_vec_normalize_magnitude.c ft_cylinder_functions.c \
ft_get_cylinder_config.c ft_multi_thread.c ft_vec_scalar.c ft_draw.c \
ft_get_light_config.c ft_palette.c ft_vector_add.c ft_error_management.c \
ft_get_matrix.c ft_parsing_tools.c ft_vector_operations.c
SRC_PATH_PARSER = src/parser/
INCLUDE = include
OBJ = $(SRC:.c=.o)
GLIB = libgl.a
CC = gcc -Wall -Wextra -Werror 
FLAGS = -framework OpenGl -framework Appkit

all : $(NAME)

$(GLIB) : 
	@$(CC) -c $(addprefix $(SRC_PATH),$(SRC))  -I $(INCLUDE)
	# $(addprefix $(SRC_PATH_PARSER),$(SRC_PARSER))
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
