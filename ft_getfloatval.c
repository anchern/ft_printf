/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfloatval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 14:53:57 by achernys          #+#    #+#             */
/*   Updated: 2018/05/01 14:53:57 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double		get_double(va_list *argptr)
{
	return (va_arg(*argptr, double));
}

long double	get_ldouble(va_list *argptr)
{
	return (va_arg(*argptr, long double));
}
