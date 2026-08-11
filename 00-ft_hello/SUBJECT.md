# ft_hello

**Proyecto 00** · Escribir en pantalla sin `printf`

---

## Objetivo

Montar el entorno, entender qué hace el compilador, y escribir tus tres primeras funciones **sin usar la librería estándar**.

Al terminar tendrás funciones que usarás en los diez proyectos siguientes.

---

## Por qué así

`printf` es una función enorme: interpreta formatos, gestiona un buffer, convierte números. Empezar por ahí es empezar por el tejado.

Debajo de `printf` hay una sola cosa: **`write`**, que le pide al sistema operativo que escriba unos bytes. Eso es todo. Si construyes tus funciones sobre `write`, no queda nada mágico entre tu código y la pantalla.

---

## Funciones permitidas

```
write
```

**Solo esa.** Nada de `printf`, `puts`, `strlen`, `malloc`. Si necesitas algo, lo escribes.

---

## Parte obligatoria

### 1. `ft_putchar`

```c
void	ft_putchar(char c);
```

Escribe **un carácter** en la salida estándar.

### 2. `ft_putstr`

```c
void	ft_putstr(char *s);
```

Escribe una **cadena** en la salida estándar. Debe usar `ft_putchar`.

### 3. `ft_putnbr`

```c
void	ft_putnbr(int n);
```

Escribe un **número entero** en la salida estándar. Debe funcionar con negativos.

⚠️ Tiene una trampa. Pruébalo con `-2147483648` (el `INT_MIN` de `<limits.h>`) antes de darlo por bueno.

---

## Entrega

```
00-ft_hello/
├── Makefile
├── src/
│   ├── ft_putchar.c
│   ├── ft_putstr.c
│   └── ft_putnbr.c
└── tests/
    └── main.c
```

**El Makefile debe tener las reglas:** `all`, `clean`, `fclean`, `re`.

Compilación obligatoria con `-Wall -Wextra -Werror`.

---

## Normas de escritura

Inspiradas en la Norminette de 42. No es burocracia: es que el código se lea igual siempre.

- **Una función hace una cosa.** Máximo 25 líneas.
- **Tabuladores** para indentar, no espacios.
- **Llaves en su propia línea.**
- **Declaraciones al principio** de la función, separadas del código por una línea en blanco.
- **Nada de `for`** en este proyecto. Solo `while`. *(Motivo: `for` esconde tres cosas en una línea. Con `while` se ven las tres por separado.)*
- Sin variables globales.

Ejemplo del estilo:

```c
void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
}
```

---

## Bonus

Solo si la parte obligatoria está perfecta.

- `ft_putnbr_base(int n, char *base)` — escribe el número en la base que le pases (`"0123456789ABCDEF"` para hexadecimal).

---

## Cómo se evalúa

| Criterio | |
|---|---|
| Compila con `-Wall -Wextra -Werror`, sin avisos | ⬜ |
| El Makefile tiene `all`, `clean`, `fclean`, `re` | ⬜ |
| `ft_putchar` escribe un carácter | ⬜ |
| `ft_putstr` escribe una cadena y usa `ft_putchar` | ⬜ |
| `ft_putnbr` funciona con 0, positivos y negativos | ⬜ |
| **`ft_putnbr` funciona con `-2147483648`** | ⬜ |
| No se usa ninguna función prohibida | ⬜ |
| El código cumple las normas de escritura | ⬜ |
| **Se responden las preguntas de defensa** | ⬜ |

---

## Defensa

**Sin mirar el código.** Si alguna no sale, el proyecto no está terminado.

1. ¿Qué hace exactamente `write(1, &c, 1)`? ¿Qué es el `1` del principio y por qué el `&`?

2. ¿Por qué `ft_putstr` puede saber dónde acaba la cadena si nadie le pasa su longitud?

3. ¿Qué hace `-Werror` que no haga `-Wall`? ¿Por qué usarla?

4. Ejecutas `make` dos veces seguidas. La segunda no compila nada. ¿Por qué?

5. ¿Cuál es la trampa de `ft_putnbr` con `-2147483648`? ¿Cómo la resolviste?

6. En `ft_putnbr`, ¿por qué `+ '0'` convierte un dígito en su carácter?

---

## Pistas

<details><summary>No sé por dónde empezar con write</summary>

`write` necesita tres cosas: **dónde** escribir, **desde qué dirección** de memoria, y **cuántos bytes**.

```c
write(1, &c, 1);
```

El `1` es la salida estándar (la pantalla). El `&c` es la dirección donde está el carácter. El último `1` es "escribe un byte".

Necesitas `#include <unistd.h>`.
</details>

<details><summary>¿Cómo sé dónde acaba una cadena?</summary>

En C, una cadena termina con un carácter especial: `'\0'`. No es la letra cero, es el valor 0.

Recorres el array hasta encontrarlo.
</details>

<details><summary>ft_putnbr: cómo separar los dígitos</summary>

Para 253:
- `253 % 10` da **3** (el último dígito)
- `253 / 10` da **25** (lo que queda)

Repites hasta que no quede nada. Pero salen **al revés**: primero el 3, luego el 5, luego el 2.

Piensa en cómo darles la vuelta. Una función puede llamarse a sí misma.
</details>

<details><summary>La trampa de INT_MIN</summary>

`int` va de −2.147.483.648 a **2.147.483.647**.

Fíjate: el negativo llega más lejos que el positivo. Así que si intentas convertir `-2147483648` en positivo para trabajar con él... ese número **no existe** como `int`.

Necesitas un tipo más grande, o tratar ese caso aparte.
</details>

<details><summary>Estructura del Makefile</summary>

```makefile
NAME    = hello
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
SRC     = src/ft_putchar.c src/ft_putstr.c src/ft_putnbr.c tests/main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

La línea del comando lleva **tabulador**, no espacios.
</details>

---

## Cuando termines

El siguiente proyecto es **`ft_string`**: recorrer, copiar y comparar cadenas a mano. Ahí `ft_putstr` te resultará familiar — pero necesitarás saber **cuánto** mide una cadena, no solo dónde acaba.

---

📖 **[Teoría de este proyecto](THEORY.md)** — lo que apareció durante el desarrollo, ordenado.

[← Volver al camino](../README.md)
