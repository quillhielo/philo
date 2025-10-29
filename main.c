/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarbajo <acarbajo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 20:04:14 by acarbajo          #+#    #+#             */
/*   Updated: 2025/10/29 20:36:40 by acarbajo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == NULL)
		return (0);
	while(str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int	atoi_result_checker(long r, long s, t_data *data, char **argv)
{
	if (r * s < INT_MIN || r * s > INT_MAX)
	{
		free_matrix();
		error(fw);
	}
	return ((int)(r * s));
}

int	ft_atoi_limits(const char *nptr, t_framework *fw, char **split)
{
	size_t		i;
	long		s;
	long		r;
	long		d;

	i = 0;
	s = 1;
	r = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = s * -1;
		i++;
	}
	if (!(nptr[i] >= 48 && nptr[i] <= 57))
		return (0);
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		d = nptr[i] - 48;
		r = r * 10 + d;
		i++;
	}
	return (atoi_result_checker(r, s, fw, split));
}
int	parser_argv(char **argv)
{
	int	i;
	
	i = 0;
	while(argv[i])
	{
		is_digit(argv[i]);
		
		
		
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	
	if (argc != 5 || argc != 6)
		return (0);
	
	data = malloc(sizeof(t_data *));
	parser_argv(argv);
}