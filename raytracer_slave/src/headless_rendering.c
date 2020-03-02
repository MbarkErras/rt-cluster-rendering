/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headless_rendering.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:45:31 by abiri             #+#    #+#             */
/*   Updated: 2020/03/02 16:05:09 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int	ft_init_rendering_image(t_rtv *rtv)
{
	int	min_h;
	int	max_h;

	min_h = 0;
	max_h = rtv->scene.height;
	read(0, &min_h, 4);
	read(0, &max_h, 4);
	rtv->min_h = min_h;
	rtv->max_h = max_h;
	rtv->mlx.img.height = rtv->scene.height;
	rtv->mlx.img.width = rtv->scene.width;
	rtv->mlx.img.size_l = rtv->scene.width * 4;
	rtv->mlx.img.data = ft_memalloc(sizeof(int) *
		rtv->scene.width * rtv->scene.height);
	return (SUCCESS);
}

void		ft_init_headless_renderer(t_rtv *rtv)
{
	rtv->anti_aliasing = 0;
	rtv->render_offset = 0;
	rtv->render_y_offset = 0;
	rtv->pixel_size = 1;
	rtv->anti_aliasing = rtv->scene.aa;
	rtv->actions.mouvement = 0;
}

#include<errno.h>
#include <string.h>

void	ft_send_final_image(t_rtv *rtv)
{
	int	size;
	int fd;

	fd = open("test_file_1", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		ft_putstr_fd(strerror(errno), 2);
	size = (rtv->max_h - rtv->min_h) * rtv->scene.width * 4;
	ft_putstr_fd("\n\n\n\n\n\n\n\n", fd);
	ft_putstr_fd(ft_itoa((int)rtv->min_h), fd);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(ft_itoa((int)rtv->max_h), fd);
	ft_putstr_fd("\n\n\n\n\n\n\n\n", fd);
	write(1, &size, 4);
	write(1, rtv->mlx.img.data + (int)rtv->min_h * rtv->scene.width * 4, size);
}

int	ft_headless_raytracer(t_rtv	*rtv, char *filename)
{
	ft_init_headless_renderer(rtv);
	ft_init_rendering_image(rtv);
	ft_ray_shooter(rtv);
	ft_send_final_image(rtv);
	ft_save_bitmap(&rtv->mlx.img, "test_bmp_file.bmp");
	return (SUCCESS);
}
