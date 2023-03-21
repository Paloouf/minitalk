/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltressen <ltressen@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 08:55:56 by ltressen          #+#    #+#             */
/*   Updated: 2023/03/21 15:38:52 by ltressen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_msg(int res, int i, siginfo_t *lol)
{
	if (res == 0 && i == 11)
	{
		usleep(500);
		kill(lol->si_pid, SIGUSR2);
	}
}

void	ft_write(int signal, siginfo_t *lol, void *nimp)
{
	static int	bits[11];
	static int	i = 11;
	int			res;

	(void)nimp;
	if (signal == SIGUSR1)
		bits[i--] = 1;
	else if (signal == SIGUSR2)
		bits[i--] = 0;
	res = 0;
	kill(lol->si_pid, SIGUSR1);
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
	ft_msg(res, i, lol);
}

int	main(void)
{
	struct sigaction		siga;

	siga.sa_sigaction = ft_write;
	siga.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sigemptyset(&siga.sa_mask);
	ft_printf("%d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &siga, 0);
		sigaction(SIGUSR2, &siga, 0);
	}
}
