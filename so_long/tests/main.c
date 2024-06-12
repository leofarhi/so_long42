#include <mlx.h>
#include <mlx_int.h>
#include <X11/X.h>

#include <stdio.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


int	key_hook(int keycode,t_vars *vars)
{
	(void)vars;
	printf("keycode: %d\n", keycode);
	return (0);
}

/*int	close(void *param)
{
	printf("Window closed\n");
	t_vars *vars = (t_vars *)param;
	printf("vars->mlx: %p\n", vars->mlx);
	//mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}*/


int main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	char	*relative_path = "./tests/test.xpm";//"./tests/texture2.xpm";
	int		img_width;
	int		img_height;
	void *img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	//mlx_hook(vars.win, ON_DESTROY, 0, close, &vars);
	//printf("img: %p\n", img);
	mlx_put_image_to_window(vars.mlx, vars.win, img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, img, 50, 0);
	//mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, int *width, int *height);
	//mlx_key_hook(vars.win, key_hook, NULL);
	//mlx_string_put(vars.mlx, vars.win, 50, 50, 0x00FFFFFF, "Hello world!");
	mlx_loop(vars.mlx);
	return 0;
}