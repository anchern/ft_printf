/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 17:56:25 by achernys          #+#    #+#             */
/*   Updated: 2018/05/08 18:23:25 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define MAXNUM 38

static __int128		getfract(int precision, long double num)
{
	int			end;
	int			i;
	__int128	tmpint;

	i = 0;
	end = precision == -1 ? 6 : precision;
	while (i < end && i < MAXNUM)
	{
		num *= 10;
		i += 1;
	}
	tmpint = (__int128)num;
	num -= (long double)tmpint;
	if (num >= 0.5)
		tmpint++;
	return ((__int128)tmpint);
}

static char			*get_fractpart(int precision, long double num, int *flag)
{
	__int128_t		intpart;
	long double		fractpart;
	char			*outs;
	char			*tmp;

	fractpart = num;
	if (precision == 0)
		return (ft_strdup(""));
	outs = ft_strnew((size_t)(precision == -1 ? 7 : precision + 1));
	ft_memset((void *)outs, '0', (size_t)(precision == -1 ? 7 :
					precision + 1));
	outs[0] = '.';
	if ((intpart = getfract(precision, fractpart)) != 0)
	{
		tmp = ft_bitoa(intpart);
		if (ft_strlen(tmp) > ft_strlen(&outs[1]))
		{
			*flag = 1;
			ft_memdel((void **)&tmp);
			return (outs);
		}
		ft_memcpy((void *)(&outs[1]), (void *)tmp, ft_strlen(tmp));
		ft_memdel((void **)&tmp);
	}
	return (outs);
}

char				*ft_ftoa(long double num, int precision)
{
	char		*intpart;
	char		*fractpart;
	char		*res;
	__int128	tmpint;
	int			flag;

	flag = 0;
	tmpint = (__int128)num;
	num -= (long double)tmpint;
	if (precision == 0 && num >= 0.5)
		tmpint++;
	fractpart = get_fractpart(precision, ABS(num), &flag);
	if (flag == 1)
		tmpint++;
	intpart = ft_bitoa(tmpint);
	res = ft_strjoin(intpart, fractpart);
	ft_memdel((void **)&intpart);
	ft_memdel((void **)&fractpart);
	return (res);
}
