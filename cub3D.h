#ifndef CUB3D_H
#define CUB3D_H

#include "libft/libft.h"
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <string.h>
#include "gnl/get_next_line.h"
#include "mlx.h"

# define MAX(a, b)  (a < b) ? b : a;
# define MIN(a, b)  (a > b) ? b : a;

# define ROTSPEED 0.2
# define MOVSPEED 0.2

typedef struct s_vect
{
    double x; 
    double y;

}               t_vect;

typedef struct s_ray
{
    t_vect dir;
    t_vect dist;
    double walldist;
    int stepx;
    int stepy;
    int mapx;
    int mapy;
    double wallx;
	int textn;
    t_vect side;
    int hit;
    int wallside;
    double x; //camera x
} t_ray;

typedef struct s_wind
{
	void *mlx_ptr;
	void *img_ptr;
	void *mlx_wind;
	int   *tab_img;
	void  *img;
}               t_wind;

typedef struct s_texture
{
    int *data;
    int w;
    int h;
} t_texture;

typedef struct s_all
{
    t_wind w;
    t_vect pos;
    t_vect dir;
    t_vect plane;
    int resx;
    int resy;
    t_vect dim;
    t_ray ray;
    t_texture texture[5];
    char **map;
    unsigned int ceil;
    unsigned int floor;
}               t_all;


void	ft_initall(t_all *p, char *file);
t_all	*getall(t_all *a);
t_vect  ft_add(t_vect v1, t_vect v2);
t_vect  ft_multscal(t_vect v1, double sc);
double  ft_vectlenght(t_vect v);
void    ft_update(t_all *p);
void floorceil(int *tab,unsigned int floor, unsigned int ceil, int size);
int ft_key(int key, t_all *p);

#endif