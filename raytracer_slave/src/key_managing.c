/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_managing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <abiri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:12:32 by azarzor           #+#    #+#             */
/*   Updated: 2020/02/12 09:04:00 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			ft_key_stroke(int key, t_rtv *rtv)
{
	t_vector move;

	(key == EXIT) ? ft_exit(rtv) : 1;
	if (key == SAVE)
		ft_dump_bitmap(&rtv->mlx.img);
	if (key == LEFT || key == RIGHT || key == UP ||
		key == DOWN || key == FOREWORD || key == BACKWARD)
	{
		rtv->actions.mouvement = 1;
		rtv->anti_aliasing = 0;
		rtv->render_offset = PIXEL_SIZE;
		rtv->render_y_offset = PIXEL_SIZE;
		rtv->pixel_size = PIXEL_SIZE;
		move = (t_vector){0, 0, 0};
		static double	angles[3] = {0, 0, 0};
		if (key == RIGHT)
			angles[0] += M_PI/36;
		if (key == LEFT)
			angles[0] -= M_PI/36;
		if (key == UP)
			angles[1] += M_PI/36;
		if (key == DOWN)
			angles[1] -= M_PI/36;
		rtv->cam.look_at.x = 5 * cos(angles[0]);
		rtv->cam.look_at.z = 5 * sin(angles[0]);
		rtv->cam.look_at.y = 5 * sin(angles[1]);
		if (key == FOREWORD)
			rtv->cam.position = ft_add_vector(rtv->cam.position, ft_normalise_vector(rtv->cam.look_at));
		if (key == BACKWARD)
			rtv->cam.position = ft_sub_vector(rtv->cam.position, ft_normalise_vector(rtv->cam.look_at));
		rtv->cam.look_at = ft_add_vector(rtv->cam.position, rtv->cam.look_at);
		/*
		move = ft_scale_vector(ft_normalise_vector(
			ft_sub_vector(rtv->cam.look_at, rtv->cam.position)), 3);*/

		/*(key == LEFT) ? rtv->cam.position.x -= 3 : 0;
		(key == RIGHT) ? rtv->cam.position.x += 3 : 0;
		(key == UP) ? rtv->cam.position.y += 3 : 0;
		(key == DOWN) ? rtv->cam.position.y -= 3 : 0;
		(key == FOREWORD) ? rtv->cam.position.z += 3 : 0;
		(key == BACKWARD) ? rtv->cam.position.z -= 3 : 0;*/
		ft_init_cam(rtv);
	}
	return (0);
}

void		ft_put_pixel(t_rtv *rtv, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < rtv->render_offset)
	{
		j = -1;
		while (++j < rtv->render_y_offset)
		{
			if (rtv->row >= 0 && rtv->row < rtv->scene.width &&
				rtv->column >= 0 && rtv->column < rtv->scene.height)
				rtv->mlx.img.data[(int)
				(((int)(rtv->column - j) % rtv->scene.height)
				* rtv->scene.width + (int)(rtv->row - i)
				% rtv->scene.width)] = color;
		}
	}
	if (rtv->row >= 0 && rtv->row < rtv->scene.width &&
		rtv->column >= 0 && rtv->column < rtv->scene.height)
		rtv->mlx.img.data[
			(int)(rtv->column * rtv->scene.width + rtv->row)] = color;
}

int			ft_frame_loop(void *arg)
{
	t_rtv	*rtv;

	rtv = arg;
	if (rtv->render_offset >= 0 && rtv->render_y_offset >= 0)
		ft_ray_shooter(rtv);
	else if (rtv->anti_aliasing != rtv->scene.aa)
	{
		rtv->render_offset = 0;
		rtv->render_y_offset = 0;
		rtv->pixel_size = 1;
		rtv->anti_aliasing = rtv->scene.aa;
		ft_ray_shooter(rtv);
	}
	mlx_put_image_to_window(rtv->mlx.mlx_ptr, rtv->mlx.win,
			rtv->mlx.img.img_ptr, 0, 0);
	return (0);
}

void		ft_init_rendrering(t_rtv *rtv)
{
	rtv->anti_aliasing = 0;
	rtv->render_offset = PIXEL_SIZE;
	rtv->render_y_offset = PIXEL_SIZE;
	rtv->pixel_size = PIXEL_SIZE;
	rtv->anti_aliasing = 0;
	rtv->actions.mouvement = 0;
}

void		ft_init_win(t_rtv *rtv)
{
	ft_init_rendrering(rtv);
	rtv->mlx.mlx_ptr = mlx_init();
	rtv->mlx.img.img_ptr = mlx_new_image(rtv->mlx.mlx_ptr,
			rtv->scene.width, rtv->scene.height);
	rtv->mlx.img.data = (int*)mlx_get_data_addr(rtv->mlx.img.img_ptr,
			&rtv->mlx.img.bpp, &rtv->mlx.img.size_l, &rtv->mlx.img.endian);
	rtv->mlx.win = mlx_new_window(rtv->mlx.mlx_ptr, rtv->scene.width,
		rtv->scene.height, "RTV1");
	rtv->mlx.img.height = rtv->scene.height;
	rtv->mlx.img.width = rtv->scene.width;
	mlx_hook(rtv->mlx.win, 2, 0, &ft_key_stroke, rtv);
	mlx_hook(rtv->mlx.win, 17, 1, (*ft_exit), &rtv);
	mlx_loop_hook(rtv->mlx.mlx_ptr, &ft_frame_loop, rtv);
	mlx_loop(rtv->mlx.mlx_ptr);
}
