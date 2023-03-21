/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:06:31 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/21 15:25:33 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sig;

void	ft_break(int signal)
{
	if (signal == SIGUSR1)
		g_sig = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("Message recu");
		g_sig = 1;
	}
}

void	ft_send(int pid, char c)
{
	int	i;

	i = 10;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (g_sig != 1)
			signal(SIGUSR1, ft_break);
		g_sig = 0;
	}
}

int	main(int argc, char **argv)
{
	int	i;

	g_sig = 0;
	i = 0;
	if (argc == 3)
	{
		while (argv[2][i])
		{
			ft_send(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
		ft_send(ft_atoi(argv[1]), '\0');
		while (g_sig == 0)
		{
			signal(SIGUSR2, ft_break);
		}	
	}
	return (0);
}
