#include "../inc/cub.h"

int is_wall(t_cub *cub, double x, double y)
{
    int X;
    int Y;

    X = floor(x / 32);
    Y = floor(y / 32) - 1;
    if (cub->map_2d[Y][X] == '1')
    {
        return (1);
    }
    return (0);
}

int player_up(t_cub *cub)
{

    if ((cub->angle * (180 / M_PI)) > (double)180 && (cub->angle * (180 / M_PI)) < (double)360)
        return (1);
    return (0);
}

void    first_horizontal_intersection(t_cub *cub)
{
    if (player_up(cub))
    {
        cub->y_h = floor(cub->p_y / 32) * 32;
        puts("1");
    }
    else
    {
        cub->y_h = floor(cub->p_y / 32) * 32 + 32;
        puts("2");
    }
    cub->x_h = ((cub->p_y - cub->y_h) / tan(cub->angle)) + cub->p_x;
}

void    next_horizontal_intersection(t_cub *cub)
{
    if (player_up(cub))
    {
        cub->y_h -= 32;
        cub->x_h += (-32 / tan(cub->angle));
    }
    else
    {
        cub->y_h += 32;
        cub->x_h += (32 / tan(cub->angle));
    }
}

void    horizontal_intersection(t_cub *cub)
{
    if (!(cub->angle * (M_PI / 180) == 180 || cub->angle * (M_PI / 180) == 360))
    {
        first_horizontal_intersection(cub);
        while (1)
        {
            if (is_wall(cub, cub->x_h, cub->y_h))
                break ;
            next_horizontal_intersection(cub);
        }

    }
}