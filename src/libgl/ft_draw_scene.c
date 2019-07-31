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

const t_obj_function g_t_obj_ft2[4] =
{
	{SPHERE, &ft_sphere_inter, &ft_sphere_shader},
	{PLANE, &ft_plane_inter, &ft_plane_shader},
	{CONE, &ft_cone_inter, &ft_cone_shader},
	{CYLINDER, &ft_cylinder_inter, &ft_cylinder_shader}
};

void		ft_draw_scene(t_data *data)
{
	int	xy[2];
	t_list			*s;
	t_ray			ray;
	unsigned int	i;int j = 2;

	xy[1] = -1;
	while (++xy[1] < data->winheight)
	{
		xy[0] = -1;
		while (++xy[0] < data->winwidth)
		{
			ft_get_camera_ray(&ray, &data->cam, xy[0], xy[1]);
			s = data->scene;
			while (s != NULL)
			{
				if (s->content_size == PLANE)
					((t_plane *)s->content)->refl.w = 2;
				if (s->content_size == SPHERE && j > 0)
				{
					((t_sphere *)s->content)->refl.x = 1;
					((t_sphere *)s->content)->refl.y = 1;
					((t_sphere *)s->content)->refl.z = 1;
					((t_sphere *)s->content)->refl.w = 1;
					j--;
					// printf("here %f\n", ((t_cylinder *)s->content)->refl.w);
				}
				else if (s->content_size == SPHERE && j == 0)
				{
					((t_sphere *)s->content)->refl.w = 0;
					j--;
				}
				i = -1;
				while (++i < (unsigned int)STATIC_ARRAY_SIZE(g_t_obj_ft2))
					if (g_t_obj_ft2[i].type == s->content_size
							&& g_t_obj_ft2[i].call(&ray, s->content))
						ft_image_fill(data, xy[0], xy[1],
								g_t_obj_ft2[i].call2(data, &ray, s->content));
				s = s->next;
			}
		}
	}
}