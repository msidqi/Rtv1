/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:57:55 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 16:03:27 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static const t_obj_function g_t_obj_ft2[4] =
{
	{SPHERE, &ft_sphere_inter, &ft_sphere_shader},
	{PLANE, &ft_plane_inter, &ft_plane_shader},
	{CONE, &ft_cone_inter, &ft_cone_shader},
	{CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader}
};

void		ft_draw(t_data *data)
{
	int		xy[2];
	t_list	*s;
	t_ray	ray;
	int		i;

	xy[1] = -1;
	while (++xy[1] < HEIGHT)
	{
		xy[0] = -1;
		while (++xy[0] < WIDTH)
		{
			ft_camera_ray(&ray, &data->cam, xy[0], xy[1]);
			s = data->scene;
			while (s != NULL)
			{
				i = -1;
				while (++i < 4)
					if (g_t_obj_ft2[i].type == s->content_size
							&& g_t_obj_ft2[i].call(&ray, s->content))
						ft_image_fill(data, xy[0], xy[1],
								g_t_obj_ft2[i].call2(data, &ray, s->content));
				s = s->next;
			}
		}
	}
}
