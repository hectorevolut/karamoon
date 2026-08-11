#include <limits.h>

void	ft_putchar(char c);
void	ft_putstr(char *s);

void	ft_putnbr(int n)
{
	char	number;

	if (n == INT_MIN)
		ft_putstr("-2147483648");
	else
	{
		if (n < 0)
		{
			ft_putchar('-');
			n *= -1;
		}
		if (n >= 10)
			ft_putnbr(n / 10);
		number = n % 10 + '0';
		ft_putchar(number);
	}
}
