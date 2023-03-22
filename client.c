/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:06:31 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/22 15:37:57 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sig;

static void	ft_resend(int pid, int signal)
{
	if (kill(pid, signal) == -1)
	{
		usleep(50);
		ft_resend(pid, signal);
	}
}

static void	ft_break(int signal)
{
	if (signal == SIGUSR1)
		g_sig = 1;
	else if (signal == SIGUSR2)
	{
		ft_printf("Message received :)");
		g_sig = 1;
	}
}

static void	ft_send(int pid, char c)
{
	int	i;

	i = 10;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_resend(pid, SIGUSR1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_resend(pid, SIGUSR2);
		}
		i--;
		while (g_sig != 1)
			signal(SIGUSR1, ft_break);
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
		while (g_sig == 0)
			signal(SIGUSR2, ft_break);
	}
	return (0);
}
