/* ft_strdup.c
 *
 * Devuelve una copia de la cadena en memoria NUEVA.
 *
 * Tres cosas que decidir:
 *   - cuanto pedir exactamente (ojo con el '\0')
 *   - que hacer si malloc falla
 *   - quien libera lo que devuelves
 */

#include <stdlib.h>

size_t	ft_strlen(char *s);

char	*ft_strdup(char *s)
{
	(void)s;
	return (NULL);
}
