#include "ft_printf.h"

size_t			get_size(va_list *argptr)
{
	return (va_arg(*argptr, size_t));
}

ssize_t 		get_ssize(va_list *argptr)
{
	return (va_arg(*argptr, ssize_t));
}

intmax_t		get_intmax(va_list *argptr)
{
	return (va_arg(*argptr, intmax_t));
}

uintmax_t 		get_uintmax(va_list *argptr)
{
	return (va_arg(*argptr, uintmax_t));
}
