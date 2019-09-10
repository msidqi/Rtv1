/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_sphere_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:05:40 by kdaou             #+#    #+#             */
/*   Updated: 2019/07/16 17:16:04 by kdaou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static int ft_sphere_values(int *i, t_sphere *p, char *s)
{
	if (!(*i & 1) && ft_expect_value(s, "\tradius", &p->radius))
		*i += 1;
	else if (!(*i & 2) && ft_expect_vector(s, "\tcenter", &p->center))
		*i += 2;
	else if (!(*i & 4) && ft_expect_color(s, "\tcolor", &p->color))
		*i += 4;
	else if (!(*i & 8) && ft_expect_diffuse(s, "\tdiffuse", &p->diffuse))
		*i += 8;
	else if (!(*i & 16) && ft_expect_value(s, "\tspecular", &p->specular))
		*i += 16;
	else if (!(*i & 32) && ft_expect_ref(s, "\tref", &p->ref))
		*i += 32;
	else if (!(*i & 64) && ft_expect_matrix(s, "\ttransfo ", &p->center))
		*i += 64;
	else
		return (0);
	return (1);
}

static int	ft_stock_sphere_config(int fd, t_sphere *p, int i, int j)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) > 0)
	{
		if (ft_sphere_values(&i, p, s)){
			if ((i | 32) > i) // set default values here by ||
				p->ref.w = 0; // reflection refraction => false
		}
		else if ((j = ft_bracket_control(s, '}'))){	
			break ;}
		else
			i = 0;
		ft_strdel(&s);
	}
	ft_strdel(&s);
	return ((i == 31 || i == 63 || i == 95 || i == 127) && j ? 1 : 0);
}

void		ft_get_sphere_config(int fd, t_data *data)
{
	char		*line;
	t_sphere	*sphere;

	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_bracket_control(line, '{'))
		{
			if (!(ft_stock_sphere_config(fd, sphere, 0, 0)))
			{
				ft_memdel((void **)&sphere);
				ft_error_management(data, 2, (void **)&line, fd);
			}
			else
			{
				ft_strdel(&line);
				break ;
			}
		}
		else
			ft_error_management(data, 2, (void **)&line, fd);
	}
	ft_lstadd(&(data->scene), ft_lstnew((void *)sphere, SPHERE));
}
