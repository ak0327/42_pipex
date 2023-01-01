/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takira <takira@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:10:47 by takira            #+#    #+#             */
/*   Updated: 2022/12/16 12:10:48 by takira           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ispunct(int c)
{
	return (('\041' <= c && c <= '\057') \
	|| ('\072' <= c && c <= '\077') \
	|| (c == '\100') \
	|| ('\133' <= c && c <= '\140') \
	|| ('\173' <= c && c <= '\176'));
}

/*
DESCRIPTION
The ispunct() function tests for any printing character,
 except for space (‘ ’) or a character for which isalnum(3) is true.
 The value of the argument must be representable
 as an unsigned char or the value of EOF.
 In the ASCII character set, this includes
 the following characters (preceded by their numeric values, in octal):

     041``!'' 042``"'' 043``#'' 044``$'' 045``%''
     046``&'' 047``''' 050``('' 051``)'' 052``*''
     053``+'' 054``,'' 055``-'' 056``.'' 057``/''
     072``:'' 073``;'' 074``<'' 075``='' 076``>''
     077``?'' 100``@'' 133``['' 134``\'' 135``]''
     136``^'' 137``_'' 140```'' 173``{'' 174``|''
     175``}'' 176``~''
 */