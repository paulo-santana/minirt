/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_comparison.c                                 :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio->                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:01:49 by psergio-          #+#    #+#             */
/*   Updated: 2022/03/11 10:21:31 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

int	dequals(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}
