/* ft_calloc.c
 *
 * Reserva n elementos de tam bytes cada uno, TODO A CERO.
 *
 * OJO: n * tam puede desbordarse. Si el producto no cabe en
 *      un size_t, reservarias menos de lo pedido.
 *      Detectalo ANTES de multiplicar.
 */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t n);

void	*ft_calloc(size_t n, size_t tam)
{
	(void)n;
	(void)tam;
	return (NULL);
}
