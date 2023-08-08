/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03.print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongolee <jongolee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 20:50:17 by jongolee          #+#    #+#             */
/*   Updated: 2023/07/21 21:05:39 by jongolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	print_died(unsigned long sec, unsigned long usec, int id)
{
	printf("%lu.%03lums %d died\n", sec, usec/1000, id);
}
