/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:06:31 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/23 16:17:02 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sig;

static void	ft_break(int signal)
{
	if (signal == SIGUSR1)
		g_sig = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("Message received :)\n");
		exit(EXIT_SUCCESS);
	}
}

static void	ft_send(int pid, char c)
{
	int	i;

	i = 8;
	while (i >= 0)
	{
		if (c & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		while (g_sig != 1)
		{
			signal(SIGUSR1, ft_break);
			signal(SIGUSR2, ft_break);
		}
		usleep(5);
		g_sig = 0;
	}
}

static int	ft_checkerror(char *argv)
{
	if (!ft_atoi(argv) || ft_atoi(argv) < 0)
	{
		ft_printf("Wrong PID, try writing ./client <pid> <messsage>");
		return (0);
	}
	if (kill(ft_atoi(argv), 0) < 0)
	{
		ft_printf("ERROR: Can't send to PID\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int	i;

	g_sig = 0;
	i = 0;
	if (argc == 3)
	{
		if (!ft_checkerror(argv[1]))
			return (0);
		while (argv[2][i])
		{
			ft_send(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
		ft_send(ft_atoi(argv[1]), '\0');
	}
	return (0);
}
