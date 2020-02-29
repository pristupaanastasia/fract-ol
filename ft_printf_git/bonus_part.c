/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smanhack <smanhack@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 18:59:31 by smanhack          #+#    #+#             */
/*   Updated: 2019/08/02 19:03:38 by smanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					proverka(char *posle, char *zeloe)
{
	if (posle[0] >= '5')
	{
		if (zeloe[ft_strlen(zeloe) - 1] == '2'
			|| zeloe[ft_strlen(zeloe) - 1] == '4'
			|| zeloe[ft_strlen(zeloe) - 1] == '6'
			|| zeloe[ft_strlen(zeloe) - 1] == '8')
			return (1);
	}
	return (0);
}
