# ft_string

**Proyecto 01** · Medir, copiar y comparar cadenas a mano

---

## Objetivo

Escribir tú mismo las funciones de cadenas que trae C. Al terminar sabrás exactamente qué hace `strlen` por dentro, y por qué copiar una cadena es más delicado de lo que parece.

Estas funciones se usan en los nueve proyectos siguientes.

---

## Por qué así

En el proyecto anterior descubriste que una cadena termina en `'\0'`. Eso te permite **recorrerla**, pero no basta para casi nada más:

- Para copiarla necesitas saber **cuánto ocupa**
- Para reservarle memoria, lo mismo
- Para escribirla de un solo `write`, también

`ft_putstr` hacía una llamada a `write` por cada carácter. Con la longitud, bastaría **una sola** para toda la cadena. Es la diferencia entre 20 llamadas al sistema y 1.

---

## Funciones permitidas

```
write
```

Igual que antes. Nada de la librería de cadenas: es justo lo que estás construyendo.

---

## Parte obligatoria

### 1. `ft_strlen`

```c
int	ft_strlen(char *s);
```

Devuelve el número de caracteres de la cadena, **sin contar** el `'\0'`.

`ft_strlen("Karamoon")` → `8`

### 2. `ft_putstr_fd`

```c
void	ft_putstr_fd(char *s, int fd);
```

Escribe la cadena en el descriptor indicado, **con una sola llamada a `write`**.

Aquí ves para qué servía `ft_strlen`. Y el `fd` te permite escribir en la salida de error (2) además de en la pantalla (1).

### 3. `ft_strcpy`

```c
char	*ft_strcpy(char *dest, char *src);
```

Copia `src` dentro de `dest`, **incluyendo el `'\0'`**. Devuelve `dest`.

⚠️ Esta función no comprueba nada. Si `dest` es más pequeño que `src`, escribes fuera de su sitio. Piensa en quién es responsable de que eso no pase.

### 4. `ft_strncpy`

```c
char	*ft_strncpy(char *dest, char *src, int n);
```

Copia como mucho `n` caracteres. Si `src` es más corta, rellena el resto con `'\0'` hasta completar `n`.

⚠️ Trampa: si `src` mide `n` o más, **el resultado no lleva `'\0'` al final**. Así es la función real, y es una fuente conocida de bugs. Reprodúcelo tal cual y entiende por qué es peligroso.

### 5. `ft_strcmp`

```c
int	ft_strcmp(char *s1, char *s2);
```

Compara dos cadenas. Devuelve:
- `0` si son iguales
- un número **negativo** si `s1` va antes que `s2`
- un número **positivo** si `s1` va después

⚠️ El estándar **solo garantiza el signo**, no el valor. Tu `ft_strcmp("abc", "ab")` puede devolver 99 mientras el real devuelve 1: las dos son correctas. Nunca compares el resultado con `== 1`.

### 6. `ft_strchr`

```c
char	*ft_strchr(char *s, int c);
```

Busca el carácter `c` en la cadena. Devuelve un **puntero a la primera aparición**, o `NULL` si no está.

⚠️ Dos detalles: el parámetro es `int` pero se compara como `char`. Y si buscas `'\0'`, debe encontrarlo al final de la cadena.

---

## Entrega

```
01-ft_string/
├── Makefile
├── src/
│   ├── ft_strlen.c
│   ├── ft_putstr_fd.c
│   ├── ft_strcpy.c
│   ├── ft_strncpy.c
│   ├── ft_strcmp.c
│   └── ft_strchr.c
└── tests/
    └── main.c
```

Compilación con `-Wall -Wextra -Werror`. Makefile con `all`, `clean`, `fclean`, `re`.

---

## Normas de escritura

Las mismas del proyecto 00:

- Máximo 25 líneas por función
- **Tabuladores**, no espacios *(en el 00 mezclaste ambos — cuida esto)*
- Llaves en su propia línea
- Declaraciones al principio, separadas por una línea en blanco
- Solo `while`, nada de `for`
- Sin variables globales

**Novedad:** puedes usar la sintaxis de índice (`s[i]`) o la de puntero (`*s`, `s++`). Elige una **y sé coherente dentro de cada función**.

---

## Bonus

Solo con la parte obligatoria perfecta.

- `ft_strdup(char *s)` — devuelve una copia de la cadena en memoria nueva. Necesitarás `malloc`, que es el proyecto 02. Si lo intentas, ten claro quién libera esa memoria.

---

## Cómo se evalúa

| Criterio | |
|---|---|
| Compila con `-Wall -Wextra -Werror`, sin avisos | ⬜ |
| Makefile con `all`, `clean`, `fclean`, `re` | ⬜ |
| `ft_strlen` correcta, incluida la cadena vacía | ⬜ |
| **`ft_putstr_fd` usa UN solo `write`** | ⬜ |
| `ft_strcpy` copia el `'\0'` y devuelve `dest` | ⬜ |
| `ft_strncpy` rellena con `'\0'` cuando sobra espacio | ⬜ |
| **`ft_strncpy` NO añade `'\0'` cuando `src` mide `n` o más** | ⬜ |
| `ft_strcmp` devuelve el signo correcto en los tres casos | ⬜ |
| `ft_strchr` encuentra el carácter y devuelve puntero | ⬜ |
| **`ft_strchr` encuentra `'\0'`** | ⬜ |
| `ft_strchr` devuelve `NULL` si no lo encuentra | ⬜ |
| Ninguna función prohibida | ⬜ |
| Normas de escritura | ⬜ |
| **Preguntas de defensa respondidas** | ⬜ |

---

## Defensa

Sin mirar el código.

1. ¿Por qué `ft_putstr_fd` con un solo `write` es mejor que el `ft_putstr` del proyecto 00? ¿Qué se ahorra exactamente?

2. `ft_strcpy` no comprueba si `dest` tiene sitio. ¿Qué pasa si no lo tiene? ¿Quién es responsable?

3. ¿Por qué `ft_strcmp` puede devolver 99 en vez de 1 y seguir siendo correcta?

4. En `ft_strcmp`, ¿por qué conviene convertir a `unsigned char` antes de restar? *(Pista: ¿qué pasa si una cadena tiene un carácter con código mayor que 127?)*

5. `ft_strchr` devuelve un puntero **dentro de la cadena original**, no una copia. ¿Qué implicaciones tiene eso para quien la use?

6. ¿Por qué `ft_strncpy` puede dejar una cadena sin `'\0'`? ¿Qué pasa si luego se la pasas a `ft_strlen`?

---

## Pistas

<details><summary>ft_strlen</summary>

Recorre hasta el `'\0'` contando. Es `ft_putstr` sin imprimir.

Una cadena vacía `""` mide 0: el primer carácter ya es `'\0'`.
</details>

<details><summary>ft_putstr_fd con un solo write</summary>

`write` necesita tres cosas: dónde, desde qué dirección, y cuántos bytes.

Ya tienes las tres. La dirección es la cadena misma — un `char *` **ya es** una dirección, así que aquí no hace falta `&`.
</details>

<details><summary>ft_strncpy: el relleno</summary>

Son dos fases. Primero copias mientras queden caracteres en `src` **y** no hayas llegado a `n`. Después, si te sobran posiciones hasta `n`, las rellenas con `'\0'`.

Dos bucles seguidos, compartiendo el mismo índice.
</details>

<details><summary>ft_strcmp: cuándo parar</summary>

Avanzas mientras los caracteres sean **iguales** y no hayas llegado al final.

Cuando el bucle para, la respuesta es la diferencia entre los dos caracteres de esa posición. Si las cadenas eran idénticas, ambos serán `'\0'` y la resta dará 0 sola — no hace falta ningún caso especial.
</details>

<details><summary>ft_strchr: el caso del '\0'</summary>

El bucle normal se detiene **en** el `'\0'`, sin comprobarlo. Así que si alguien busca `'\0'`, tu bucle termina sin haberlo comparado.

Hace falta una comprobación después del bucle.
</details>

---

## Cuando termines

El proyecto 02 es **`ft_memory`**: `malloc`, `free`, y arrays que crecen.

Ahí `ft_strdup` deja de ser bonus y se vuelve obligatoria — porque para copiar una cadena a memoria nueva hay que pedirla primero, y hay que saber cuánta. Con `ft_strlen` ya tienes esa mitad resuelta.

---

📖 **[Teoría de este proyecto](THEORY.md)** — lo que apareció durante el desarrollo, ordenado.

[← Volver al camino](../README.md) · [Proyecto anterior](../00-ft_hello/SUBJECT.md)
