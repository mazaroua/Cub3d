/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazaroua <mazaroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 21:14:07 by mazaroua          #+#    #+#             */
/*   Updated: 2023/06/08 22:35:55 by mazaroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

void    load_textures(t_cub *data)
{
    void    *img;

    img = mlx_xpm_file_to_image(data->m_ptr, "./textures/texture1.xpm", &data->texture_width, &data->texture_height);
    data->texture_addr = (unsigned int *)mlx_get_data_addr(img, &data->texture_bpp, &data->texture_sline, &data->texture_endian);
}