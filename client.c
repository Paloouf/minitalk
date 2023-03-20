/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:06:31 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/20 15:40:34 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			kill(pid, SIGUSR1);
			//ft_printf("1");
		}
		else
		{
			kill(pid, SIGUSR2);
			//ft_printf("0");
		}
		i--;
	usleep(10);
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc == 3)
	{
		while (argv[2][i])
		{
			ft_send(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
	}
	return (0);
}