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

void		ft_camera(t_data *data, t_vector4 position , t_vector4 lookat, double focal_length)
{
	data->cam.mx = ft_create_matrix4();
	data->cam.l = 1;
	data->cam.bigl = 1;
	data->cam.focal_length = focal_length;
	data->cam.position = position;
	data->cam.to = lookat;

	t_vector4 forward = ft_vec4_sub(&data->cam.to, &data->cam.position); // lookAtPoint - eyePoint;
	forward = ft_vec4_normalize(&forward);


	t_vector4 up = ft_create_vector4(0,1,0,0);
	t_vector4 camera_left = ft_vec4_cross_product(&up, &forward);
	t_vector4 camera_up = ft_vec4_cross_product(&forward, &camera_left);


	camera_left = ft_vec4_normalize(&camera_left);
	camera_up = ft_vec4_normalize(&camera_up);

	data->cam.up = camera_up;
	data->cam.left = camera_left;
	data->cam.forward = forward;

	data->cam.mx.v[0][2] = forward.v[X]; // Forward dir
	data->cam.mx.v[1][2] = forward.v[Y];
	data->cam.mx.v[2][2] = forward.v[Z];
	data->cam.mx.v[3][2] = forward.v[W];

	data->cam.mx.v[0][1] = camera_up.v[X]; // Up dir
	data->cam.mx.v[1][1] = camera_up.v[Y];
	data->cam.mx.v[2][1] = camera_up.v[Z];
	data->cam.mx.v[3][1] = camera_up.v[W];

	data->cam.mx.v[0][0] = camera_left.v[X]; // Right dir
	data->cam.mx.v[1][0] = camera_left.v[Y];
	data->cam.mx.v[2][0] = camera_left.v[Z];
	data->cam.mx.v[3][0] = camera_left.v[W];
	ft_printmatrix4(&data->cam.mx);
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

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			xm = ft_map(x, data->cam.bigl, WIDTH) /*+ data->cam.position.v[X]*/;
			ym = ft_map(y, data->cam.l, HEIGHT) /*+ data->cam.position.v[Y]*/;
	
			t_vector4 new_left = ft_vec4_scalar(&data->cam.left, xm);
			t_vector4 new_up = ft_vec4_scalar(&data->cam.up, ym);
			t_vector4 new_forw = ft_vec4_scalar(&data->cam.forward, data->cam.focal_length);
			t_vector4 left_up =  ft_vec4_add(&new_up , &new_left);
			t_vector4 res = ft_vec4_add(&left_up, &new_forw);
			
			// t_ray ray = ft_get_ray(data, &res);
			t_ray ray;
			ray.dir = ft_vec4_normalize(&res);
			
			ray.origin = ft_create_vector4(data->cam.position.v[X], data->cam.position.v[Y], data->cam.position.v[Z], 0);
			ray.t = FAR;

			t_light_source lamp;
			lamp.type = POINT_LIGHT;
			lamp.size = 0;
			lamp.origin = ft_create_vector4(0, -9, 0, 1);


			t_plane	plane1;
			plane1.normal = ft_create_vector4(0, 1, 0, 0);
			plane1.point = ft_create_vector4(0, 1 ,0, 0);
			plane1.color = 0x8DEEEE ;
			if (ft_plane_intersection(&ray, &plane1))
				ft_image_fill(data, x, y, plane1.color);
			
			t_sphere sphere1;
			sphere1.center = ft_create_vector4(0, 0, 0, 1);
			sphere1.radius = 0.8;
			sphere1.color = 0xAA0000;

			t_sphere sphere2;
			sphere2.center = ft_create_vector4(0.2, -2, 0, 1);
			sphere2.radius = 0.5;
			sphere2.color = 0x0000AA;

			t_sphere sphere3;
			sphere3.center = ft_create_vector4(-2, 0, -5, 1);
			sphere3.radius = 0.5;
			sphere3.color = 0xA57982;
			t_sphere sphere4;
			sphere4.center = ft_create_vector4(2, 0, 0, 1);
			sphere4.radius = 1;
			sphere4.color = 0x449900;
			t_sphere sphere5;
			sphere5.center = ft_create_vector4(0.5, 0, 5, 1);
			sphere5.radius = 0.3;
			sphere5.color = 0xF7A072;
			t_sphere sphere6;
			sphere6.center = ft_create_vector4(-3, -1, 0, 1);
			sphere6.radius = 0.6;
			sphere6.color = 0x0FA3B1;

			t_ray ray_to_light;


			if (ft_sphere_intersection(&ray, &sphere1, 0))
			{
				ft_image_fill(data, x, y, sphere1.color);
				ray_to_light = ft_light_intersection(&ray, &lamp);
				ray_to_light.t = FAR;
				if (ft_sphere_intersection(&ray_to_light, &sphere1, 1))
					ft_image_fill(data, x, y, 0x0);
				if (ft_sphere_intersection(&ray_to_light, &sphere2, 0))
					ft_image_fill(data, x, y, 0x0);
			}

			if (ft_sphere_intersection(&ray, &sphere2, 0))
			{
				ft_image_fill(data, x, y, sphere2.color);
				ray_to_light = ft_light_intersection(&ray, &lamp);
				ray_to_light.t = FAR;
				if (ft_sphere_intersection(&ray_to_light, &sphere2, 1))
					ft_image_fill(data, x, y, 0x0);
			}

			if (ft_sphere_intersection(&ray, &sphere3, 0))
			{
				ft_image_fill(data, x, y, sphere3.color);
				ray_to_light = ft_light_intersection(&ray, &lamp);
				ray_to_light.t = FAR;
				if (ft_sphere_intersection(&ray_to_light, &sphere3, 1))
					ft_image_fill(data, x, y, 0x0);
				if (ft_sphere_intersection(&ray_to_light, &sphere2, 0))
					ft_image_fill(data, x, y, 0x0);
			}

			if (ft_sphere_intersection(&ray, &sphere4, 0))
			{
				ft_image_fill(data, x, y, sphere4.color);
				ray_to_light = ft_light_intersection(&ray, &lamp);
				ray_to_light.t = FAR;
				if (ft_sphere_intersection(&ray_to_light, &sphere4, 1))
					ft_image_fill(data, x, y, 0x0);
				if (ft_sphere_intersection(&ray_to_light, &sphere2, 0))
					ft_image_fill(data, x, y, 0x0);
			}

			if (ft_sphere_intersection(&ray, &sphere5, 0))
			{
				ft_image_fill(data, x, y, sphere5.color);
				ray_to_light = ft_light_intersection(&ray, &lamp);
				ray_to_light.t = FAR;
				if (ft_sphere_intersection(&ray_to_light, &sphere5, 1))
					ft_image_fill(data, x, y, 0x0);
				if (ft_sphere_intersection(&ray_to_light, &sphere2, 0))
					ft_image_fill(data, x, y, 0x0);
			}
			//  if (ft_sphere_intersection(&ray, &sphere2, 0))
			// 	ft_image_fill(data, x, y, sphere2.color);
				
 
			// if (ft_sphere_intersection(&ray, &sphere3, 0))
			// 	ft_image_fill(data, x, y, sphere3.color);

			// if (ft_sphere_intersection(&ray, &sphere4, 0))
			// 	ft_image_fill(data, x, y, sphere4.color);
			
			// if (ft_sphere_intersection(&ray, &sphere5, 0))
			// 	ft_image_fill(data, x, y, sphere5.color);

			// if (ft_sphere_intersection(&ray, &sphere6, 0))
			// 	ft_image_fill(data, x, y, sphere6.color);
			x++;
		}
		y++;
	}
}



t_list		*ft_get_scene()
{
	unsigned int	obj_num;
	unsigned int	i;
	t_list			*node;
	void			*content;
	t_list			*head;
	t_list			*tmp;
	i = -1;
	obj_num = 6;

	t_sphere array[6];

	array[0].center = ft_create_vector4(0, 0, 0, 1);
	array[0].radius = 0.8;
	array[0].color = 0xAA0000;

	array[0].type = SPHERE;
	array[1].type = SPHERE;
	array[2].type = SPHERE;
	array[3].type = SPHERE;
	array[4].type = SPHERE;
	array[5].type = SPHERE;
	
	array[1].center = ft_create_vector4(0.2, -2, 0, 1);
	array[1].radius = 0.5;
	array[1].color = 0x0000AA;

	array[2].center = ft_create_vector4(-2, 0, -5, 1);
	array[2].radius = 0.5;
	array[2].color = 0xA57982;

	array[3].center = ft_create_vector4(2, 0, 0, 1);
	array[3].radius = 1;
	array[3].color = 0x449900;

	array[4].center = ft_create_vector4(0.5, 0, 5, 1);
	array[4].radius = 0.3;
	array[4].color = 0xF7A072;

	array[5].center = ft_create_vector4(-3, -1, 0, 1);
	array[5].radius = 0.6;
	array[5].color = 0x0FA3B1;

	while (++i < obj_num)// iterate for each object.
	{
		if (array[i].type == SPHERE)// type == sphere
		{
			content = (t_sphere *)malloc(sizeof(t_sphere));
			// printf("node type == %d\n", ((t_sphere *)content)->type);
			if (i == 0)
			{
				node = ft_lstnew(content, 5); // assign struct in content and type in SPHERE
				tmp = node;
			}
			else
				node = ft_lstnew(content, SPHERE); // assign struct in content and type in SPHERE
			// printf("node type == %zu\n", (node)->content_size);
		}
		else if (array[i].type == PLANE) // type == plane
		{
			content = malloc(sizeof(t_plane));
			node = ft_lstnew(content, PLANE);
		}
		ft_lstadd(&head, node);
	}
	tmp->next = NULL;
	return (head);
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
	// while (++i < data.winwidth)
	// 	ft_image_fill(&data, i , data.winwidth / 2, 0xdd0011);
	// while (++j < data.winheight)
	// 	ft_image_fill(&data, data.winheight / 2, j, 0xdd0011);

	t_vector4 cam_pos = ft_create_vector4(0, -2, 15, 1);
	t_vector4 look_at_pos = ft_create_vector4(0, 0, -1, 1);
	data.cam.mousepos.x = -900000;
	data.cam.mousepos.y = -900000;

	int k = 0;
	t_list *scene = ft_get_scene();
	t_sphere *tmp;
	while (scene != NULL)
	{
		tmp = (t_sphere *)scene->content;
		printf("type == %zu : radius == %f\n", scene->content_size, tmp->radius);
		if (k == 5)
			printf("%d\n",(int)scene->next);
		scene = scene->next;
		k++;
	}
	
	
	exit(1);
	ft_camera(&data, cam_pos, look_at_pos, 2);
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








*/