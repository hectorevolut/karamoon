/* ft_memset.c
 *
 * Escribe el byte c en los primeros n bytes de b. Devuelve b.
 *
 * OJO: b es void *, no se puede desreferenciar directamente.
 *      Hay que convertirlo a un tipo de UN byte.
 */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t n)
{
	(void)c;
	(void)n;
	return (b);
}
