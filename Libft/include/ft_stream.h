/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stream.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 19:37:02 by angagnie          #+#    #+#             */
/*   Updated: 2017/02/10 04:16:59 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STREAM_H
# define FT_STREAM_H

typedef struct s_is		t_is;
typedef struct s_fis	t_fis;

/*
** InputStream
*/

struct					s_is
{

};

/*
** FileInputStream
*/

struct					s_fis
{
	t_is		super;
	char		*buff;
	size_t		i;
	int			fd;
};

#endif
