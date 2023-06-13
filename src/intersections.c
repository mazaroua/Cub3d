#include "../inc/cub.h"

bool    right_side(double rayangle)
{
    if ((rayangle > 3 * (M_PI / 2) && rayangle <= 2 * M_PI)
        || (fabs(rayangle) >= 0 && rayangle < M_PI / 2))
        return (true);
    // if ((rayangle * (180 / M_PI) > 270 && rayangle * (180 / M_PI) <= 360)
	// 	|| (fabs(rayangle * (180 / M_PI)) >= 0 && rayangle * (180 / M_PI) < 90))
    //     return (true);
    return (false);
}


int is_wall(t_cub *cub, double x, double y)
{
    int X;
    int Y;

    X = (int)floor(x / S_SIZE);
    Y = (int)floor(y / S_SIZE);
	if (X < 0 || X > (cub->win_width / S_SIZE) - 1
		|| Y < 0 || Y > (cub->win_height / S_SIZE) - 1)
		return (-1);
    if (cub->map_2d[Y][X] == '1')
        return (1);
	if (cub->map_2d[Y][X] == 'D')
		return (2);
    return (0);
}

int player_up(double angle)
{
    if ((angle * (180 / M_PI)) > (double)180
		&& (angle * (180 / M_PI)) < (double)360)
        return (1);
    return (0);
}

void    first_horizontal_intersection(double rayangle, t_cub *cub)
{
	if (player_up(rayangle))
    {
        cub->y_h = floor(cub->p_y / S_SIZE) * S_SIZE;
    }
    else
        cub->y_h = floor(cub->p_y / S_SIZE) * S_SIZE + S_SIZE;
    cub->x_h = (cub->y_h - cub->p_y) / tan(rayangle) + cub->p_x;
}

void    next_horizontal_intersection(double rayangle, t_cub *cub)
{
    if (player_up(rayangle))
    {
        cub->y_h -= S_SIZE;
        cub->x_h += (-S_SIZE / tan(rayangle));
    }
    else
    {
        cub->y_h += S_SIZE;
        cub->x_h += (S_SIZE / tan(rayangle));
    }
}

void    horizontal_intersection(double rayangle, t_cub *cub)
{
   	first_horizontal_intersection(rayangle, cub);
	if (!is_wall(cub, cub->x_h, cub->y_h + 1)
		&& !is_wall(cub, cub->x_h, cub->y_h - 1))
	{
		while (true)
		{
			next_horizontal_intersection(rayangle, cub);
			if (is_wall(cub, cub->x_h, cub->y_h + 1)
                || is_wall(cub, cub->x_h, cub->y_h - 1))
				break ;
		}
 	}
}

void	first_ver_intersect(double rayangle, t_cub *cub)
{
    double  Y1;
	double	xdiff;

    if (right_side(rayangle))
	    cub->x_v = (floor(cub->p_x / S_SIZE) + 1 ) * S_SIZE;
    else
    	cub->x_v = floor(cub->p_x / S_SIZE) * S_SIZE;
	xdiff = cub->x_v - cub->p_x;
	Y1 = xdiff * tan(rayangle);
	cub->y_v = cub->p_y + Y1;
}

void	next_ver_intersect(double rayangle, t_cub *cub)
{
    if (right_side(rayangle))
    {
	    cub->x_v += S_SIZE;
	    cub->y_v += (S_SIZE * tan(rayangle));
    }
    else
    {
        cub->x_v -= S_SIZE;
        cub->y_v += (-S_SIZE * tan(rayangle));
    }
}

void	vertical_intersection(double rayangle, t_cub *cub)
{
	first_ver_intersect(rayangle, cub);
	if (!is_wall(cub, cub->x_v + 1, cub->y_v)
		&& !is_wall(cub, cub->x_v - 1, cub->y_v))
	{
		 while (true)
		{
			next_ver_intersect(rayangle, cub);
			if (is_wall(cub, cub->x_v + 1, cub->y_v)
                || is_wall(cub, cub->x_v - 1, cub->y_v))
				break ;
		}
	}
}

double  cal_distance(double x1, double y1, double x2, double y2)
{
    double deltaX;
    double deltaY;

    deltaX = fabs(x2 - x1);
    deltaY = fabs(y2 - y1);
    return (sqrt(deltaX * deltaX + deltaY * deltaY));
}

void    intersections(double rayangle, t_cub *cub)
{
	double dis_h;
	double dis_v;

    cub->vert_line = false;
    cub->hori_line = false;
	cub->door = false;
	horizontal_intersection(rayangle, cub);
 	vertical_intersection(rayangle, cub);
	dis_h = cal_distance(cub->p_x, cub->p_y, cub->x_h, cub->y_h);
	dis_v = cal_distance(cub->p_x, cub->p_y, cub->x_v, cub->y_v);
    if (dis_h > dis_v)
    {
        cub->vert_line = true;
        cub->next_x = cub->x_v;
        cub->next_y = cub->y_v;
        cub->x_offset = (int)cub->y_v % S_SIZE;
   	}
	else
	{
        cub->hori_line = true;
 		cub->next_x = cub->x_h;
 		cub->next_y = cub->y_h;
        cub->x_offset = (int)cub->x_h % S_SIZE;
	}
}