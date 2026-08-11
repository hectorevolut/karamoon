/* main.c - pruebas del proyecto 01
 *
 *   make && ./string
 *
 * Compara tu resultado con el ESPERADO de cada linea.
 */

#include <unistd.h>

int		ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, int n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

/* helpers de las pruebas (del proyecto 00) */
static void	pc(char c)
{
	write(1, &c, 1);
}

static void	ps(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		pc(s[i]);
		i++;
	}
}

static void	pn(int n)
{
	long	num;

	num = n;
	if (num < 0)
	{
		pc('-');
		num = -num;
	}
	if (num >= 10)
		pn(num / 10);
	pc((num % 10) + '0');
}

int	main(void)
{
	char	buf[32];
	char	*p;
	int		i;

	ps("=== ft_strlen ===\n");
	ps("\"Karamoon\" -> ");	pn(ft_strlen("Karamoon"));	ps("   esperado: 8\n");
	ps("\"\"         -> ");	pn(ft_strlen(""));			ps("   esperado: 0\n");
	ps("\"a\"        -> ");	pn(ft_strlen("a"));			ps("   esperado: 1\n");

	ps("\n=== ft_putstr_fd ===\n");
	ft_putstr_fd("a pantalla (fd 1)\n", 1);
	ft_putstr_fd("a error    (fd 2)\n", 2);

	ps("\n=== ft_strcpy ===\n");
	ft_strcpy(buf, "Shadow");
	ps("copia -> \"");	ps(buf);	ps("\"   esperado: \"Shadow\"\n");

	ps("\n=== ft_strncpy ===\n");
	i = 0;
	while (i < 10)
	{
		buf[i] = 'X';
		i++;
	}
	ft_strncpy(buf, "abc", 6);
	ps("relleno: ");
	i = 0;
	while (i < 6)
	{
		if (buf[i] == '\0')
			ps("_");
		else
			pc(buf[i]);
		i++;
	}
	ps("   esperado: abc___  (_ = '\\0')\n");

	ps("\n=== ft_strcmp (solo importa el SIGNO) ===\n");
	ps("(\"abc\",\"abc\") -> ");	pn(ft_strcmp("abc", "abc"));	ps("   esperado: 0\n");
	ps("(\"abc\",\"abd\") -> ");	pn(ft_strcmp("abc", "abd"));	ps("   esperado: negativo\n");
	ps("(\"abc\",\"ab\")  -> ");	pn(ft_strcmp("abc", "ab"));		ps("   esperado: positivo\n");

	ps("\n=== ft_strchr ===\n");
	p = ft_strchr("Karamoon", 'm');
	ps("buscar 'm' -> \"");
	if (p)
		ps(p);
	ps("\"   esperado: \"moon\"\n");
	p = ft_strchr("Karamoon", 'z');
	ps("buscar 'z' -> ");
	if (p)
		ps("encontrado");
	else
		ps("NULL");
	ps("   esperado: NULL\n");
	p = ft_strchr("Karamoon", '\0');
	ps("buscar '\\0' -> ");
	if (p)
		ps("encontrado");
	else
		ps("NULL");
	ps("   esperado: encontrado\n");

	return (0);
}
