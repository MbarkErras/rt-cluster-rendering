/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master_raytracer.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <merras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 08:50:37 by abiri             #+#    #+#             */
/*   Updated: 2020/02/21 22:43:44 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MASTER_RAYTRACER_H
# define MASTER_RAYTRACER_H
# include <mlx.h>
# include <dirent.h>
# include "master_middlewares.h"
# define TEXTURES_DIR "textures/"
# define WIDTH (720 * 1.7777777778)
# define HEIGHT 720

typedef struct	s_img
{
	void		*mlx_win;
	void		*mlx_ptr;
	void		*mlx_img;
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win;
	t_img	img;
}				t_mlx;
typedef struct	s_master_env
{
	t_mlx	mlx;
}				t_master_env;

#endif
