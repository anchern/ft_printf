/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_procdouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:55:00 by achernys          #+#    #+#             */
/*   Updated: 2018/05/01 16:57:03 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define MAXNUM 38

static __int128	getfract(t_data * data, long double num)
{
	int end;
	int i;

	i = 0;
	end = data->precision == -1 ? 6 : data->precision;
	while (i < end && i < 48)
	{
		num *=10;
		i += 1;
	}
	return ((__int128)round(num));
}

char	*get_fractpart(t_data * data, long double num)
{
	__int128_t			intpart;
	long double			fractpart;
	char				*outstr;
	char				*tmp;

	intpart = (__int128_t)num;
	fractpart = num - (long double)intpart;
	if (data->precision == 0)
		return("");
	outstr = ft_strnew((size_t)(data->precision == -1 ? 7 : data->precision + 1));
	ft_memset((void *)outstr, '0', (size_t)(data->precision == -1 ? 7 : data->precision + 1));
	outstr[0] = '.';
	if ((intpart = getfract(data, fractpart)) != 0)
	{
		tmp = ft_bitoa(intpart);
		ft_strcpy(&outstr[1], tmp);
		ft_memdel((void **) &tmp);
	}
	return (outstr);
}

static int	getlennum(long double num)
{
	int i;

	i = 0;
	while (num >= 1)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*procf(char identifier, t_data *data, t_argptrsave *structarg)
{
	long double num;
	char		*intpart;
	char		*fractpart;
	char		*res;
	int			lennum;
	char		*tmpintpart;
	long double	tmpnum;

	if (data->L > 0)
		num = get_ldouble(&structarg->argptrcurr);
	else
		num = get_double(&structarg->argptrcurr);
	if (isnan(num))
		return (ft_strdup(identifier == 'F' ? "NAN" : "nan"));
	if (isinf(num))
		return (ft_strdup(identifier == 'F' ? "INF" : "inf"));
	if ((lennum = getlennum(num)) > MAXNUM)
	{
		tmpnum = num;
		while (tmpnum >= 1)
			tmpnum /= 10;
		tmpintpart = ft_bitoa((__int128)(tmpnum * (long double)ft_pow(10, MAXNUM)));
		if (data->precision == 0)
		{
			res = ft_strnew((size_t)lennum);
			ft_memset((void *) res, '0', (size_t)lennum);
		}
		else
		{
			res = ft_strnew((size_t)lennum +
				(size_t)(data->precision == -1 ? 6 : data->precision) + 1);
			ft_memset((void *) res, '0', (size_t)lennum +
				(size_t)(data->precision == -1 ? 6 : data->precision) + 1);
			res[lennum] = '.';
		}
		ft_memcpy((void *)res, (void *)tmpintpart, MAXNUM);
		ft_memdel((void **)&tmpintpart);
		return (res);
	}
	intpart = ft_bitoa((__int128)(data->precision == 0 ? round(num) : num));
	fractpart = get_fractpart(data, ABS(num));
	res = ft_strjoin(intpart, fractpart);
	ft_memdel((void **)&intpart);
	return (res);
}
