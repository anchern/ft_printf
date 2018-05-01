/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:23:08 by achernys          #+#    #+#             */
/*   Updated: 2018/05/01 17:12:17 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "ft_printf.h"

/*
** TYPES
**
** ALL: idDnpuoxUOXcCsSfegaFEGA
**
** 1 i d														(int)
** 2 li ld D													(long)
** 3 hi hd 														(short)
** 4 lli lld Li Ld												(ll int)
**
** 5 lln ln hhn hn Ln	n										(int *)
**
** 6 llp lp hhp hp Lp	p										(void *)(lx)
**
** 7 zu zo zx zX												(size_t)(l)
**
** 8 zi zd														(ssize_t)(lu)
**
** 9 u o x X													(u int)
** 10 lu lo lx lX uD uI O U										(u long)
** 11 hu ho hx hX												(u short)
** 12 llu llo llx llX Lu Lo Lx LX								(llu int)
**
** 13 ji jd 													(intmax_t)(ll)
**
** 14 ju jo jx jX												(uintmax_t)(llu)
**
** 15 hhu hho hhx hhX											(u char)
**
** 16 c hc hhc llc Lc hhi hhd									(char)
** 17 lc C														(wchar_t)
**
** 18 s hs hhs lls Ls											(char *)
** 19 ls S														(wchr_t *)
**
** 20 f e g a F E G A l-//- j-//- z-//-							(double)
** 21 llf lle llg lla llE llG llF llA L-//-						(long double)
*/

/*
** FLAGS
**
** # -+0$
*/

static size_t	parse_arg(const char *str, t_argptrsave *structarg)
{
	size_t	addi;
	t_data	*data;
	char	*argstr;

	data = getdatastruct();
	addi = 1;
	processingflags(str, structarg, &addi, data);
	if (str[addi] == 'n')
		procn(structarg->len, structarg, data);
	else if (str[addi] != 0)
	{
		argstr = getargstr(str[addi], data, structarg);
		if (argstr != 0 && ft_strcmp(argstr, "0x"))
			structarg->len += write(1, argstr, ft_strlen(argstr));
		else if (ft_strchr("cCsS", str[addi]))
			structarg->len += printnullstr(data, str[addi]);
		else if (str[addi] == 'p')
			structarg->len += write(1, data->precision == 0 ? "0x" : "0x0",
									data->precision == 0 ? 2 : 3);
		else if (ft_strchr("oOxX", str[addi]) && (argstr == 0 || *argstr == 0)
				 &&	data->precision != 0)
			structarg->len += write(1, "0", 1);
		ft_memdel((void **)&argstr);
	}
	addi = str[addi] == 0 ? addi + 0 : addi + 1;
	ft_memdel((void **)&data);
	return (addi);
}

static int		getoutstr(const char *format, t_argptrsave *structarg)
{
	size_t	i;
	size_t	lencurpart;

	i = 0;
	lencurpart = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != 0)
		{
			structarg->len += write(1, &format[i - lencurpart], lencurpart);
			lencurpart = 0;
			i += parse_arg(&format[i], structarg);
			continue ;
		}
		i++;
		lencurpart++;
	}
	if (lencurpart != 0)
		structarg->len += write(1, &format[i - lencurpart],
					format[i - 1] == '%'? lencurpart - 1 : lencurpart);
	return (structarg->len);
}

int				ft_printf(const char *format, ...)
{
	t_argptrsave	*structarg;
	int			len;

	if (format == 0)
		return (0);
	structarg = (t_argptrsave *)ft_memalloc(sizeof(*structarg));
	structarg->len = 0;
	va_start(structarg->argptrstart, format);
	va_copy(structarg->argptrcurr, structarg->argptrstart);
	va_copy(structarg->argstar, structarg->argptrstart);
	if ((len = getoutstr(format, structarg)) > -1)
	{
		closearglst(structarg);
		ft_memdel((void **)&structarg);
		return (len);
	}
	closearglst(structarg);
	ft_memdel((void **)&structarg);
	return (-1);
}
