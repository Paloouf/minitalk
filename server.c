/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 08:55:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/20 15:55:17 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_write(int signal)
{
	static int bits[8];
	static int	i = 8;
	int	res;

	if (signal == SIGUSR1)
	{
		bits[i] = 1;
	}
	else if (signal == SIGUSR2)
	{
		bits[i] = 0;
	}
	i--;
	res = 0;
	if (i == 0)
	{
		while (i < 7)
		{
			res += bits[7-i] * ft_power(2, 6-i);
			i++;
		}
		i = 8;
		ft_printf("%c", (char)res);
		ft_bzero(bits, 8);	
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