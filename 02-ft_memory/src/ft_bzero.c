/* ft_bzero.c
 *
 * Pone a cero los primeros n bytes de s.
 * Debe apoyarse en ft_memset.
 */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t n);

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
