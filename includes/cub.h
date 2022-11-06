/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fate <fate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 07:44:15 by gtrinida          #+#    #+#             */
/*   Updated: 2022/11/03 01:50:41 by fate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <errno.h>
# include <string.h>
# include "../gnl/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../minilibx_macos/mlx.h"


// # define mapWidth 24
// # define mapHeight 24

# define screenWidth 1920
# define screenHeight 1080
// # define texWidth 64
// # define texHeight 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define FLOOR 4
# define CEIL 5

# define CUB_OK 0
# define CUB_ERR 1
# define TOO_MANY_ARGS 2
# define NO_FILE_PASSED 3
# define WRONG_FILE_TYPE 4
# define EMPTY_FILE 5
# define INVALID_CONFIG_PARAM 6
# define NO_MAP_IN_CONFIG 7
# define UNKNOW_SYM 8
# define INVALID_MAP 9
# define EMPTY_IDENTIFER 10
# define IDENTIFER_ALREADY_EXIST 11
# define NOT_RGB 12
# define END_CONFIG 13
# define TEXTURE_PATH_ERROR 14
# define CANT_CONVERT 15
# define TOO_MANY_PLAYERS 16
# define UNCLOSED_MAP 17
# define NO_PLAYER 18

# define NORTH_TEXTURE_IDENTIFER "NO"
# define SOUTH_TEXTURE_IDENTIFER "SO"
# define WEST_TEXTURE_IDENTIFER "WE"
# define EAST_TEXTURE_IDENTIFER "EA"
# define FLOOR_COLOR_IDENTIFER "F"
# define CEILLING_COLOR_IDENTIFER "C"

# define PNG 0
# define XPM 1

# define NO_INDEX 0
# define SO_INDEX 1
# define WE_INDEX 2
# define EA_INDEX 3
# define SCREEN_INDEX 4
# define MINIMAP_INDEX 5
# define F_INDEX 4
# define C_INDEX 5

# define UP 0
# define DOWN 1
# define RIGHT 2
# define LEFT 3

# define BLOCK_SIZE 25

typedef struct s_pos
{
    double	pos_x; //позиция по x координате
	double	pos_y; //позиция по y координате
	double	dir_x; //вектор направления
	double	dir_y; //вектор направления
	double	plane_x; //плоскость камеры
	double	plane_y; //плоскость камеры (по сути своей FoV, изначально будет 66)
	double	camera_x; //текущая координата x
	double	raydir_x; //направление луча по координате x
	double	raydir_y; //направление луча по координате у
	double	sidedist_x; //расстояние для луча от своего начального положения 
	//до ближайшей стороны х
	double	sidedist_y; //расстояние для луча от своего начального положения
	//до ближайшей стороны у
	double	deltadist_x; //расстояние, которое луч должен пройти от 1 стороны x
	//до другой стороны х
	double	deltadist_y; //расстояние, которое луч должен пройти от 1 стороны y
	//до другой стороны y
	double	perpwalldist; //вычесление длины луча
	int		map_x; //текущий квадрат карты на котором находится луч по х
	int		map_y; //текущий квадрат карты на котором находится луч по у
	int		step_x; //в каком направлении двигаться
	int		step_y; //в каком направлении двигаться
	int		hit; //проверка на попадание луча в стену
	int		side; //тип стены в которую попал луч
	int		line_height; //высота стены
	int		draw_start; //нижняя точка стены
	int		draw_end; //высшая точка стены
	int		color;   //цвет????????
	double	old_plane_x;
	double	old_dir_x;
	double	move_speed;
	double	wall_x; //точное место попадания луча по стене
	int		tex_x;
	int		tex_y;
	int		tex_n;
	int		tex_num;                                          
}t_pos;

typedef	struct s_texture
{
	int	bpp;
	int	size_line;
	int	endian;
	int	width;
	int	height;
	int	*texture;
	int	*img;
	char	*path;
	int		side;
	
}	t_texture;

typedef struct s_config
{
	char	**config_txt;
	char	*path_to_texture[4];
	int		colors[2];
}t_config;

typedef	struct t_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
	char		*map_path;
	char		**map;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		**swne_path;
	int			floor_color;
	int			ceil_color;
	int			fd;
	int			strs;
	int			map_height;
	int			map_width;
	t_pos		*info;
	t_texture	**textures;
}t_mlx;

/*----read_config----*/
int	fill_list(int fd, t_list **list);
int	read_config(char ***config, char *path_to_cfg);

/*----parse_config----*/
int		parse_config(t_mlx *mlx, char *path_to_cfg);
int	parse_settings(t_mlx *mlx, t_config *config, int *end_of_config);

/*----convert_img----*/
int	convert_img(t_mlx *mlx, t_config *config);

/*----parse_config_line----*/
int	check_config_param(t_config *cfg);
int	get_identefer_index(char *str);
int	parse_path(t_config *config, char *str, int index);
int	parse_color(t_config *config, char *str, int index);
int	parse_identefer(t_config *config, char *str);

/*----parse_rgb----*/
int	parse_rgb(char *str, int *color);

/*----parse_config_map----*/
int	is_empty_line(char *line);
int	is_closed(char **map);
int	map_check_valid_sym(t_config *cfg, int start_map);
int	parse_map(t_mlx *mlx, t_config *cfg, int end_of_config);

/*----------UTILS---------*/

/*----utils----*/
char	**lst_to_arr(t_list *list, int len);
int		is_space(char c);
int	is_player(char c);
int is_map_object(char c);
int	is_inner_object(char c);
void	ft_log(char *str); //debug

/*----print_utils----*/
void	init_image(t_mlx *mlx, int index, int width, int height);
int	player_pos(float p);

/*----clear----*/
void	safe_free(void *data);
void	free_img(t_mlx *mlx, t_texture *img);
void	free_strarr(char **strings);
void	clear_cub(t_mlx *mlx);

/*----validate----*/
int	check_file_type(char *str, char *file_type);
int		check_argv(int argc, char **argv);

/*----print_error----*/
void	print_error(int error);
void	error_in_line(char *str, int error);

/*----print_default----*/
void		print_config_format(void);

/*----color----*/
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);


int			ft_check(t_mlx *mlx, int side, char *line);
int			fill_floor_ceil(t_mlx *mlx, char *line, int f_or_c);
int			get_path(t_mlx *mlx);
int			close_window(int key, t_mlx *mlx);
int			close_button(void *cub);
void		start_turn(t_mlx *mlx, t_pos *info, double rotate);
void		redraw_window(t_mlx *mlx);
void		put_pixel_img(t_mlx *mlx, int x, int y, int color);
void		initilization(t_mlx *mlx, char *line);
void		gameloop(t_mlx *mlx);
void		left_turn(t_mlx *mlx, t_pos *info);
void		right_turn(t_mlx *mlx, t_pos *info);
void		go_forward(t_mlx *mlx);
void		go_back(t_mlx *mlx);
void		go_left(t_mlx *mlx);
void		go_right(t_mlx *mlx);
void		exit_arg();
void		sky_and_floor(t_mlx *mlx);
void		init_ray(t_pos *info, t_mlx* mlx, int x);
void		ray_calculate(t_pos *info, t_mlx *mlx);
void		check_wall_hit(t_pos *info, t_mlx *mlx);
void		check_steps(t_pos *info);
void		get_textures(t_mlx *mlx);
int			close_buttonV2(t_mlx *mlx); //временное название потом убрать
void		clear_cub(t_mlx *mlx);

t_texture	*xpg_to_img(t_mlx *mlx, char *path_to_file);

#endif
