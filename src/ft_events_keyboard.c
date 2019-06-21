/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_keyboard.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 13:27:08 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/14 13:28:57 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int     mouse_move(int x, int y, t_data *data)
{
    data->worldpos.v[X] = x;
    data->worldpos.v[Y] = y;
   // printf("x == %d\ny == %d\n----------\n", (int)ft_get_world_pos((double)x, 800, 1), (int)ft_get_world_pos((double)y, 800, 1));
    return (0);
}

int     key_press(int key_code, t_data *data)
{
    if (key_code == 53)
    {
        mlx_destroy_image(data->mlx, data->img_ptr);
        mlx_destroy_window(data->mlx, data->win);
        // free(data);
        // data = NULL;
        exit(0);
    }
    return (0);
}

int     mouse_press(int button, int x, int y, t_data *data)
{
	ft_refresh_image(data);
    (void)x;
    (void)y;
	if (button == LEFT_CLICK)
		data->movex++;
	if (button == RIGHT_CLICK)
		data->movex--;
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);

    return (0);
}
