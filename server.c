/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 08:55:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/21 09:19:29 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_write(int signal)
{
	static int	bits[11];
	static int	i = 11;
	int			res;

	if (signal == SIGUSR1)
		bits[i] = 1;
	else if (signal == SIGUSR2)
		bits[i] = 0;
	i--;
	res = 0;
	if (i == 0)
	{
		while (i < 10)
		{
			res += bits[10 - i] * ft_power(2, 9 - i);
			i++;
		}
		i = 11;
		ft_printf("%c", (char)res);
		ft_bzero(bits, 11);
	}
}

int	main(void)
{
	ft_printf("%d", getpid());
	while (1)
	{
		signal(SIGUSR1, ft_write);
		signal(SIGUSR2, ft_write);
	}
}
