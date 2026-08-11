/* ft_free_tab.c
 *
 * Libera un array de cadenas terminado en NULL, donde cada
 * cadena fue reservada aparte y el array tambien.
 *
 * OJO: el orden importa.
 */

#include <stdlib.h>
#include <stddef.h>

void ft_free_tab(char **tab)
{
    size_t i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}
