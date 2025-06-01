#include "ft_conversion.h"
#include "minirt_defs.h"
#include "minirt_errors.h"
#include "minirt_graphics.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static bool	create_screenshots_dir(void)
{
	struct stat	st;

	if (stat("screenshots", &st) == -1)
	{
		if (mkdir("screenshots", 0777) == -1)
		{
			warning("failed to create dir", "screenshots");
			return (false);
		}
	}
	else if (S_ISREG(st.st_mode))
	{
		warning("could not create 'screenshots' directory",
			"a file by that name already exists");
		return (false);
	}
	return (true);
}

static char	*get_valid_screenshot_filename(char filename[32])
{
	int		i;
	char	*i_str;

	i = 0;
	strncpy(filename, "screenshots/screenshot_0.bmp", 32);
	while (access(filename, F_OK) == 0)
	{
		i++;
		if (i == 10000)
		{
			warning("max screenshots reached (10000)",
				"please remove some of the screenshots from the directory");
			return (NULL);
		}
		i_str = ft_itoa(i);
		if (!i_str)
			return (NULL);
		strncpy(filename, "screenshots/screenshot_", 32);
		strcat(filename, i_str);
		free(i_str);
		strcat(filename, ".bmp");
	}
	return (filename);
}

static u_int32_t	get_file_size(void)
{
	const u_int32_t	headers_size = 54;
	const u_int32_t	row_size = ((WIN_X * 3 + 3) / 4) * 4;

	return (headers_size + row_size * WIN_Y);
}

static void	write_le_uint16(int fd, u_int32_t value)
{
	char	bytes[2];

	bytes[0] = value & 0xFF;
	bytes[1] = (value >> 8) & 0xFF;
	write(fd, bytes, 2);
}

static void	write_le_uint32(int fd, u_int32_t value)
{
	char	bytes[4];

	bytes[0] = value & 0xFF;
	bytes[1] = (value >> 8) & 0xFF;
	bytes[2] = (value >> 16) & 0xFF;
	bytes[3] = (value >> 24) & 0xFF;
	write(fd, bytes, 4);
}

static void	write_le_color(int fd, t_color color)
{
	write(fd, &color.b, 1);
	write(fd, &color.g, 1);
	write(fd, &color.r, 1);
}

static void	write_bmp_header(int fd)
{
	write(fd, "BM", 2);                   // Bitmap identifier
	write_le_uint32(fd, get_file_size()); // File size in bytes
	write_le_uint32(fd, 0);               // Reserved (empty)
	write_le_uint32(fd, 54);              // Offset (start of data)
}

static void	write_dib_header(int fd)
{
	write_le_uint32(fd, 40);     // header_size
	write_le_uint32(fd, WIN_X);  // image width in pixels
	write_le_uint32(fd, -WIN_Y); // image height in pixels
	write_le_uint16(fd, 1);      // number of planes (1)
	write_le_uint16(fd, 24);     // bits per pixel
	write_le_uint32(fd, 0);      // compression (0 = no compression)
	write_le_uint32(fd, 0);      // compressed size
	write_le_uint32(fd, 2835);   // horizontal resolution
	write_le_uint32(fd, 2835);   // vertical resolution
	write_le_uint32(fd, 0);      // number of colors (0 if 24 bpp)
	write_le_uint32(fd, 0);      // important colors (0 = all)
}

static void	mlx_write_img_to_bmp(int fd, t_img_data img_data)
{
	t_ivec2	coords;

	write_bmp_header(fd);
	write_dib_header(fd);
	coords.y = 0;
	while (coords.y < WIN_Y)
	{
		coords.x = 0;
		while (coords.x < WIN_X)
		{
			write_le_color(fd, get_pixel_color(img_data, coords));
			coords.x++;
		}
		for (int i = 0; (WIN_X * 3 + i) % 4 != 0; i++)
			write(fd, "\0", 1);
		coords.y++;
	}
}

void	save_image(t_state *state)
{
	char	filename[32];
	int		fd;

	if (!create_screenshots_dir())
		return ;
	if (!get_valid_screenshot_filename(filename))
		return ;
	fd = open(filename, O_CREAT | O_WRONLY, 0666);
	if (fd == -1)
	{
		warning(NULL, "screenshot failed");
		return ;
	}
	info(NULL, "screenshot in progress...");
	if (state->post_process == PP_NONE)
		mlx_write_img_to_bmp(fd, state->img_data);
	else
		mlx_write_img_to_bmp(fd, state->processed_img);
	info("screenshot taken", filename);
}
