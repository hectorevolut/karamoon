/* main.c — pruebas del proyecto 02
 *
 *   make        && ./memory     <- comprobar resultados
 *   make debug  && ./debug      <- comprobar fugas y errores de memoria
 */

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>

size_t	ft_strlen(char *s);
void	*ft_memset(void *b, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
char	*ft_strdup(char *s);
void	*ft_calloc(size_t n, size_t tam);
void	ft_free_tab(char **tab);

/* helpers de las pruebas */
static void	ps(char *s)
{
	write(1, s, ft_strlen(s));
}

static void	pn(long n)
{
	char	c;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		pn(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

static void	bytes(unsigned char *p, int n)
{
	int		i;
	char	c;

	i = 0;
	while (i < n)
	{
		c = p[i] ? (char)p[i] : '_';
		write(1, &c, 1);
		i++;
	}
}

int	main(void)
{
	char			buf[16];
	int				nums[4];
	char			*copia;
	int				*cero;
	char			**tab;
	unsigned char	*raw;

	ps("=== ft_memset ===\n");
	ft_memset(buf, 'A', 8);
	ps("  8 bytes con 'A': ");	bytes((unsigned char *)buf, 8);
	ps("   esperado: AAAAAAAA\n");

	ps("\n=== ft_bzero ===\n");
	ft_memset(buf, 'Z', 16);
	ft_bzero(buf, 8);
	ps("  8 a cero, 8 con Z: ");	bytes((unsigned char *)buf, 16);
	ps("   esperado: ________ZZZZZZZZ\n");

	ps("\n=== ft_memcpy (con enteros, no texto) ===\n");
	nums[0] = 100;
	nums[1] = 200;
	nums[2] = 0;
	nums[3] = 0;
	ft_memcpy(&nums[2], &nums[0], 2 * sizeof(int));
	ps("  copiados: ");
	pn(nums[2]);	ps(" ");	pn(nums[3]);
	ps("   esperado: 100 200\n");

	ps("\n=== ft_strdup ===\n");
	copia = ft_strdup("Karamoon");
	if (copia)
	{
		ps("  copia: \"");	ps(copia);	ps("\"   esperado: \"Karamoon\"\n");
		raw = (unsigned char *)copia;
		ps("  byte 8 (debe ser '\\0'): ");
		if (raw[8] == 0)
			ps("OK\n");
		else
			ps("** FALTA EL TERMINADOR **\n");
		free(copia);
	}
	else
		ps("  ** devolvio NULL **\n");

	ps("\n=== ft_calloc ===\n");
	cero = ft_calloc(5, sizeof(int));
	if (cero)
	{
		ps("  5 enteros: ");
		pn(cero[0]); ps(" "); pn(cero[1]); ps(" "); pn(cero[2]);
		ps(" "); pn(cero[3]); ps(" "); pn(cero[4]);
		ps("   esperado: 0 0 0 0 0\n");
		free(cero);
	}
	else
		ps("  ** devolvio NULL **\n");

	ps("  desbordamiento: ft_calloc((size_t)-1, 2) -> ");
	if (ft_calloc((size_t)-1, 2) == NULL)
		ps("NULL   OK\n");
	else
		ps("** NO detectado **\n");

	ps("\n=== ft_free_tab ===\n");
	tab = malloc(4 * sizeof(char *));
	if (tab)
	{
		tab[0] = ft_strdup("uno");
		tab[1] = ft_strdup("dos");
		tab[2] = ft_strdup("tres");
		tab[3] = NULL;
		ps("  liberando 3 cadenas + el array... ");
		ft_free_tab(tab);
		ps("hecho\n");
		ps("  (comprueba con ./debug que no quedan fugas)\n");
	}

	ps("\n--- ejecuta ./debug para verificar la memoria ---\n");
	return (0);
}
