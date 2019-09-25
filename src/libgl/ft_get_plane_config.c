/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_plane_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 13:31:36 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/16 17:15:27 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void ft_plane_val_correction(t_plane **plane, t_data *data, int fd)
{
	t_vec4 up;
	double dot_prod;

	up = ft_create_vec4(0, 1, 0, 0);
	(*plane)->normal = ft_vec4_normalize((*plane)->normal);					// correcting normal
	dot_prod = ft_vec4_dot_product((*plane)->normal, up);
	if (dot_prod <= 1 + NEAR && dot_prod >= 1 - NEAR)
		up = ft_create_vec4(1, 0, 0, 0);
	(*plane)->left = ft_vec4_normalize(
							ft_vec4_cross_product((*plane)->normal, up));	// calculate left && forward vectors
	(*plane)->forw = ft_vec4_normalize(
					ft_vec4_cross_product((*plane)->left, (*plane)->normal));

	if ((*plane)->texture.id > 0)
	{
		if (!ft_load_texture((*plane)->texture.id, &(*plane)->texture, data)) // loading texture if exists
			ft_error_management(data, 11, (void **)plane, fd);
		if ((*plane)->texture.stretch_x == 0)
			(*plane)->texture.stretch_x = 1;
		if ((*plane)->texture.stretch_y == 0)
			(*plane)->texture.stretch_y = 1;
		if ((*plane)->texture.stretch_z == 0)
			(*plane)->texture.stretch_z = 1;
	}
		
}

static int	ft_stock_plane_config_transfo(char *line, t_plane *p)
{
	int j;

	j = 0;
	if (ft_expect_matrix(line, "\ttransfo ", &(p->normal)))
	{
		p->normal = ft_vec4_normalize(p->normal);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->point)))
		j++;
	return (j == 2 ? 1 : 0);
}

static int	ft_plane_values(int *i, t_plane *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tposition", &(p->point)))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
		*i += 8;
	else if (!(*i & 16) && ft_expect_vector(s, "\tnormal", &(p->normal)))
		*i += 16;
	else if (!(*i & 32) && ft_stock_plane_config_transfo(s, p))
		*i += 32;
	else if (!(*i & 64) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 64;
	else if (!(*i & 128) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 128;
	else
		return (0);
	return (1);
}

static int	ft_stock_plane_config(int fd, t_plane *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_plane_values(&i, p, s)){
			if ((i | 64) > i) // set default values here by ||
				p->ref.w = 0; // reflection refraction => false
			if ((i | 128) > i)
			{
				p->texture.img = NULL;
				p->texture.id = -1;
			}
		}
		else if ((j = ft_bracket_control(s, '}')))
			break ;
		else
			i = 0;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 31 || i == 63 || i == 95 || i == 127 || i == 159 ||
							i == 191 || i == 223 || i == 255) && j ? 1 : 0);
}

void		ft_get_plane_config(int fd, t_data *data)
{
	char	*line;
	t_plane	*plane;

	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_plane_config(fd, plane, 0, 0)))
			{
				ft_memdel((void **)&plane);
				ft_error_management(data, 3, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 3, (void **)&line, fd);
	}
	ft_plane_val_correction(&plane, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)plane, PLANE));
}
