/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cylinder_config.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 15:20:18 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/16 17:13:49 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void ft_cylinder_val_correction(t_cylinder **cylinder, t_data *data, int fd)
{
	t_vec4 up;
	double dot_prod;

	up = ft_create_vec4(0, 1, 0, 0);
	(*cylinder)->axis = ft_vec4_normalize((*cylinder)->axis);					// correcting normal
	dot_prod = ft_vec4_dot_product((*cylinder)->axis, up);
	if (dot_prod <= 1 + NEAR && dot_prod >= 1 - NEAR)
		up = ft_create_vec4(1, 0, 0, 0);
	(*cylinder)->left = ft_vec4_normalize(
							ft_vec4_cross_product((*cylinder)->axis, up));	// calculate left && forward vectors
	(*cylinder)->forw = ft_vec4_normalize(
					ft_vec4_cross_product((*cylinder)->left, (*cylinder)->axis));
	
	if ((*cylinder)->texture.id > -1) {
		if (!ft_load_texture((*cylinder)->texture.id, &(*cylinder)->texture, data)) // loading texture if exists
			ft_error_management(data, 11, (void **)cylinder, fd);
		if ((*cylinder)->texture.stretch_x == 0)
			(*cylinder)->texture.stretch_x = 1;
		if ((*cylinder)->texture.stretch_y == 0)
			(*cylinder)->texture.stretch_y = 1;
		if ((*cylinder)->texture.stretch_z == 0)
			(*cylinder)->texture.stretch_z = 1;
	}
}

static int	ft_stock_cylinder_config_next(char *line, t_cylinder *p, int *i)
{
	int j;
	int tmp;

	j = 0;
	tmp = 0;
	if (!(*i & 32) && ft_expect_value(line, "\tradius", &(p->radius)))
	{
		tmp = 1;
		*i += 32;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->axis)))
	{
		p->axis = ft_vec4_normalize(p->axis);
		j++;
	}
	if (ft_expect_matrix(line, "\ttransfo ", &(p->point)))
		j++;
	if (j == 2)
		*i += 64;
	return (j == 2 || tmp ? 1 : 0);
}

static int ft_cylinder_values(int *i, t_cylinder *p, char *s)
{
	if (!(*i & 1) && ft_expect_vector(s, "\tcenter", &(p->point)))
		*i += 1;
	else if (!(*i & 2) && ft_expect_color(s, "\tcolor", &(p->color)))
		*i += 2;
	else if (!(*i & 4) && ft_expect_diffuse(s, "\tdiffuse", &(p->diffuse)))
		*i += 4;
	else if (!(*i & 8) && ft_expect_value(s, "\tspecular", &(p->specular)))
		*i += 8;
	else if (!(*i & 16) && ft_expect_vector(s, "\tnormal", &(p->axis)))
		*i += 16;
	else if (!(*i & 96)  && ft_stock_cylinder_config_next(s, p, i))
		*i += 0;
	else if (!(*i & 128) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 128;
	else if (!(*i & 256) && ft_expect_texture(s, "\ttexture", &p->texture))
		*i += 256;
	else
		return (0);
	return (1);
}

static int	ft_stock_cylinder_config(int fd, t_cylinder *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_cylinder_values(&i, p, s)){
			if ((i | 128) > i) // set default values here by ||
				p->ref.w = 0;  // reflection refraction => false
			if ((i | 256) > i)
			{
				p->texture.img = NULL;
				p->texture.id = -1;
			}
		}
		// printf("cyltext id : %d | img addr %p --%s\n", p->texture.id, p->texture.img, s);
		else if ((j = ft_bracket_control(s, '}')))
		{
			break ;
		}
		else
			i = 0;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 63 || i == 127 || i == 255 || i == 191 || i == 319
					|| i == 383 || i == 447 || i == 511) && j ? 1 : 0);
}

void		ft_get_cylinder_config(int fd, t_data *data)
{
	char		*line;
	t_cylinder	*cylinder;

	if (!(cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_cylinder_config(fd, cylinder, 0, 0)))
			{
				ft_memdel((void **)&cylinder);
				ft_error_management(data, 5, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 5, (void **)&line, fd);
	}
	ft_cylinder_val_correction(&cylinder, data, fd);
	ft_lstadd(&(data->scene), ft_lstnew((void *)cylinder, CYLINDER));
}
