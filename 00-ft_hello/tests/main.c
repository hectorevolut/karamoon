/* main.c — pruebas del proyecto 00
 *
 * Compila con:  make
 * Ejecuta con:  ./hello
 */

void	ft_putchar(char c);
void	ft_putstr(char *s);
void	ft_putnbr(int n);

int	main(void)
{
	ft_putstr("--- ft_putchar ---\n");
	ft_putchar('K');
	ft_putchar('\n');

	ft_putstr("--- ft_putstr ---\n");
	ft_putstr("Bienvenido a Karamoon\n");

	ft_putstr("--- ft_putnbr ---\n");
	ft_putnbr(0);
	ft_putchar('\n');
	ft_putnbr(42);
	ft_putchar('\n');
	ft_putnbr(-42);
	ft_putchar('\n');
	ft_putnbr(2147483647);
	ft_putchar('\n');
	ft_putnbr(-2147483648);
	ft_putchar('\n');

	return (0);
}
