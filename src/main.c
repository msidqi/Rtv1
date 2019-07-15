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

double		ft_map(int x_or_y, double size, int width_or_height)
{
	return (x_or_y * size / width_or_height - (size / 2));
}

void		ft_camera(t_data *data, t_vector4 position , t_vector4 lookat, double focal_length)
{
	data->cam.mx = ft_create_matrix4();
	data->cam.l = 1;
	data->cam.bigl = 1;
	data->cam.focal_length = focal_length;
	data->cam.position = position;
	data->cam.to = lookat;

	t_vector4 forward = ft_vec4_sub(data->cam.to, data->cam.position); // lookAtPoint - eyePoint;
	forward = ft_vec4_normalize(forward);


	t_vector4 up = ft_create_vector4(0,1,0,0);
	t_vector4 camera_left = ft_vec4_cross_product(up, forward);
	t_vector4 camera_up = ft_vec4_cross_product(forward, camera_left);


	camera_left = ft_vec4_normalize(camera_left);
	camera_up = ft_vec4_normalize(camera_up);

	data->cam.up = camera_up;
	data->cam.left = camera_left;
	data->cam.forward = forward;

	data->cam.mx.v[0][2] = forward.x; // Forward dir
	data->cam.mx.v[1][2] = forward.y;
	data->cam.mx.v[2][2] = forward.z;
	data->cam.mx.v[3][2] = forward.w;

	data->cam.mx.v[0][1] = camera_up.x; // Up dir
	data->cam.mx.v[1][1] = camera_up.y;
	data->cam.mx.v[2][1] = camera_up.z;
	data->cam.mx.v[3][1] = camera_up.w;

	data->cam.mx.v[0][0] = camera_left.x; // Right dir
	data->cam.mx.v[1][0] = camera_left.y;
	data->cam.mx.v[2][0] = camera_left.z;
	data->cam.mx.v[3][0] = camera_left.w;
	// ft_printmatrix4(&data->cam.mx);
}

t_ray		ft_get_ray(t_data *data, t_vector4 *view_window_pos)
{
	t_ray ray;

	ray.dir = ft_vec4_normalize(ft_vec4_sub((*view_window_pos), data->cam.position));
	ray.origin = ft_create_vector4(data->cam.position.x, data->cam.position.y, data->cam.position.z, 0);
	return (ray);
}

void		ft_draw(t_data *data)
{
	int x;
	int y;
	double xm;
	double ym;
	t_list *scene;
	t_ray ray;
	t_shader pixel_shader;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			xm = ft_map(x, data->cam.bigl, WIDTH * ASPECT_RATIO);
			ym = ft_map(y, data->cam.l, HEIGHT );
			// printf("xm : %f ym : %f\n", xm, ym);
			// exit(1);
			t_vector4 new_left = ft_vec4_scalar(data->cam.left, xm);
			t_vector4 new_up = ft_vec4_scalar(data->cam.up, ym);
			t_vector4 new_forw = ft_vec4_scalar(data->cam.forward, data->cam.focal_length);
			t_vector4 left_up =  ft_vec4_add(new_up , new_left);

			ray.dir = ft_vec4_normalize(ft_vec4_add(left_up, new_forw));
			ray.origin = ft_create_vector4(data->cam.position.x, data->cam.position.y, data->cam.position.z, 0);
			ray.t = FAR;


			scene = data->scene;
			while (scene != NULL) // foreach obj
			{
				if (scene->content_size == SPHERE && ft_sphere_intersection(&ray, (t_sphere *)scene->content)) // for spheres
				{// 0- intersect ray from camera with a sphere
					pixel_shader = ft_compute_sphere_shader(data, &ray, (t_sphere *)scene->content);
					ft_image_fill(data, x, y, ft_color_add(pixel_shader.specular,ft_color_add(pixel_shader.diffuse, pixel_shader.ambient)) );
				}
				else if (scene->content_size == CONE && ft_cone_intersection(&ray, (t_cone *)scene->content))
				{
					pixel_shader = ft_compute_cone_shader(data, &ray, (t_cone *)scene->content);
					ft_image_fill(data, x, y, ft_color_add(pixel_shader.specular,ft_color_add(pixel_shader.diffuse, pixel_shader.ambient)));//ft_color_add(pixel_shader.specular,ft_color_add(pixel_shader.diffuse, pixel_shader.ambient)) );
				}
				else if (scene->content_size == CYLINDER && ft_cylinder_intersection(&ray, (t_cylinder *)scene->content))
				{
					pixel_shader = ft_compute_cylinder_shader(data, &ray, (t_cylinder *)scene->content);
					ft_image_fill(data, x, y, ft_color_add(pixel_shader.specular,ft_color_add(pixel_shader.diffuse, pixel_shader.ambient))); // ft_color_add(pixel_shader.specular,ft_color_add(pixel_shader.diffuse, pixel_shader.ambient)) );
				}
				else if (scene->content_size == PLANE && ft_plane_intersection(&ray, (t_plane *)scene->content))
				{
					pixel_shader = ft_compute_plane_shader(data, &ray, (t_plane *)scene->content);
					ft_image_fill(data, x, y, ft_color_add(pixel_shader.specular,ft_color_add(pixel_shader.diffuse, pixel_shader.ambient)));
				}
				scene = scene->next;
			}
			x++;
		}
		y++;
	}
}

void	ft_link_two_lists(t_list *head_1, t_list *head_2)
{
	if (head_1 == NULL || head_2 == NULL)
		return ;
	while (head_1 != NULL)
	{
		head_1 = head_1->next;
	}
	head_1->next = head_2;
}



int		main(int argc, char **argv)
{
	t_data  data;

	if (argc != 2)
		return (1);
	ft_window_setup(&data, "ReTweet", HEIGHT, WIDTH);
	ft_image_setup(&data);
	data.aspectratio = WIDTH / HEIGHT;
	data.scene = ft_get_config(argv[1], &data);
	ft_camera(&data, data.cam.position, data.cam.to, 2);
	ft_draw(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img_ptr, 0, 0);
	ft_mlx_hooks(&data, true);
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











magnitude A =  ||A|| = P-C
magnitude B =  ||B|| = V = 1



B is normalazed 

angle  entre (vec4 A et vec4 B)  ==    dotprod(A , B)




cos (A , B) =   dot(A, B )  / (  ||A||  * ||1||  )




*/