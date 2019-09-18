/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:20:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:21:43 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"
#ifndef PI
# define PI 3.14159265358979323846
#endif

int		ft_texture_sphere(int id, t_ray *ray, t_sphere *sp)
{
	double phi = 0, theta = 0, u, v;(void)id;

	t_vec4 X = ft_vec4_sub(sp->center, ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin));
	//t_vec4 P = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);

	phi = atan2(X.z, X.x);				// angle between x axis and X around sphere's latitude
	theta = acos(-(X.y) / sp->radius);	// angle between y axis and X along the longtitude (s pole to n pole)
	u = ((phi + PI) / (2 * PI));	//
	v = theta / PI;

	//  printf("x : %f, Y : %f, z : %f\nθ : %f, u : %f\nφ : %f, v : %f\n---------------\n", X.x, X.y, X.z,
	//  phi, u, theta, v);
	// printf("%d, %d\n", sp->texture.width, sp->texture.height);
	// printf("%x\n", sp->texture.buff[(int)(floor(u * sp->texture.width)) + (int)(floor(v * sp->texture.height) * sp->texture.width)]);

	int red = ft_color_rgb_scalar(0xFF0000, v, 0, 0), green = ft_color_rgb_scalar(0x00FF00, 0, u, 0);
	size_t img_size = sp->texture.width * sp->texture.height * 3;
	// int k = (int)(floor(u * sp->texture.width)) + (int)(floor(v * sp->texture.height * sp->texture.width));
	int k = sp->texture.width + sp->texture.height;
	for(int i = 0; i < img_size; i +=3)
		printf("%d %d %d, %X\n", sp->texture.buff[i], sp->texture.buff[i + 1], sp->texture.buff[i + 2],
		sp->texture.buff[i]+ sp->texture.buff[i + 1]  * 256 + sp->texture.buff[i + 2] * 256 * 256);
	// printf("u : %f | v : %f | v : %f | k : %d\n", floor(u * sp->texture.width), floor(v * sp->texture.height), floor(v * sp->texture.height * sp->texture.width), k);
	// if (u > 0.8 && u < 0.9 && v > 0.8 && v < 0.9)
		return (sp->texture.buff[k] + sp->texture.buff[k + 1] * 256 + sp->texture.buff[k + 2] * 256 * 256);
	// sp->texture.buff[(int)(floor(u * sp->texture.width)) + (int)(floor(v * sp->texture.height) * sp->texture.width)]
	return (red);//ft_color_add(red, green));
}

int		ft_texture_plane(int id, t_ray *ray, t_plane *pl)
{
	(void)id;

	t_vec4 inter_point = ft_vec4_add(ft_vec4_scalar(ray->dir, ray->t), ray->origin);

	size_t img_size = pl->texture.width * pl->texture.height * 3;

	if (inter_point.x > pl->texture.width || inter_point.z > pl->texture.height || inter_point.x < 0 || inter_point.z < 0)
		return (0x00);
	int k = (int)(inter_point.x + inter_point.z * pl->texture.width);
	// printf("here %d | max %zu\n", k, img_size);
	return (pl->texture.buff[k] + pl->texture.buff[k + 1] * 256 + pl->texture.buff[k + 2] * 256 * 256);
}