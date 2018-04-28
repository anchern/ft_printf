/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_procint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 17:37:56 by achernys          #+#    #+#             */
/*   Updated: 2018/04/24 17:59:50 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "ft_printf.h"

static void	dataconversion(t_data *data)
{
	data->hashtag = 0;
	if (data->precision > -1 || data->minus == 1)
		data->zero = 0;
	if (data->plus > 0)
		data->space = 0;
}

static char	*getstr(char **formatstr, t_data *data, size_t *len, char *sign)
{
	char	*outstr;

	if (data->precision > (int)*len)
		*len = (size_t)data->precision;
	if ((*sign = *formatstr[0]) == '-')
	{
		*formatstr[0] = '0';
		*len = data->precision >= (int)ft_strlen(*formatstr) ? *len + 1 : *len;
	}
	else if (data->plus || data->space )
	{
		*sign = (char)(data->plus ? '+' : ' ');
		*len += 1;
	}
	outstr = ft_strnew(*len);
	ft_memset((void *)outstr, '0', *len);
	return (outstr);
}

static char	*numnotationint(char *formatstr, t_data *data, int identifier)
{
	char	*outstr;
	size_t	len;
	char	sign;
	int		i;

	dataconversion(data);
	len = ft_strlen(formatstr);
	if (data->precision < (int)len && !data->plus && !data->space)
			return ((char *) -1);
	outstr = getstr(&formatstr, data, &len, &sign);
	i = (int)ft_strlen(formatstr) - 1;
	while (i >= 0)
	{
		outstr[len - 1] = formatstr[i];
		len--;
		i--;
	}
	if ((sign == '-' || sign == '+' || sign == ' ') &&
			identifier !='u' && identifier != 'U')
		outstr[0] = sign;
	return (outstr);
}

static char	*get_value(t_data *data, t_argptrsave *structarg,
								 char identifier)
{
	if (data->L == 2)
		return (ft_bitoa(va_arg(structarg->argptrcurr, __int128)));
	else if (data->l == 2)
		return (ft_bitoa(get_long(&structarg->argptrcurr)));
	else if (data->j == 1)
		return (ft_bitoa(get_intmax(&structarg->argptrcurr)));
	else if (data->l == 1 || identifier == 'D')
		return (ft_bitoa(get_long(&structarg->argptrcurr)));
	else if (data->z == 1)
		return (ft_bitoa(get_ssize(&structarg->argptrcurr)));
	else if (data->h == 1)
		return (ft_bitoa(get_short(&structarg->argptrcurr)));
	else if (data->h == 2)
		return (ft_bitoa(get_char(&structarg->argptrcurr)));
	else
		return (ft_bitoa(get_int(&structarg->argptrcurr)));
}

char		*procint(t_data *data, t_argptrsave *structarg, char identifier)
{
	char		*outstr;
	char		*resstr;

	if (identifier == 'u' || identifier == 'U')
		resstr = ft_bitoa(get_uvalue(data, structarg, identifier));
	else
		resstr = get_value(data, structarg, identifier);
	if (*resstr == '0' && data->precision == 0)
		*resstr = 0;
	if ((outstr = identifier == 'u' || identifier == 'U' ?
  					numnotationnot(resstr, data, identifier) :
				  numnotationint(resstr, data, identifier)) != (char *)-1)
	{
		ft_memdel((void **) &resstr);
		return (outstr);
	} else
		return (resstr);
}
