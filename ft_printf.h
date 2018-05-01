/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achernys <achernys@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:12:38 by achernys          #+#    #+#             */
/*   Updated: 2018/05/01 14:59:27 by achernys         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <math.h>
# define ABS(x) x < 0 ? -x : x

typedef struct 		s_argptrsave
{
	va_list	argptrstart;
	va_list argptrcurr;
	va_list argstar;
	int		len;
}					t_argptrsave;

typedef struct		s_data
{
	unsigned char	zero;
	unsigned char	space;
	unsigned char	minus;
	unsigned char	plus;
	unsigned char	hashtag;
	unsigned char	h;
	unsigned char	z;
	unsigned char	l;
	unsigned char	L;
	unsigned char	j;
	int				wstar;
	int				pstar;
	int				dollar;
	size_t 			width;
	int 			precision;
}					t_data;

int 				ft_printf(const char *format, ...);

void				processingflags(const char *format, t_argptrsave *structarg,
							size_t *addi, t_data *data);
char 				procdollar(const char *format, size_t savei, size_t *addi);
void				setarg(t_argptrsave *structarg, int num);
void				procstar(t_data *data, t_argptrsave *sarg);
t_data				*getdatastruct(void);
void				procn(int len, t_argptrsave *structarg, t_data *data);

char				*getflagsstr(void);
char				*gettypesstr(void);
char				*getexpansionstr(void);
char				*getexpflagstr(void);
char				*getallparamstr(void);

char				*getargstr(char identifier, t_data *data,
							   t_argptrsave *structarg);
int					getnum(const char *format, t_argptrsave *structarg,
							 size_t *addi, t_data *data);

int					get_int(va_list *argptr);
long 				get_long(va_list *argptr);
short				get_short(va_list *argptr);
int 				*get_intptr(va_list *argptr);
char				get_char(va_list *argptr);
wchar_t				get_wchar(va_list *argptr);
char				*get_str(va_list *argptr);
wchar_t				*get_wstr(va_list *argptr);
size_t				get_size(va_list *argptr);
ssize_t				get_ssize(va_list *argptr);
intmax_t			get_intmax(va_list *argptr);
uintmax_t			get_uintmax(va_list *argptr);
unsigned int		get_unint(va_list *argptr);
unsigned long		get_unlong(va_list *argptr);
unsigned long long	get_ullong(va_list *argptr);
unsigned short		get_unshort(va_list *argptr);
unsigned char		get_unchar(va_list *argptr);
unsigned long long	get_uvalue(t_data *data, t_argptrsave *structarg,
								 char identifier);

char				*numnotationnot(char *formatstr, t_data *data, char identifier);
char				*addspace(char *src, t_data *data, char identifier);

char				*procdig(char identifier, t_data *data,
							 t_argptrsave *structarg);
char				*proctext(char identifier, t_data *data,
							  t_argptrsave *structarg);
char				*procint(t_data *data, t_argptrsave *structarg,
							 char identifier);
char				*procnotation(t_data *data, t_argptrsave *structarg,
								  char identifier);
char				*ft_bitoa(__int128 n);
char				*ft_itoabase(unsigned __int128 number, int base, char sym);
int					isnonzerodigit(int c);

char				*procs(int identifier, t_data *data, t_argptrsave *structarg);
char				*procc(int identifier, t_data *data, t_argptrsave *structarg);
char				*procwc(wchar_t wchar);
char				*procwstr(wchar_t *wstr);
int					printnullstr(t_data *data, char identifier);

char				*isneedtoadd(char *argstr, t_data *data, char identifier);

double				get_double(va_list *argptr);
long double			get_ldouble(va_list *argptr);
char				*procf(char identifier, t_data *data, t_argptrsave *structarg);
char				*procdouble(char identifier, t_data *data, t_argptrsave *structarg);

void				closearglst(t_argptrsave *structarg);
#endif
