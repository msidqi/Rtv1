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

NAME = rtv1
LIBFT = libft.a
LIBGL = libgl.a
LIBMLX = libmlx.a
LIBFTL = src/libft/libft.a
LIBGLL = src/libgl/libgl.a
LIBMLXL = src/minilibx_macos/libmlx.a
SRC_PATH = src
GLSRC_PATH = src/libgl
SRC = connect_dots.c ft_event_system_mlx.c ft_get_plane_config.c \
ft_plane_functions.c ft_vector_sub.c drawline.c ft_events_keyboard.c \
ft_get_shadow_ray.c ft_sphere_functions.c get_next_line.c \
drawsquares.c ft_expect.c ft_get_sphere_config.c ft_utils_func.c interface.c \
ft_atof.c ft_expect_matrix.c ft_image_setup_mlx.c ft_vec_create.c \
ft_camera.c ft_get_camera_config.c ft_light_intersection.c \
ft_vec_cross_dot_prod.c ft_color_operations.c ft_get_cone_config.c \
ft_matrix_operations.c ft_vec_destroy.c ft_cone_functions.c ft_get_config.c \
ft_min_max.c ft_vec_normalize_magnitude.c ft_cylinder_functions.c \
ft_get_cylinder_config.c ft_vec_scalar.c ft_draw_scene.c \
ft_get_light_config.c ft_palette.c ft_vector_add.c ft_error_management.c \
ft_get_matrix.c ft_parsing_tools.c ft_vector_operations.c ft_multi_thread.c
INCLUDE = include
INC = include/libft.h include/libgl.h
OBJS_DIR = .objs
CC = sudo gcc -Wall -Wextra -Werror 
FLAGS_LINUX = -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lm -lpthread
FLAGS = -framework OpenGl -framework Appkit -lmlx
OBJ = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

all : $(NAME)

$(OBJ) : $(OBJS_DIR)/%.o : $(GLSRC_PATH)/%.c $(INC)| $(OBJS_DIR)
	$(CC) -c $< -o $@ -I$(INCLUDE)
$(LIBGLL) : $(OBJ)
	sudo ar rc $@ $^
	sudo ranlib $@
$(LIBFTL) :
	make -C $(SRC_PATH)/libft
$(NAME) : $(LIBFTL) $(LIBGLL) $(SRC_PATH)/main.c
	$(CC) -o $@ $< src/libgl/*.c src/libft/src/*.c $(word 3,$^) $(FLAGS_LINUX) -I$(INCLUDE)
	#$(CC) -o $@ $< $(word 2,$^) $(word 3,$^) $(FLAGS_LINUX) -I$(INCLUDE)

clean : 
	rm -rf $(OBJ) $(LIBGLL) $(LIBFTL)
	make clean -C $(SRC_PATH)/libft
fclean : clean
	rm -rf $(NAME)
	make fclean -C $(SRC_PATH)/libft
re : fclean all

$(OBJS_DIR):
	mkdir $(OBJS_DIR)