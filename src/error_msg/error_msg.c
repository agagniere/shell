/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 16:42:23 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/20 16:49:46 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	error_msg(char *cmd, char *msg, char *file)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(file, 2);
}
