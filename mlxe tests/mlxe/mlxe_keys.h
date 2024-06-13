/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxe_keys.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:09:30 by lfarhi            #+#    #+#             */
/*   Updated: 2024/06/13 16:18:30 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXE_KEYS_H
# define MLXE_KEYS_H

# include <X11/X.h>
#include <X11/keysym.h>

# define STATE_NOTHING 0x00
# define STATE_ONDOWN 0x01
# define STATE_ONPRESSED 0x02
# define STATE_ONRELEASE 0x03

# define MAX_KEYS 65535 + 1
# define MAX_MOUSE 5 + 1
# define MAX_ALL_KEYS MAX_KEYS + MAX_MOUSE

# define MOUSE_LEFT MAX_KEYS + 1
# define MOUSE_MIDDLE MAX_KEYS + 2
# define MOUSE_RIGHT MAX_KEYS + 3
# define MOUSE_SCROLL_UP MAX_KEYS + 4
# define MOUSE_SCROLL_DOWN MAX_KEYS + 5

#endif