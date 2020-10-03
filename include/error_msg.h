/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseinic <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:01:36 by mseinic           #+#    #+#             */
/*   Updated: 2017/02/20 18:09:22 by mseinic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSG_H
# define ERROR_MSG_H
# define NO_PERMISSION_MSG "permission denied"
# define NO_DIRECTORY_MSG "not a directory"
# define NO_FILE_OR_DIR_MSG "no such file or directory"
# define NO_PERMISSION(C, F) (error_msg(C, NO_PERMISSION_MSG, F))
# define NO_FILE_OR_DIR(C, F) (error_msg(C, NO_FILE_OR_DIR_MSG, F))
# define NOT_A_DIR(C, F) (error_msg(C, NO_DIRECTORY_MSG, F))

void	error_msg(char *cmd, char *msg, char *file);
#endif
