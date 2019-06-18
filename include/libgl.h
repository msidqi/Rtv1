/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:43:22 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/10 05:31:38 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGL_H
# define LIBGL_H

# include <mlx.h>
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>

# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 126
# define DOWN_ARROW 125
# define ZOOM_OUT 78
# define ZOOM_IN 69
# define SPACE 49
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define MOUSE_PRESS_CODE 4
# define MOUSE_MOVE_CODE 6
# define KEY_PRESS_CODE 2
# define RED_BUTTON_CODE 17
# define MAX_ITER 30
# define ABS(Value) (Value >= 0) ? (Value) : -(Value)


typedef struct		t_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct		s_vector3
{
	double			x;
	double			y;
	double			z;
}					t_vector3;

typedef struct		s_startend
{
	t_vector2			start;
	t_vector2			end;
}					t_startend;

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef enum		e_bool
{
	false, true
}					t_bool;

typedef	struct		s_data
{
	t_vector2		worldpos;
	t_color			color;
	t_startend		thread_range;
	int				winwidth;
	int				winheight;
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				*image;
	double			zoom;
	double			movex;
	double			movey;
	double			movez;
	int				endian;
	int				size_line;
	int				bpp;
}					t_data;

typedef struct		s_palette
{
	int				palette[8];
	int				palette_choice;
}					t_palette;

int					ft_window_setup(t_data *data, char *win_name,
											int winheight, int winwidth);
int					ft_image_setup(t_data *data);
void				ft_image_fill(t_data *data, int x, int y, int color);
double				lerp(double x1, double x2, double lerp);
double				ft_get_world_pos(double screen_coord,
								double widthheight, double zoom);
void				ft_refresh_image(t_data *data);
void				ft_mlx_hooks(t_data *data, t_bool ismove);
int					key_press(int key_code, t_data *data);
int					mouse_press(int button, int x, int y, t_data *data);
int					mouse_move(int x, int y, t_data *data);
void				ft_multi_thread(t_data *data, int n_threads, void *(*f)(void *));
void				drawline(t_data *data, int startline, int nlines, int color);
void				drawnsquares(t_data *data, int onedlen);
void				connect_dots(t_data *data, t_vector2 a, t_vector2 b, int color);
void				vec2_init(t_vector2 *a, double x, double y);
void				vec3_init(t_vector3 *a, double x, double y, double z);
t_vector2			vec2_add(t_vector2 a, t_vector2 b);
t_vector3			vec3_add(t_vector3 a, t_vector3 b);
t_vector2			vec2_sub(t_vector2 a, t_vector2 b);
t_vector3			vec3_sub(t_vector3 a, t_vector3 b);
t_vector2			vec2_scalar_multi(t_vector2 a, double factor);
t_vector3			vec3_scalar_multi(t_vector3 a, double factor);
double				vec2_magnitude(t_vector2 a);
double				vec3_magnitude(t_vector3 a);
double				vec2_magnitude_cmp(t_vector2 a, t_vector2 b);
double				vec3_magnitude_cmp(t_vector3 a, t_vector3 b);
t_vector2			vec2_normalize(t_vector2 a);
t_vector3			vec3_normalize(t_vector3 a);
double				vec2_dot_product(t_vector2 a, t_vector2 b);
double				vec3_dot_product(t_vector3 a, t_vector3 b);
t_vector2			vec2_rotate_byangle(t_vector2 a, double angle);
t_vector2			vec2_rotate_byaxis(t_vector2 a, t_vector2 x_axis, t_vector2 y_axis);

#endif
