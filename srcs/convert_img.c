#include "cub.h"

static void in_path_error(char *path, int err)
{
	ft_putstr_fd("Error in texture: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (err == WRONG_FILE_TYPE)
		ft_putendl_fd("wrong file type", STDERR_FILENO);
	else if (err == CANT_CONVERT)
		ft_putendl_fd("can't convert img", STDERR_FILENO);
}

// t_texture	*xpg_to_img(t_mlx *mlx, char *path_to_file)
// {
// 	t_texture	*t;

// 	t = malloc(sizeof(t_texture));
// 	t->img = mlx_xpm_file_to_image(mlx->mlx_ptr, path_to_file, &(t->width), &(t->height));
// 	if (!t->img)
// 	{
// 		 printf("XPG_TO_IMG\n");
// 		//ft_error();
// 		exit(1);
// 	}
// 	t->texture = (int *)mlx_get_data_addr(t->img, &(t->bpp),
// 			&(t->size_line), &(t->endian));
// 	return (t);
// }

static int	get_img(t_mlx *cub, t_config *cfg, int index)
{
	cub->textures[index] = xpg_to_img(cub, cfg->path_to_texture[index]);
	if (!cub->textures[index])
		return (TEXTURE_PATH_ERROR);
	return (CUB_OK);
}


/*
Нужно преобразовать xpg в img таким образом
	//добавлять высоту и ширину нужно до вызова функции
	mlx->textures[NORTH] = xpg_to_img(mlx, mlx->swne_path[NORTH]);
	mlx->textures[SOUTH] = xpg_to_img(mlx, mlx->swne_path[SOUTH]);
	mlx->textures[EAST] = xpg_to_img(mlx, mlx->swne_path[EAST]);
	mlx->textures[WEST] = xpg_to_img(mlx, mlx->swne_path[WEST]);
	добавить в структуру высоту и ширину текстуры
*/
int	convert_img(t_mlx *cub, t_config *config)
{
	int	err;
	int	f_type;
	int	i;

	ft_log("images convert");
	i = -1;
	while (++i <= EA_INDEX)
	{ 
		ft_log("image converting...");
		if (!check_file_type(config->path_to_texture[i], ".png"))
			f_type = PNG;
		else if (!check_file_type(config->path_to_texture[i], ".xpm"))
			f_type = XPM;
		else
		{
			in_path_error(config->path_to_texture[i], WRONG_FILE_TYPE);
			return (TEXTURE_PATH_ERROR);
		}
		(void)f_type;
		err = get_img(cub, config, i);
		if (err)
			return (err);
	}
	ft_log("images convert end");
	return (CUB_OK);
}
