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
	unsigned int	i;

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
				if ( xy[0] == 0 && xy[1] == 0 && s->content_size == SPHERE)
				{
					int bpp, size_l, endian;
					t_sphere *sp = (t_sphere *)s->content;
					sp->texture.img = mlx_xpm_file_to_image(data->mlx, "textures/earth.xpm", &sp->texture.width, &sp->texture.height);
					sp->texture.buff = (int *)mlx_get_data_addr(sp->texture.img, &bpp, &size_l, &endian);
					if(sp->texture.buff == NULL)
					{
						printf("Error in loading the image\n");
						exit(1);
					}
					// for (int k = 0; k < size_l; k++)
					// 	printf("%X\n", sp->texture.buff[k]);
					//  exit(1);
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