/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iscntrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:46:08 by angagnie          #+#    #+#             */
/*   Updated: 2015/11/27 11:16:05 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iscntrl(int c)
{
	return ((0 <= c && c < ' ') || (c == 127));
}
