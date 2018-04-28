/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_procnotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:20:39 by achernys          #+#    #+#             */
/*   Updated: 2018/04/26 19:34:59 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	get_uvalue(t_data *data, t_argptrsave *structarg,
								 char identifier)
{
	if (data->l == 2)
		return (get_ullong(&structarg->argptrcurr));
	else if (data->j == 1)
		return (get_uintmax(&structarg->argptrcurr));
	else if (data->z == 1)
		return (get_size(&structarg->argptrcurr));
	else if (data->l == 1 || identifier == 'O' || identifier == 'p' ||
			 identifier == 'U')
		return (get_unlong(&structarg->argptrcurr));
	else if (data->h == 1)
		return (get_unshort(&structarg->argptrcurr));
	else if (data->h == 2)
		return (get_unchar(&structarg->argptrcurr));
	else
		return (get_unint(&structarg->argptrcurr));
}

static char	*getstr(char **formatstr, t_data *data, size_t *len,
					   char identifier)
{
	char	*outstr;

	if (data->precision > (int)*len)
		*len = (size_t)data->precision;
	if ((identifier == 'p' && data->precision != 0) || ((data->hashtag ) &&
			**formatstr != '0' && identifier != 'b'))
	{
		if (identifier == 'x' || identifier == 'X' || identifier == 'p')
			*len += 2;
		else if ((identifier == 'o' || identifier == 'O') &&
			data->precision <= (int)ft_strlen(*formatstr))
			*len += 1;
	}
	outstr = ft_strnew(*len);
	ft_memset((void *)outstr, '0', *len);
	return (outstr);
}

char	*numnotationnot(char *formatstr, t_data *data, char identifier)
{
	char	*outstr;
	size_t	len;
	int		i;

	if (data->precision == 0 && *formatstr == '0' && identifier != 'o' &&
			identifier != 'O' && identifier != 'p')
		return (0);
	if (data->precision > -1 || data->minus == 1)
		data->zero = 0;
	len = ft_strlen(formatstr);
	i = (int)len - 1;
	if (data->precision < (int)len && !data->hashtag && identifier != 'p')
			return ((char *)-1);
	outstr = getstr(&formatstr, data, &len, identifier);
	while (i >= 0)
	{
		outstr[len - 1] = formatstr[i];
		len--;
		i--;
	}
	if (((identifier == 'x' || identifier == 'X') && data->hashtag &&
			*formatstr != '0') || identifier == 'p')
		outstr[1] = (char)(identifier == 'X' ? 'X' : 'x');
	return (outstr);
}

char	*procnotation(t_data *data, t_argptrsave *structarg, char identifier)
{
	unsigned long long	value;
	char				*resstr;
	char 				*outstr;

	resstr = 0;
	value = get_uvalue(data, structarg, identifier);
	if (identifier == 'o' || identifier == 'O')
		resstr = ft_itoabase(value, 8, 'a');
	else if (identifier == 'x' || identifier == 'X' || identifier == 'p')
		resstr = ft_itoabase(value, 16, (char)(identifier == 'X' ? 'A' : 'a'));
	else if (identifier == 'b')
		resstr = ft_itoabase(value, 2, 'a');
	if ((outstr = numnotationnot(resstr, data, identifier)) != (char *)-1)
	{
		ft_memdel((void **) &resstr);
		return (outstr);
	}
	if (*resstr == '0')
	{
		ft_memdel((void **)&resstr);
		return (0);
	} else
		return (resstr);
}