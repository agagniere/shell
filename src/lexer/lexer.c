/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angagnie <angagnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 14:09:54 by angagnie          #+#    #+#             */
/*   Updated: 2017/03/16 15:26:37 by angagnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_antoine(t_string *str, t_sh_context *w)
{
	t_sis	in;

	in = NEW_SIS(str)
		sh_parse((t_is *)&in, w);
	return (0);
}

int		sh_parse(t_is *in, t_sh_context *w)
{
	t_tokenizer		*tk;

	tk = NEW_TOKENIZER(in);

}
