# ft_memory

**Proyecto 02** · Pedir memoria, usarla y devolverla

---

## 📖 Antes de empezar, estudia

No hace falta que domines esto — hace falta que lo hayas mirado, para reconocer el terreno cuando aparezca:

- **Stack y heap** — qué es cada uno y por qué existen dos sitios distintos donde vive la memoria
- **Qué devuelve `malloc`** — qué tipo es, qué contiene la memoria que te da, y qué pasa si falla
- **Qué significa "ser dueño" de un puntero** — cuando una función devuelve memoria reservada, ¿quién la libera?
- **Qué es una fuga de memoria** y por qué el compilador no puede detectarla
- **`sizeof`** — para qué sirve al reservar memoria

Búscalo tú. Media hora de lectura basta.

---

## Objetivo

Hasta ahora toda la memoria te la daban hecha: los literales los pone el compilador, y los buffers los declaraba `main`. Solo escribías dentro de espacio ajeno.

Aquí la pides tú, decides cuánta, y **te encargas de devolverla**.

---

## Por qué esto ahora

Piensa en el juego que vas a construir. Cuando arranca un nivel, ¿cuántos enemigos hay?

No lo sabes al compilar. Depende del nivel, y los niveles se cargan de fichero.

```c
struct Enemigo enemigos[???];    /* ¿cuántos? */
```

**Esa es la limitación que resuelve el heap.** Memoria de tamaño decidido en tiempo de ejecución, que vive tanto como tú quieras.

Y viene con una responsabilidad nueva: si no la devuelves, se acumula. Un bucle de juego a 60 fps que pierde 100 bytes por frame se come 21 MB por hora.

---

## Funciones permitidas

```
write, malloc, free
```

---

## Parte obligatoria

### 1. `ft_memset`

```c
void	*ft_memset(void *b, int c, size_t n);
```

Escribe el byte `c` en los primeros `n` bytes de `b`. Devuelve `b`.

⚠️ El parámetro es `void *`: no sabes qué tipo hay dentro. Piensa a qué tipo tienes que convertirlo para poder escribir byte a byte, y por qué precisamente ese.

### 2. `ft_bzero`

```c
void	ft_bzero(void *s, size_t n);
```

Pone a cero los primeros `n` bytes. Debe apoyarse en `ft_memset`.

### 3. `ft_memcpy`

```c
void	*ft_memcpy(void *dest, void *src, size_t n);
```

Copia `n` bytes de `src` a `dest`. Devuelve `dest`.

⚠️ No es `ft_strcpy`: aquí **no hay `'\0'` que valga**. Copias `n` bytes exactos, sean lo que sean. Sirve para cualquier tipo de dato, no solo texto.

### 4. `ft_strdup`

```c
char	*ft_strdup(char *s);
```

Devuelve una **copia de la cadena en memoria nueva**.

⚠️ Tres cosas: cuánto pides exactamente (ojo con el `'\0'`), qué haces si `malloc` falla, y **quién libera lo que devuelves**.

### 5. `ft_calloc`

```c
void	*ft_calloc(size_t n, size_t tam);
```

Reserva espacio para `n` elementos de `tam` bytes cada uno, **y lo pone todo a cero**.

⚠️ Tiene una trampa que no es evidente. `n * tam` puede **desbordarse**: si el producto no cabe en un `size_t`, da un número pequeño, reservas poco, y quien lo use escribirá fuera. Es una vulnerabilidad real y con nombre. Piensa cómo detectarlo **antes** de multiplicar.

### 6. `ft_free_tab`

```c
void	ft_free_tab(char **tab);
```

Libera un array de cadenas terminado en `NULL` — donde cada cadena fue reservada aparte, y el array también.

⚠️ El orden importa. Piensa qué pasa si liberas primero el array.

---

## Entrega

```
02-ft_memory/
├── Makefile
├── src/
│   ├── ft_memset.c
│   ├── ft_bzero.c
│   ├── ft_memcpy.c
│   ├── ft_strdup.c
│   ├── ft_calloc.c
│   └── ft_free_tab.c
└── tests/
    └── main.c
```

Compilación con `-Wall -Wextra -Werror`. Makefile con `all`, `clean`, `fclean`, `re`.

**Nuevo:** el Makefile debe tener además una regla `debug` que compile con `-g -fsanitize=address`.

---

## Herramienta nueva: AddressSanitizer

El compilador **no puede detectar** los errores de memoria: ocurren en ejecución. Para eso existen los *sanitizers*.

```bash
gcc -Wall -Wextra -g -fsanitize=address src/*.c tests/main.c -o debug
./debug
```

Lo que detecta, comprobado:

```
SUMMARY: AddressSanitizer: 100 byte(s) leaked in 1 allocation(s).
ERROR: AddressSanitizer: heap-use-after-free
ERROR: AddressSanitizer: attempting double-free
```

Te da el fichero y la línea exacta. **Úsalo en cada función de este proyecto.**

> `valgrind ./programa` hace algo parecido y detecta además lecturas de memoria sin inicializar. Es más lento pero más minucioso.

---

## Normas de escritura

Las mismas. Recordatorio de lo que se te ha escapado antes:

- **Tabuladores**, no espacios
- `i = 0;` **antes** del bucle — el compilador lo detecta, compila tú primero
- Incluye la cabecera mínima que necesites, no una grande
- Máximo 25 líneas por función, solo `while`, sin globales

---

## Bonus

Solo con lo obligatorio perfecto y sin fugas.

- `ft_realloc(void *p, size_t antiguo, size_t nuevo)` — cambia el tamaño de un bloque conservando el contenido. Piensa qué hay que hacer si no cabe donde está.

---

## Cómo se evalúa

| Criterio | |
|---|---|
| Compila con `-Wall -Wextra -Werror`, sin avisos | ⬜ |
| Makefile con `all`, `clean`, `fclean`, `re`, `debug` | ⬜ |
| `ft_memset` funciona con cualquier tipo de dato | ⬜ |
| `ft_bzero` se apoya en `ft_memset` | ⬜ |
| `ft_memcpy` copia `n` bytes exactos, sin mirar `'\0'` | ⬜ |
| `ft_strdup` reserva el tamaño correcto (con el `'\0'`) | ⬜ |
| **`ft_strdup` comprueba si `malloc` falló** | ⬜ |
| `ft_calloc` deja toda la memoria a cero | ⬜ |
| **`ft_calloc` detecta el desbordamiento de `n * tam`** | ⬜ |
| `ft_free_tab` libera en el orden correcto | ⬜ |
| **CERO fugas con `-fsanitize=address`** | ⬜ |
| **CERO use-after-free y cero double free** | ⬜ |
| Normas de escritura | ⬜ |
| **Preguntas de defensa respondidas** | ⬜ |

---

## Defensa

Sin mirar el código.

1. ¿Qué diferencia hay entre la memoria de `char buf[100];` y la de `malloc(100)`? ¿Cuándo desaparece cada una?

2. `ft_strdup` devuelve memoria reservada. ¿Quién la libera y cómo lo sabe? ¿Qué pasa si nadie lo hace? ¿Y si lo hacen dos veces?

3. ¿Por qué hay que comprobar el retorno de `malloc`? ¿Qué pasa si no lo compruebas y falla?

4. En `ft_memset`, ¿por qué el parámetro es `void *` y a qué tipo lo conviertes? ¿Por qué no a `int *`?

5. ¿Cuál es el desbordamiento de `ft_calloc`? Pon un ejemplo con números concretos.

6. ¿Por qué el compilador no detecta una fuga de memoria, si detecta una variable sin inicializar?

7. En `ft_free_tab`, ¿qué pasa si liberas primero el array y luego intentas liberar las cadenas?

---

## Pistas

<details><summary>ft_memset: el tipo de la conversión</summary>

`void *` no se puede desreferenciar: el compilador no sabe cuántos bytes leer.

Necesitas un tipo que ocupe **exactamente un byte**, porque quieres escribir byte a byte sin saltarte ninguno.

Y de los dos candidatos de un byte, ¿cuál evita el problema del signo que ya viste en `ft_strcmp`?
</details>

<details><summary>ft_strdup: cuánto pedir</summary>

`ft_strlen("Karamoon")` da 8. Pero la cadena ocupa **9 bytes** en memoria.

Si pides 8 y copias el `'\0'`, escribes un byte fuera. AddressSanitizer te lo dirá.
</details>

<details><summary>ft_calloc: detectar el desbordamiento</summary>

Multiplicar y luego comprobar **no sirve**: si se desbordó, el resultado ya es un número pequeño y parece correcto.

Hay que comprobarlo **antes**, con una división: si `n` es mayor que el máximo dividido entre `tam`, el producto no va a caber.

El valor máximo de un `size_t` se obtiene con `(size_t)-1` — un `-1` convertido a sin signo da todos los bits a uno.

Y cuidado con dividir entre cero.
</details>

<details><summary>ft_free_tab: el orden</summary>

Cada cadena es un bloque. El array de punteros es otro bloque.

Si liberas el array primero, pierdes las direcciones de las cadenas: ya no puedes alcanzarlas para liberarlas. Fuga garantizada, y además estarías leyendo memoria liberada para intentarlo.
</details>

<details><summary>Makefile: la regla debug</summary>

```makefile
debug: $(SRC)
	$(CC) -Wall -Wextra -g -fsanitize=address $(SRC) -o debug
```

Sin `-Werror`, para que un aviso no te impida ejecutar el sanitizer.
</details>

---

## Cuando termines

El proyecto 03 es **`ft_canvas`**: un lienzo en memoria y **una imagen guardada en disco** que abrirás con el visor de tu ordenador.

Ahí `ft_calloc` deja de ser un ejercicio: un lienzo de 320×200 son 64.000 píxeles que hay que reservar y poner a cero. Y verás por qué una imagen es, en el fondo, un array.

**Primer resultado visual del camino.**

---

📖 **[Teoría de este proyecto](THEORY.md)** — se escribe al terminar.

[← Volver al camino](../README.md) · [Proyecto anterior](../01-ft_string/SUBJECT.md)
