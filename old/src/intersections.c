#include "../inc/cub.h"

bool    right_side(double angle)
{
    if (angle <= (M_PI / 2) && angle >= 0)
        return (true);
    return (false);
}

double  cal_distance(double x1, double y1, double x2, double y2)
{
    double deltaX;
    double deltaY;

    deltaX = x2 - x1;
    deltaY = y2 - y1;
    double distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    return (distance);
}

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

void	first_ver_intersect(t_cub *cub)
{
    double  Y1;
    double  Y2;

    if (right_side(cub->angle))
	    cub->x_v = (floor(cub->p_x / 32) + 1 ) * 32;
    else
        cub->x_v = floor(cub->p_x / 32) * 32;
	Y1 = floor(cub->p_y / 32) * 32 + \
    (cub->x_v - cub->p_x) * tan(cub->angle);
    Y2 = Y1 - floor(cub->p_y / 32) * 32;
    cub->p_y = floor(cub->p_y / 32) * 32 + Y2;
}

void	next_ver_intersect(t_cub *cub)
{
    if (right_side(cub->angle))
    {
	    cub->x_v += 32;
	    cub->y_v += (32 * tan(cub->angle));
    }
    else
    {
        cub->x_v -= 32;
        cub->y_v += (-32 * tan(cub->angle));
    }
}
/*
void    intersections(t_cub *cub)
{
    double dis_h;
    double dis_v;

 horizontal_intersection(cub);
   // vertical_intersection(cub);
   /*dis_h = cal_distance(cub->p_x, cub->p_y, cub->x_h, cub->y_h);
    dis_v = cal_distance(cub->p_x, cub->p_y, cub->x_v, cub->y_v);
    if (dis_h > dis_v)
    {
        cub->x_h = cub->x_v;
        cub->y_h = cub->y_v;
    }
	//my_mlx_pixel_put(cub->data, cub->x_h, cub->y_h, 0xff00000)
}*/