/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_procdouble.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:55:00 by achernys          #+#    #+#             */
/*   Updated: 2018/05/01 19:54:34 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#define MAXNUM 38

static __int128	getfract(t_data * data, long double num)
{
	int 		end;
	int 		i;
	__int128	tmpint;

	i = 0;
	end = data->precision == -1 ? 6 : data->precision;
	while (i < end && i < MAXNUM)
	{
		num *=10;
		i += 1;
	}
	tmpint = (__int128)num;
	num -= (long double) tmpint;
	if (num >= 0.5)
		tmpint++;
	return ((__int128)tmpint);
}

char	*get_fractpart(t_data * data, long double num, int *flag)
{
	__int128_t		intpart;
	long double		fractpart;
	char			*outstr;
	char			*tmp;

	fractpart = num;
	if (data->precision == 0)
		return("");
	outstr = ft_strnew((size_t)(data->precision == -1 ? 7 : data->precision + 1));
	ft_memset((void *)outstr, '0', (size_t)(data->precision == -1 ? 7 : data->precision + 1));
	outstr[0] = '.';
	if ((intpart = getfract(data, fractpart)) != 0)
	{

		tmp = ft_bitoa(intpart);
		if (ft_strlen(tmp) > ft_strlen(&outstr[1]))
		{
			*flag = 1;
			ft_memdel((void **) &tmp);
			return (outstr);
		}
		ft_memcpy((void *)(&outstr[1]), (void *)tmp, MAXNUM);
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
	__int128	tmpint;
	long double	tmpnum;
	int			flag;

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
	flag = 0;
	tmpint = (__int128)num;
	num -= (long double) tmpint;
	if ( data->precision == 0 && num >= 0.5)
		tmpint++;
	fractpart = get_fractpart(data, ABS(num), &flag);
	if (flag == 1)
		tmpint++;
	intpart = ft_bitoa(tmpint);
	res = ft_strjoin(intpart, fractpart);
	ft_memdel((void **)&intpart);
	ft_memdel((void **)&fractpart);
	return (res);
}
