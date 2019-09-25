/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:57:55 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 16:03:27 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"//texture mapping + soft shadows + refraction

const t_obj_function g_t_obj_ft2[5] =
{
	{ SPHERE, &ft_sphere_inter, &ft_sphere_shader },
	{ PLANE, &ft_plane_inter, &ft_plane_shader },
	{ CONE, &ft_cone_inter, &ft_cone_shader },
	{ CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader },
	{ BOX, &ft_box_inter, &ft_box_shader }
};

void		ft_draw_scene(t_data *data)
{
	int				xy[2];
	t_list			*s;
	t_ray			ray;
	unsigned int	ij[2];
	int				colors[4];

	xy[1] = -1;
	while (++xy[1] < data->winheight)
	{
		xy[0] = -1;
		while (++xy[0] < data->winwidth)
		{
			ij[1] = -1;
			while (++ij[1] < 4)		// rays_number
			{
				ft_get_camera_ray(&ray, &data->cam, xy, ij[1]);
				s = data->scene;
				colors[ij[1]] = 0;
				while (s != NULL)
				{
					ij[0] = -1;
					while (++ij[0] < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_ft2))
						if (g_t_obj_ft2[ij[0]].type == s->content_size
								&& g_t_obj_ft2[ij[0]].call(&ray, s->content))
							colors[ij[1]] = ft_filters_aa(data, xy[0], xy[1],
									g_t_obj_ft2[ij[0]].call2(data, &ray, s->content));
					s = s->next;
				}
			}
			ft_image_fill(data, xy[0], xy[1], ft_color_avg(colors));
			// ft_image_fill(data, xy[0], xy[1], ft_color_avg2(colors[0], colors[1], colors[2], colors[3], colors[4], colors[5], colors[6], colors[7], colors[8], colors[9], colors[10], colors[11], colors[12], colors[13], colors[14], colors[15]));
		}
	}
}
