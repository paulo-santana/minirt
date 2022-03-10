/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_comparison.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:01:49 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/10 17:03:04 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#define EPSILON 0.00001

int	fequals(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}
