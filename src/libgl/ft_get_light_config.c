/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_light_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:01:45 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/16 17:14:42 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static short	ft_light_type(int i)
{
	if (i == 3)
		return (POINT_LIGHT);
	if (i == 15)
		return (AREA_LIGHT);
	if (i == 51)
		return (SPOT_LIGHT);
	if (i == 35)
		return (DIRECTIONAL_LIGHT);
	if (i == 63)
		return (AREA_SPOT_LIGHT);
	return (-1);
}

static int		ft_stock_light_config(int fd, t_light *l, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_expect_vector(s, "\tposition", &(l->origin)))
			i = i | 1;
		else if (ft_expect_intensity(s, "\tintensity", l))
			i = i | 2;
		else if (ft_expect_area_uv(s, "\tarea_u", &(l->u_dir), &(l->u_nodes)))
			i = i | 4;
		else if (ft_expect_area_uv(s, "\tarea_v", &(l->v_dir), &(l->v_nodes)))
			i = i | 8;
		else if (ft_expect_spot_dot(s, "\tspot_dot", &(l->spot_dot)))
			i = i | 16;
		else if (ft_expect_vector(s, "\tdirection", &(l->dir)))
			i = i | 32;
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			i = 0;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((l->type = ft_light_type(i)) >= 0 && j ? 1 : 0);
}

static t_vec4	ft_node_pos(t_light *light, int *i_j)
{
	return (ft_vec4_add(light->origin,
		ft_vec4_add(ft_vec4_scalar(light->u_dir,
			(i_j[1] + (float)(rand() % 10) / light->u_nodes)
							* 0.1 - (light->u_nodes * 0.1 / 2)),
		ft_vec4_scalar(light->v_dir,
			(i_j[0] + (float)(rand() % 10) / light->v_nodes)
							* 0.1 - (light->v_nodes * 0.1 / 2)))));
}

static void		ft_create_area_lightlst(t_data *data, int fd, t_light *l)
{
	t_light *new_l;
	int		i_j[2];

	if (l->type == AREA_LIGHT || l->type == AREA_SPOT_LIGHT)
	{
		i_j[0]= -1;
		l->lst = NULL;
		while (++i_j[0] < l->v_nodes)
		{
			i_j[1]= -1;
			while (++i_j[1] < l->u_nodes)
			{
				if (!(new_l = (t_light *)malloc(sizeof(t_light))))
					ft_error_management(data, 10, NULL, fd);
				if (l->type == AREA_SPOT_LIGHT)
				{
					new_l->spot_dot = l->spot_dot;
					new_l->dir = l->dir;
				}
				new_l->origin = ft_node_pos(l, i_j);
				new_l->type = (l->type == AREA_LIGHT) ? POINT_LIGHT : SPOT_LIGHT;
				ft_lstadd(&l->lst, ft_lstnew((void *)new_l, 0));
			}
		}
	}
}

void			ft_get_light_config(int fd, t_data *data)
{
	char	*line;
	t_light	*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_light_config(fd, light, 0, 0)))
			{
				ft_memdel((void **)&light);
				ft_error_management(data, 6, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 6, (void **)&line, fd);
	}
	ft_create_area_lightlst(data, fd, light);
	ft_lstadd(&(data->light_list), ft_lstnew((void *)light, 0));
}
