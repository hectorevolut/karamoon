/* ft_putstr_fd.c
 *
 * Escribe la cadena en el descriptor fd usando UNA SOLA llamada a write.
 *   fd 1 = pantalla, fd 2 = salida de error
 */

#include <unistd.h>

int	ft_strlen(char *s);

void	ft_putstr_fd(char *s, int fd)
{
	(void)s;
	(void)fd;
}
