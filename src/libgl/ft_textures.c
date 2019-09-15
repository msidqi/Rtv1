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
	// printf("%d, %d\n", (int)(floor(u * sp->texture.width)), (int)(floor(v * sp->texture.height) * sp->texture.width));
	// printf("%x\n", sp->texture.buff[(int)(floor(u * sp->texture.width)) + (int)(floor(v * sp->texture.height) * sp->texture.width)]);

	int red = ft_color_rgb_scalar(0xFF0000, v, 0, 0), green = ft_color_rgb_scalar(0x00FF00, 0, u, 0);
	size_t img_size = sp->texture.width * sp->texture.height * 3;
	int k = (int)(floor(u * sp->texture.width)) + (int)(floor(v * sp->texture.height) * sp->texture.width);
	// if (u > 0.8 && u < 0.9 && v > 0.8 && v < 0.9)
		return (sp->texture.buff[k] + sp->texture.buff[k + 1] * 256 + sp->texture.buff[k + 2] * 256 * 256);
	// sp->texture.buff[(int)(floor(u * sp->texture.width)) + (int)(floor(v * sp->texture.height) * sp->texture.width)]
	return (red);//ft_color_add(red, green));
}