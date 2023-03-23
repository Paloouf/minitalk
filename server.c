/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 08:55:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/23 16:27:37 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_msg(int res, int i, siginfo_t *lol)
{
	if (res == 0 && i == 9)
	{
		usleep(5);
		kill(lol->si_pid, SIGUSR2);
	}
}

static void	ft_write(int signal, siginfo_t *lol, void *nimp)
{
	static int	bits[9];
	static int	i = 9;
	int			res;

	(void)nimp;
	if (signal == SIGUSR1)
		bits[i--] = 1;
	else if (signal == SIGUSR2)
		bits[i--] = 0;
	res = 0;
	if (i == 0)
	{
		while (i < 8)
		{
			res += bits[8 - i] * ft_power(2, 7 - i);
			i++;
		}
		i = 9;
		ft_printf("%c", (char)res);
		ft_bzero(bits, 9);
	}
	usleep(5);
	ft_msg(res, i, lol);
	kill(lol->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction		siga;

	siga.sa_sigaction = ft_write;
	siga.sa_flags = SA_SIGINFO;
	sigemptyset(&siga.sa_mask);
	sigaction(SIGUSR1, &siga, 0);
	sigaction(SIGUSR2, &siga, 0);
	ft_printf("%d\n", getpid());
	while (1)
		sleep(1);
}
