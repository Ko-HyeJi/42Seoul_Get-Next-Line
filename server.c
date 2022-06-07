/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyko <hyko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:06:23 by hyko              #+#    #+#             */
/*   Updated: 2022/06/07 19:32:52 by hyko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb >= 0)
	{
		if (nb < 10)
			ft_putchar(nb + '0');
		else
		{
			ft_putnbr(nb / 10);
			ft_putnbr(nb % 10);
		}
	}
	else if (nb == -2147483648)
		write(1, "-2147483648", 11);
	else
	{
		write(1, "-", 1);
		if (-10 < nb)
			ft_putchar(nb * -1 + '0');
		else
		{
			ft_putnbr(nb * -1 / 10);
			ft_putnbr(nb * -1 % 10);
		}
	}
}

void	ft_signal_handler(int sig)
{
	static char	c;
	static int	i;

	if (i < 8)
	{
		c = c << 1;
		if (sig == SIGUSR2)
			c += 1;
		i++;
	}
	if (i >= 8)
	{
		write(1, &c, 1);
		c = 0;
		i = 0;
	}
}

int	main(void)
{
	write(1, "PID : ", 6);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, &ft_signal_handler);
	signal(SIGUSR2, &ft_signal_handler);
	while (1)
		pause();
	return (0);
}
