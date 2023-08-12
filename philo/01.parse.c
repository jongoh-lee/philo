#include "./main.h"

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_input_valid(char *str, int i, int sign)
{
	unsigned long long	result;

	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			on_error(INPUT);
	}
	if (str[i] == 0)
		on_error(INPUT);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
		if ((sign == -1 && result > 2147483648) || \
		(sign == 1 && result > 2147483647))
			on_error(INPUT);
	}
	while (is_space(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i++] - '0';
	}
	return (result * sign);
}

int	check_arg(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_input_valid(av[i], 0, 1))
			return (0);
		i++;
	}
	return (1);
}
