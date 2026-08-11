/* ft_memcpy.c
 *
 * Copia n bytes de src a dest. Devuelve dest.
 *
 * NO es ft_strcpy: aqui no hay '\0' que valga.
 * Copia n bytes exactos, sean lo que sean.
 */

#include <stddef.h>

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char   *ptr1;
    unsigned char   *ptr2;
    size_t          i;

    ptr1 = src;
    ptr2 = dest;
    i = 0;
    while (i < n)
    {
        ptr2[i] = ptr1[i];
        i++;
    }
	return (dest);
}
