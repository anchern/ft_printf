/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getparam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:32:39 by achernys          #+#    #+#             */
/*   Updated: 2018/03/24 21:55:35 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 0-1		int
** 2-3		long int
** 4		int *
** 5		void *
** 6-9		unsigned int
** 10-11	unsigned long int
** 12		char
** 13		wchar_t
** 14		char *
** 15		wchar_t *
** 16-23	double
** extension
*/

char	*getflagsstr(void)
{
	char	*types_str;

	types_str = (char *)ft_memalloc(sizeof(*types_str) * 7);
	return (ft_strcpy(types_str, "# +-.*"));
}

char	*getexpansionstr(void)
{
	char	*types_str;

	types_str = (char *)ft_memalloc(sizeof(*types_str) * 6);
	return (ft_strcpy(types_str, "lLhzj"));
}

char	*gettypesstr(void)
{
	char	*types_str;

	types_str = (char *)ft_memalloc(sizeof(*types_str) * 28);
	return (ft_strcpy(types_str, "idDnpuoxXUOcCsSfegaFEGA%br"));
}

char	*getexpflagstr(void)
{
	char	**param;
	int		i;
	int		outp;
	char	*outstr;

	outp = 2;
	param = (char **)ft_memalloc(sizeof(param) * 4);
	param[0] = getflagsstr();
	param[1] = getexpansionstr();
	param[2] = ft_strjoin(param[0], param[1]);
	param[3] = 0;
	outstr = (char *)ft_memalloc(sizeof(outstr) * ft_strlen(param[outp] + 1));
	ft_strcpy(outstr, param[outp]);
	i = 0;
	while (param[i] != 0)
	{
		ft_memdel((void **)&param[i]);
		i++;
	}
	ft_memdel((void **)&param);
	return (outstr);
}

char	*getallparamstr(void)
{
	char	**param;
	int		i;
	char	*outstr;
	int		outp;

	outp = 4;
	param = (char **)ft_memalloc(sizeof(param) * 6);
	param[0] = getflagsstr();
	param[1] = getexpansionstr();
	param[2] = gettypesstr();
	param[3] = ft_strjoin(param[0], param[1]);
	param[4] = ft_strjoin(param[3], param[2]);
	param[5] = 0;
	outstr = (char *)ft_memalloc(sizeof(outstr) * ft_strlen(param[outp] + 1));
	ft_strcpy(outstr, param[outp]);
	i = 0;
	while (param[i] != 0)
	{
		ft_memdel((void **)&param[i]);
		i++;
	}
	ft_memdel((void **)&param);
	return (outstr);
}
