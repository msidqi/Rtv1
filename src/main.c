/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 12:48:35 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/14 12:48:36 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"
#define HEIGHT 800
#define WIDTH 800

double		ft_map(int x_or_y, double size, int width_or_height)
{
	return (x_or_y * size / width_or_height - (size / 2));
}


t_ray		ft_get_ray(t_data *data, t_vector4 *view_window_pos)
{
	// ft_printmatrix4(&data->cam.mx);

	// t_matrix4 translation = ft_get_translation_matrix4(0, 0, 0);
	// t_vector4 view_window_pos = ft_create_vector4(xm, ym, data->cam.focal_length, 1);
	t_vector4 k = ft_vec4_sub(&(*view_window_pos), &data->cam.position);

	t_ray ray;
	ray.dir = ft_vec4_normalize(&k);
	ray.origin = ft_create_vector4(data->cam.position.v[X], data->cam.position.v[Y], data->cam.position.v[Z], 0);
	return (ray);
}

void		ft_draw(t_data *data)
{
	int x;
	int y;
	double xm;
	double ym;
	// double	fow;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			xm = ft_map(x, data->cam.size, WIDTH) /*+ data->cam.position.v[X]*/;
			ym = ft_map(y, data->cam.size, HEIGHT) /*+ data->cam.position.v[Y]*/;
			t_vector4 view_window_pos = ft_create_vector4(xm, ym, 0/*data->cam.focal_length*/, 1);

			t_ray ray = ft_get_ray(data, &view_window_pos);
			if (ft_sphere_intersection(&ray))
				ft_image_fill(data, x, y, 0xFF0000);
			

			// ft_printvector4(&ray);
			// printf("mag == %.14f\n", ft_vec4_magnitude(&ray));
			// printf("x: %d , y: %d | xm: %f , ym: %f\n", x, y, xm, ym);
			x++;
		}
		y++;
	}
}
int		main(void)
{
	t_data  data;
	int i;
	int j;
	data.movex = 90;
	j = -1;
	i = -1;
	ft_window_setup(&data, "ReTweet", 800, 800);
	ft_image_setup(&data);
	data.zoom = 1;
	data.worldpos.v[X] = ft_get_world_pos(i, data.winwidth, data.zoom);
	data.worldpos.v[Y] = ft_get_world_pos(i, data.winheight, data.zoom);
	while (++i < data.winwidth)
		ft_image_fill(&data, i , data.winwidth / 2, 0xdd0011);
	while (++j < data.winheight)
		ft_image_fill(&data, data.winheight / 2, j, 0xdd0011);

	data.cam.mx = ft_create_matrix4();
	// ft_printmatrix4(&data.cam.mx);
	data.cam.size = 1;
	data.cam.focal_length = 2;
	data.cam.position = ft_create_vector4(0, 0, 0, 1);
	data.cam.to = ft_create_vector4(0, 3, -3, 1);
	t_vector4 forward = ft_vec4_sub(&data.cam.to, &data.cam.position); // lookAtPoint - eyePoint;
	t_vector4 forward_normalized = ft_vec4_normalize(&forward);

	

	t_vector4 up = ft_create_vector4(0,1,0,0);
	t_vector4 camera_left = ft_vec4_cross_product(&up, &forward_normalized);
	t_vector4 camera_up = ft_vec4_cross_product(&forward_normalized, &camera_left);


	camera_left = ft_vec4_normalize(&camera_left);
	camera_up = ft_vec4_normalize(&camera_up);
	ft_printvector4(&camera_up); // cameraUPPPP
	ft_printvector4(&camera_left); // LEFT
	ft_printvector4(&forward_normalized); // FORWARD

	data.cam.mx.v[0][2] = forward_normalized.v[X]; // Forward dir
	data.cam.mx.v[1][2] = forward_normalized.v[Y];
	data.cam.mx.v[2][2] = forward_normalized.v[Z];
	data.cam.mx.v[3][2] = forward_normalized.v[W];

	data.cam.mx.v[0][1] = camera_up.v[X]; // Up dir
	data.cam.mx.v[1][1] = camera_up.v[Y];
	data.cam.mx.v[2][1] = camera_up.v[Z];
	data.cam.mx.v[3][1] = camera_up.v[W];

	data.cam.mx.v[0][0] = camera_left.v[X]; // Right dir
	data.cam.mx.v[1][0] = camera_left.v[Y];
	data.cam.mx.v[2][0] = camera_left.v[Z];
	data.cam.mx.v[3][0] = camera_left.v[W];
	ft_printmatrix4(&data.cam.mx);
	ft_draw(&data);

	// t_matrix4 mat;
	// t_matrix4 trans;
	// mat = ft_create_matrix4();
	// ft_putmatrix4(&mat);
	// trans = ft_get_translation_matrix4(10, 10, 10);
	// ft_putmatrix4(&trans);

	// t_vector4 vec = ft_create_vector4(10 , 11, 12, 1);
	// ft_putvector4(&vec);
	// vec = ft_matrix_x_vector(&trans, &vec);
	// ft_putvector4(&vec);


	mlx_put_image_to_window(data.mlx, data.win, data.img_ptr, 0, 0);
	ft_mlx_hooks(&data, false);
	return (0);
}


/*
	macro up : 1;
	macro down  : 2;
	macro left : 4;
	macro right  : 8;
	(left | up | left | right)
*/


/*

Vec P(x,y,z,w) , Vec C(5,5,5,1)

|P - C|² = r²
P - C² = r²








*/