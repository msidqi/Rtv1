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
# include <fcntl.h>

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
# define NUM_LOCK_9 92
# define NUM_LOCK_8 91
# define NUM_LOCK_7 89
# define NUM_LOCK_6 88
# define NUM_LOCK_5 87
# define NUM_LOCK_4 86
# define NUM_LOCK_3 85
# define NUM_LOCK_2 84
# define NUM_LOCK_1 83
# define NUM_LOCK_0 82
# define MOUSE_PRESS_CODE 4
# define MOUSE_MOVE_CODE 6
# define KEY_PRESS_CODE 2
# define RED_BUTTON_CODE 17
# define ABS(Value) (Value >= 0) ? (Value) : -(Value)
# define MAX_ITER 30
# define VERTEX 0
# define VECTOR 1
# define DIRECTION 2
# define MATRIX 3
# define TRANSLATION_MATRIX 0
# define ROTATION_MATRIX 1
# define SCALING_MATRIX 2
# define NEAR 1e-6
# define FAR 1e30
# define POINT_LIGHT 0
# define DIRECTIONAL_LIGHT 1
# define SPOT_LIGHT 2
# define AREA_LIGHT 3
# define SPHERE 0
# define PLANE 1
# define CONE 2
# define CYLINDER 3
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0xFF
# define BLACK 0x0
# define WHITE 0xFFFFFF
# define AMBIENT_R 0.4
# define AMBIENT_G 0.4
# define AMBIENT_B 0.4
# define SPECULAR_POW 80
# define HEIGHT 720
# define WIDTH 1280
# define ASPECT_RATIO HEIGHT / WIDTH

typedef struct		t_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_matrix
{
	unsigned int	cols;
	unsigned int	rows;
	double			**v;
}					t_matrix;

typedef struct		s_vec4
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vec4;


/*
** Homogenous Coordinates
**   F U R  T   (Forward/Up/Right/Translation Vector)
** [[1 0 0] 0]
** [[0 1 0] 0]
** [[0 0 1] 0]
** [ 0 0 0  1] 0 Direction Vector 1 Position Vector
** FUR == unit vectors describing object orientation. aka vector basis
**
*/
typedef struct		s_matrix4
{
	short			type;
	double			v[4][4];
}					t_matrix4;

typedef struct		s_startend
{
	t_vec2			start;
	t_vec2			end;
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
 
typedef struct		s_ray // P(t) = origin + t * dir
{
	t_vec4			origin; // vector to origin point
	t_vec4			dir; // direction vector
	double			t; // distance
}					t_ray;

typedef	struct		t_light
{
	double			i_r; // intensity rgb(1.0, 0.0, 0.0) == red
	double			i_g;
	double			i_b;
	t_vec4			origin;
}					t_light;

typedef struct		s_camera
{
	t_vec4			to;
	t_vec4			pos;
	double			l;
	double			bigl;
	double			focal_length;
	int				n;
	t_vec4			up;
	t_vec4			forward;
	t_vec4			left;
}					t_camera;

typedef	struct		s_data
{
	t_list			*light_list;
	t_list			*scene;
	t_camera		cam;
	// t_vec4			worldpos;
	t_color			color;
	t_startend		thread_range;
	unsigned int	winwidth;
	unsigned int	winheight;
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				*image;
	int				endian;
	int				size_line;
	int				bpp;
}					t_data;

typedef	struct		s_sphere
{
	double			specular;
	t_vec4			diffuse;
	t_vec4			center;
	double			radius;
	unsigned int	color;

}					t_sphere;

typedef	struct		s_plane
{
	double			specular;
	t_vec4       	diffuse;
	t_vec4			normal;
	t_vec4			point;
	unsigned int	color;
}					t_plane;

typedef	struct		s_cone
{
	double			specular;
	t_vec4			diffuse;
	t_vec4			axis;
	t_vec4			center;
	double			half_angle;
	unsigned int	color;
}					t_cone;

typedef	struct		s_cylinder
{
	double			specular;
	t_vec4			diffuse;
	t_vec4			axis;
	t_vec4			point;
	double			radius;
	unsigned int	color;
}					t_cylinder;

typedef struct		s_shader_x
{
	t_vec4       	diff;
	t_vec4       	spec;
}					t_shader_x;

typedef struct		s_shader
{
	unsigned int	diffuse;
	unsigned int	specular;
	unsigned int	ambient;
}					t_shader;

typedef struct		s_palette
{
	int				palette[8];
	int				palette_choice;
}					t_palette;

typedef struct		s_obj_function
{
	size_t			type;
	int				(*call)();
	unsigned int	(*call2)();
}					t_obj_function;

int					ft_window_setup(t_data *data, char *win_name,
											int winheight, int winwidth);
int					ft_image_setup(t_data *data);
void				ft_image_fill(t_data *data, int x, int y, int color);
double				lerp(double x1, double x2, double lerp);
double				ft_get_world_pos(double screen_coord,
								double widthheight, double zoom);
void				ft_refresh_image(t_data *data);
void				ft_mlx_hooks(t_data *data, t_bool ismove);
int					no_event_mouse_move(int x, int y, t_data *data);
int					key_press(int key_code, t_data *data);
int					mouse_press(int button, int x, int y, t_data *data);
int					mouse_move(int x, int y, t_data *data);
void				ft_multi_thread(t_data *data, int n_threads, void *(*f)(void *));
void				drawline(t_data *data, int startline, int nlines, int color);
void				drawnsquares(t_data *data, unsigned int onedlen);
void				connect_dots(t_data *data, t_vec2 a, t_vec2 b, int color);
void				ft_create_vec2(t_vec2 *a, double x, double y);
void				ft_create_vec3(t_vec3 *a, double x, double y, double z);
t_vec2				ft_vec2_add(t_vec2 a, t_vec2 b);
t_vec3				ft_vec3_add(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_sub(t_vec2 a, t_vec2 b);
t_vec3				ft_vec3_sub(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_scalar(t_vec2 a, double factor);
t_vec3				ft_vec3_scalar(t_vec3 a, double factor);
double				ft_vec2_mag(t_vec2 a);
double				ft_vec3_mag(t_vec3 a);
double				ft_vec2_mag_cmp(t_vec2 a, t_vec2 b);
double				ft_vec3_mag_cmp(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_normalize(t_vec2 a);
t_vec3				ft_vec3_normalize(t_vec3 a);
double				ft_vec2_dot_product(t_vec2 a, t_vec2 b);
double				ft_vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_rotate_byangle(t_vec2 a, double angle);
t_vec2				ft_vec2_rotate_byaxis(t_vec2 a, t_vec2 x_axis, t_vec2 y_axis);
t_matrix			*ft_create_matrix(unsigned int rows, unsigned int cols);
t_matrix4			ft_create_matrix4();
int					ft_destroy_matrix(t_matrix *mat);
void				ft_putmatrix(t_matrix *mat);
void				ft_putmatrix4(t_matrix4 *mat);
t_matrix4			ft_get_translation_matrix4(t_matrix4 mat, double x, double y, double z);
t_vec4				ft_create_vec4(double x, double y, double z, double w) ;
void				ft_putvec4(t_vec4 *vec);
t_vec4				ft_matrix_x_vector(t_matrix4 mat, t_vec4 vec);
void				ft_printvec4(t_vec4 *vec);//don't forget to remove this
t_vec4				ft_vec4_sub(t_vec4 vec1, t_vec4 vec2);
t_vec4    			ft_vec4_normalize(t_vec4 a);
double    			ft_vec4_mag(t_vec4 a);
double				ft_vec4_dot_product(t_vec4 a, t_vec4 b);
void				ft_draw(t_data *data);
void				ft_printmatrix4(t_matrix4 *mat);
t_vec4 	   			ft_vec4_cross_product(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_add(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_scalar(t_vec4 a, double factor);
int					ft_plane_inter(t_ray *ray, t_plane *plane);
int					ft_sphere_inter(t_ray *ray, t_sphere *sphere);
int					ft_cone_inter(t_ray *ray, t_cone *cone);
int					ft_cylinder_inter(t_ray *ray, t_cylinder *cylinder);
void				ft_camera(t_data *data, t_vec4 position, t_vec4 lookat);
t_ray				ft_get_ray_to_light(t_ray *ray, t_light *source);
unsigned int 		ft_color_rgb_scalar(unsigned int color, double r, double g, double b);
int					ft_color_add(unsigned int color1, unsigned int color2);
unsigned int		ft_sphere_shader(t_data *data, t_ray *ray, t_sphere *sphere);
unsigned int		ft_plane_shader(t_data *data, t_ray *ray, t_plane *plane);
unsigned int		ft_cylinder_shader(t_data *data, t_ray *ray, t_cylinder *cylinder);
unsigned int		ft_cone_shader(t_data *data, t_ray *ray, t_cone *cone);
void				ft_camera_ray(t_ray *ray, t_camera *cam, int x, int y);
int					ft_ray_inter_objs(t_list *list, t_ray *r_light, double distance_to_light);
unsigned int		ft_compute_shader(unsigned int color, t_shader_x *sh_x);
t_shader_x			ft_ray_inter_lights(t_data *data, t_vec4 nr,
                                         t_ray *ray, t_vec4 *ds);
double				ft_min(double val, double min);
double				ft_max(double val, double max);
// parser

typedef struct	s_function
{
	char		*type;
	void		(*call)();
}				t_function;

int					get_next_line(int fd, char **line);
double				ft_atof(char *nbr);

int					ft_expect_vector(char *line, char *name, t_vec4 *vector);
int					ft_expect_intensity(char *line, char *name, t_light *light);
int					ft_expect_diffuse(char *line, char *name, t_vec4 *vector);
int					ft_expect_value(char *line, char *name, double *n);
int					ft_expect_color(char *line, char *name, unsigned int *color);
int					ft_expect_matrix(char *line, char *str, t_vec4 *vec);

int					ft_is_numeric(char *str);
size_t				ft_table_size(char **tab);
int					ft_is_limited(double n);
int					ft_bracket_control(char *str, char c);
void				ft_cheak_data(t_data *data);

char				*ft_error_type(int error);
void				ft_error_management(t_data *data, int error, void **to_free,
									int fd);

void				ft_get_camera_config(int fd, t_data *data);
void				ft_get_sphere_config(int fd, t_data *data);
void				ft_get_light_config(int fd, t_data *data);
void				ft_get_plane_config(int fd, t_data *data);
void				ft_get_cone_config(int fd, t_data *data);
void				ft_get_cylinder_config(int fd, t_data *data);
void				ft_get_config(char *conf_file, t_data *data);
void				ft_del(void *content, size_t size);

#endif
