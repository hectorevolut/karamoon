# Teoría — ft_string

Lo que apareció durante el proyecto 01. Todo anclado a las seis funciones que escribiste.

---

## 1. Qué es una cadena en C

### No existe el tipo "cadena"

C no tiene un tipo para texto. Una cadena es **un array de `char` que termina en un byte con valor 0**, escrito `'\0'`.

Eso es todo. No hay longitud guardada, no hay cabecera, no hay objeto. Solo bytes seguidos y una marca al final.

### El coste oculto del literal

```
"Karamoon"  →  8 caracteres visibles, 9 bytes en memoria
```

El compilador añade el `'\0'` automáticamente. Por eso `sizeof("Karamoon")` da 9 y `ft_strlen("Karamoon")` da 8: **miden cosas distintas**.

Cuando construyas cadenas a mano tendrás que reservar ese byte extra y ponerlo tú.

### La consecuencia: todo se recorre

Como la longitud no está guardada en ningún sitio, **cualquier operación tiene que recorrer la cadena entera**.

`ft_strlen("Karamoon")` mira 9 bytes para decir 8. Y si llamas a `ft_strlen` dentro de un bucle sobre la misma cadena, la estás recorriendo una vez por iteración.

Otros lenguajes guardan la longitud aparte precisamente por esto. C eligió la marca al final: menos memoria, más trabajo en cada operación.

### Y si falta el `'\0'`

Tu bucle no se detiene. Sigue leyendo memoria que no le pertenece hasta topar con un cero por casualidad, o hasta que el sistema mate el proceso.

**No hay ninguna comprobación.** Confías en que la marca esté ahí.

Esta decisión de diseño de los años 70 es el origen de una familia entera de vulnerabilidades de seguridad.

---

## 2. `size_t` y los tipos sin signo

### Qué es

`size_t` es un entero **sin signo**, garantizado lo bastante grande para representar el tamaño de cualquier objeto en memoria. En x86-64 son 8 bytes.

Es lo que devuelve `strlen`, lo que recibe `write` como tercer parámetro, y lo que pide `malloc`. **Todo lo que sea "una cantidad de bytes" usa `size_t`.**

Vive en `<stddef.h>`.

### Por qué lo cambiaste tú

Empezaste con `int ft_strlen`, y lo cambiaste a `size_t` por iniciativa propia. Era la decisión correcta:

- Una longitud **nunca puede ser negativa** — con `int` estás desperdiciando la mitad del rango
- `write(fd, s, ft_strlen(s))` espera un `size_t`. Con `int` hay una conversión implícita en cada llamada
- Con `int`, cadenas de más de 2.147.483.647 caracteres se romperían

### Dónde NO sirve

Y aquí está la lección del proyecto. En `ft_strcmp` usaste `size_t` como tipo de retorno, y el resultado fue:

```
("abc","abd")  tuyo = 18446744073709551615     real = -1
```

**Un tipo sin signo no puede expresar un negativo.** La resta daba −1, y al devolverla como `size_t` se convirtió en el número más grande de 64 bits — que es **positivo**. Toda comparación de orden quedaba invertida.

**La regla:** el tipo se elige por lo que el valor puede ser, no por costumbre.

| Valor | Tipo |
|---|---|
| Una longitud o una cantidad de bytes | `size_t` |
| Algo que puede ser negativo | `int` |

Recorrer y devolver son cosas distintas: en `ft_strcmp` el índice puede ser `size_t` y el retorno `int`.

### El peligro real de mezclar

```c
int n = -1;
write(1, s, n);      /* n se convierte a size_t */
```

Ese `-1` se convierte en 18.446.744.073.709.551.615. Le estás pidiendo al sistema que escriba 18 trillones de bytes.

Por eso `-Wextra` avisa de comparaciones entre `signed` y `unsigned`: son una fuente conocida de bugs.

---

## 3. `char` tiene signo

### El problema

En x86, `char` es **con signo** por defecto: va de −128 a 127. Pero hay 256 caracteres posibles.

Comprobado:

```
char c = 241;                    /* código de 'ñ' en Latin-1 */
c como char          = -15
c como unsigned char = 241
```

### Por qué rompía `ft_strcmp`

Al restar dos `char`, un carácter acentuado se interpreta como negativo. Comparando `"ñ"` con `"a"`:

```
sin cast:  -15 - 97  = -112   →  la ñ va ANTES que la a   ✗
con cast:  241 - 97  =  144   →  la ñ va DESPUÉS          ✓
```

Cualquier ordenación alfabética con acentos habría salido mal.

`strcmp` real convierte a `unsigned char` antes de restar. Tu versión también, y por eso coincide exactamente con la real en los nueve casos que probamos.

### Detalle

Que `char` tenga signo **no está en el estándar**: depende de la plataforma. En ARM suele ser sin signo. Por eso, cuando el signo importa, se escribe `signed char` o `unsigned char` explícitamente.

---

## 4. Punteros que apuntan a memoria ajena

### Lo que devuelve `ft_strchr`

```
t = 0x563aa4bfb008  ->  "Karamoon"
p = 0x563aa4bfb00c  ->  "moon"      (4 bytes más adelante)
```

`ft_strchr` **no crea nada**. Devuelve una dirección **dentro de la cadena que le pasaron**.

### Dos consecuencias

**1. Quien reciba ese puntero puede modificar la cadena original.**

```c
char buf[] = "Karamoon";
char *p = ft_strchr(buf, 'm');
*p = 'M';                        /* buf ahora es "KaraMoon" */
```

Eso es intencionado y útil. Pero significa que estás dando acceso de escritura a datos que no son tuyos.

**2. El puntero muere cuando muera la cadena.**

```c
char *buscar(void) {
    char local[] = "Karamoon";
    return ft_strchr(local, 'm');   /* local desaparece al volver */
}
```

El puntero devuelto apunta a memoria que ya no existe. Tu función no reserva nada, así que **no puede alargar la vida de nada**.

Este es el bug que dominará el proyecto 02, donde sí reservarás memoria y habrá que decidir quién la libera.

### `NULL` frente a `0`

Son equivalentes para el compilador, pero `NULL` **dice que es un puntero**. Escribir `return (0);` en una función que devuelve `char *` funciona y confunde. Usa `NULL`, definido en `<stddef.h>`.

---

## 5. El contrato de una función

### Tu decisión

En `ft_strlen` planteaste devolver `-1` si `s` era `NULL`, y decidiste quitarlo por coherencia con la función real. **Fue la decisión correcta**, y por dos motivos:

**Coherencia.** Si tu función se llama como la real, debe comportarse como la real. Inventar un contrato distinto para un nombre conocido es peor que no proteger.

**El `-1` era activamente dañino.** El tercer parámetro de `write` es `size_t`. Ese `-1` se convertiría en 18 trillones.

### La filosofía de C

**El que llama garantiza los datos.** La función no paga el coste de comprobarlo en cada invocación.

Es un compromiso deliberado: máxima velocidad a cambio de máxima responsabilidad. Otros lenguajes eligen lo contrario.

Lo aplicaste de forma coherente en las seis funciones: `ft_strcpy` no comprueba el tamaño de `dest`, `ft_strchr` no comprueba `NULL`.

### Contrato incumplido ≠ contrato distinto

Hay una diferencia que apareció en `ft_strcpy`:

- **No comprobar el tamaño de `dest`** → decisión de contrato. Trasladas la responsabilidad
- **No copiar el `'\0'`** → incumplimiento. La función no hace lo que promete

Lo primero es diseño. Lo segundo es un bug.

---

## 6. Buffer overflow

### Qué es

`ft_strcpy` copia hasta encontrar el `'\0'` de `src`. Si `dest` es más pequeño, **sigue escribiendo más allá de su final**.

Esa memoria pertenece a otra cosa: otra variable, o datos de control del programa.

### Por qué es la vulnerabilidad clásica

Si lo que hay justo detrás de `dest` es la **dirección de retorno** de la función, un atacante que controle el contenido de `src` puede sobrescribirla y **redirigir la ejecución** a código de su elección.

Es el mecanismo del gusano Morris (1988) y de miles de vulnerabilidades desde entonces.

### Por qué existe `strncpy`

Precisamente para limitar cuánto se escribe. Pero **no es la versión segura de `strcpy`**, y eso lo descubriste implementándola.

---

## 7. La trampa de `strncpy`

### Lo que implementaste

```c
while (i < n && src[i])   /* copia, con tope */
    ...
while (i < n)             /* rellena lo que sobre */
    dest[i] = '\0';
```

Los dos bucles son simétricos: misma variable, misma cota, distinto contenido. El segundo continúa donde paró el primero.

### El resultado sin terminador

```
src corta (abc, 6):    [abc___]     ← rellena con '\0'
src justa (abc, 3):    [abcX]       ← NO hay '\0'
src larga (abcdef, 3): [abcX]       ← NO hay '\0'
```

Si `src` mide `n` o más, las `n` posiciones se llenan de caracteres y **no queda sitio para el terminador**.

**Eso es correcto.** Es lo que hace la función real.

### Por qué es peligroso

```c
char buf[3];
strncpy(buf, "abcdef", 3);   /* 'a','b','c' — sin terminador */
printf("%s", buf);            /* lee hasta encontrar un cero por ahí */
```

Al pasarle esa cadena a `ft_strlen`, seguiría leyendo más allá del buffer: número absurdo o `Segmentation fault`. Y si esos bytes contenían datos sensibles, acaban impresos.

**Mucha gente cree que `strncpy` es la versión segura de `strcpy`.** No lo es: cambia un problema (escribir de más) por otro (leer de más).

### El error que cometiste

Tu primera versión usaba `ft_strlen(dest)` para decidir el relleno. Dos problemas:

1. **Escribía fuera de las `n` posiciones autorizadas** — el relleno no tenía tope
2. **Llamaba a `ft_strlen` sobre un destino que aún no era una cadena válida** — leer memoria arbitraria

La solución usa solo `i` y `n`: información que ya tenías, sin mirar el contenido.

> **Lección general:** cuando una función recibe un límite, ese límite es la única fuente de verdad. No deduzcas el estado desde el contenido de un buffer a medio escribir.

---

## 8. Lo que garantiza el estándar

### `strcmp` solo garantiza el signo

```
("abc","ab")  tuyo = 99     real = 99
```

El estándar dice: negativo, cero o positivo. **No dice qué número.** Una implementación puede devolver la diferencia de caracteres, o normalizar a −1/0/1.

**Nunca escribas `if (ft_strcmp(a, b) == 1)`.** Se compara con cero:

```c
if (ft_strcmp(a, b) == 0)   /* iguales */
if (ft_strcmp(a, b) < 0)    /* a va antes */
```

### Por qué se especifica así

Dejar libertad permite implementaciones más rápidas. Si el estándar exigiera exactamente −1, 0 o 1, cada comparación necesitaría normalizar el resultado.

Es un patrón general en C: **se especifica lo mínimo** para dejar margen de optimización. Lo que no está especificado, no se puede asumir.

---

## 9. Prototipos y por qué existen los `.h`

### El problema que te encontraste

Cambiaste `ft_strlen` a `size_t`, pero otros ficheros seguían declarando `int ft_strlen(char *s);`.

Comprobado:

```c
/* def.c */   size_t f(void) { return 42; }
/* use.c */   int f(void);              ← MIENTE
```

```
$ gcc -Wall -Wextra -Werror def.c use.c -o mix
$                                    ← compila sin un solo aviso
```

### Por qué no lo detecta

**Cada `.c` se compila por separado.** Al compilar `use.c`, el compilador no tiene ni idea de qué hay en `def.c`: se cree el prototipo que le das.

El enlazador junta los `.o` después, y **solo empareja nombres, no tipos**.

Aquí funcionaba por casualidad —el valor cabía y la convención de llamada coincidía— pero es comportamiento indefinido.

### La solución

Los ficheros **`.h`**. La declaración vive en **un solo sitio**, y todos los `.c` la incluyen. Si cambias el tipo, cambias una línea y todos se enteran.

Es lo que verás en el proyecto 02, donde varias funciones se llaman entre sí.

### Incluir lo mínimo

Usaste `<stdio.h>` para conseguir `size_t`. Funciona porque lo trae de rebote, pero:

- La cabecera correcta es **`<stddef.h>`**
- `<stdio.h>` mete `printf`, `fopen`, `scanf`... — las funciones que el proyecto prohíbe

**Incluye la cabecera mínima que necesitas**, no una grande que "ya lo trae todo".

---

## Resumen

- Una cadena es **bytes + una marca al final**. Sin longitud guardada
- **`size_t` para cantidades, `int` para lo que puede ser negativo**
- **`char` tiene signo** en x86 → `unsigned char` cuando el signo importa
- Un puntero devuelto **apunta a memoria ajena** y muere con ella
- El contrato lo define quien escribe la función; **C confía en el que llama**
- **`strncpy` no es la versión segura de `strcpy`**: puede dejar cadenas sin terminador
- El estándar **especifica lo mínimo**; lo demás no se puede asumir
- Los prototipos incoherentes **no los detecta el compilador** → para eso están los `.h`

---

[← Volver al enunciado](SUBJECT.md) · [Al camino](../README.md)
