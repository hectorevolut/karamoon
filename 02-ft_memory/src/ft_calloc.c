/* ft_calloc.c
 *
 * Reserva n elementos de tam bytes cada uno, TODO A CERO.
 *
 * OJO: n * tam puede desbordarse. Si el producto no cabe en
 *      un size_t, reservarias menos de lo pedido.
 *      Detectalo ANTES de multiplicar.
 */

#include <stdlib.h>
#include <stdint.h>

void *ft_memset(void *b, int c, size_t n);

void *ft_calloc(size_t n, size_t tam)
{
    void *ptr;

    if (tam != 0 && n > SIZE_MAX / tam)
        return (NULL);
    ptr = malloc(n * tam);
    if (!ptr)
        return (NULL);
    ft_memset(ptr, 0, n * tam);
    return (ptr);
}
