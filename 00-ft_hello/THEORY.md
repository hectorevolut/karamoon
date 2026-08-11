# Teoría — ft_hello

Lo que apareció durante el proyecto 00, ordenado. **Todo esto lo has tocado ya con las manos**: cada apartado se refiere a algo que escribiste, rompiste o defendiste.

---

## 1. `write` y las llamadas al sistema

### Qué es realmente

Tu programa **no puede escribir en la pantalla**. No tiene permiso. Escribir en un terminal, en un fichero o en la red son operaciones del hardware, y el hardware lo controla el **kernel** — el núcleo del sistema operativo.

La única forma de pedirle algo al kernel es una **llamada al sistema** (*syscall*). `write` es una de ellas.

Cuando ejecutas `write(1, &c, 1)`:

1. Tu programa coloca los argumentos en unos registros de la CPU
2. Ejecuta una instrucción especial que **cambia el nivel de privilegio** del procesador
3. El kernel toma el control, comprueba que puedes hacer eso, y escribe
4. Devuelve el control a tu programa

Ese cambio de privilegio no es gratis: cuesta del orden de **cientos de ciclos** de CPU, frente a los pocos que cuesta una llamada a función normal.

### Por qué importó en el proyecto 01

Tu `ft_putstr` del proyecto 00 llamaba a `write` **una vez por carácter**. Para `"Karamoon\n"` son 9 syscalls.

`ft_putstr_fd` del proyecto 01 lo hace con **una sola**. Mismo resultado, una novena parte del coste.

Esa es la razón de que `printf` tenga un buffer interno: acumula texto y llama a `write` lo menos posible.

### `printf` no es una syscall

`printf` es una función de librería que vive en tu proceso. Formatea el texto, lo guarda en un buffer, y **cuando toca** llama a `write`. Es un envoltorio.

Por eso este proyecto lo prohibía: para que no quedara nada entre tu código y el kernel.

---

## 2. Descriptores de fichero

### Los tres que siempre existen

El `1` de `write(1, ...)` es un **descriptor de fichero** (*file descriptor*, o `fd`): un número entero que identifica algo abierto por tu proceso.

Todo programa arranca con tres:

| fd | Nombre | Para qué |
|---|---|---|
| 0 | entrada estándar (`stdin`) | De dónde lee |
| 1 | **salida estándar** (`stdout`) | Donde escribe lo normal |
| 2 | salida de error (`stderr`) | Donde escribe los errores |

### Por qué existen dos salidas

Comprobado:

```bash
$ ./programa
esto va al fd 1 (pantalla)
esto va al fd 2 (error)

$ ./programa > out.txt
esto va al fd 2 (error)      ← el error SIGUE en pantalla

$ cat out.txt
esto va al fd 1 (pantalla)   ← solo lo normal fue al fichero
```

**Al redirigir con `>`, el shell cambia a dónde apunta el fd 1. Tu código ni se entera** — sigue escribiendo en el descriptor 1 como siempre.

Y los errores siguen viéndose. Por eso `stderr` existe: para que un mensaje de fallo no se pierda dentro de un fichero de resultados.

> Esto reaparece en `ft_putstr_fd(char *s, int fd)`, donde el descriptor pasa a ser un parámetro y puedes elegir a dónde escribir.

---

## 3. Direcciones de memoria y el `&`

### Por qué `write` no recibe el carácter

```c
write(1, &c, 1);
```

`write` no quiere el valor: quiere **dónde está guardado**. El `&` significa *"la dirección de"*.

El motivo es la firma:

```
write(descriptor, dirección, cuántos_bytes)
```

Está diseñada para escribir **n bytes seguidos a partir de un punto**. Si recibiera valores, ¿cómo le pasarías 500 bytes? Con una dirección le basta saber dónde empiezan y cuántos son.

### Toda variable tiene una dirección

Una variable es un trozo de memoria con nombre. Ese trozo está en algún sitio, y ese sitio tiene un número: su dirección.

- `c` → el **valor** guardado
- `&c` → **dónde** está guardado

En el proyecto 01, `ft_putstr_fd(s, fd)` no lleva `&` porque **`s` ya es una dirección**: un `char *` es, por definición, la dirección del primer carácter.

---

## 4. Los caracteres son números

### ASCII

`char` no es un "tipo texto". Es un **entero pequeño**. Cada carácter tiene un número asignado por la tabla ASCII.

Comprobado:

```
'0' = 48   '1' = 49   '9' = 57      → consecutivos
'A' = 65   'a' = 97                 → diferencia de 32
```

### Por qué `+ '0'` funciona

Los diez dígitos ocupan posiciones **consecutivas**, del 48 al 57. Eso no es casualidad: se diseñó así.

```
7 + '0' = 7 + 48 = 55 = '7'
'7' - '0' = 55 - 48 = 7
```

Funciona en las dos direcciones: número → carácter, y carácter → número.

**Se escribe `'0'` y nunca `48`.** El estándar garantiza que los dígitos son consecutivos, pero no que empiecen en 48. Con `'0'` tu código funciona en cualquier codificación.

---

## 5. El rango de `int` y el desbordamiento

### La cuenta

Un `int` son 32 bits: **4.294.967.296 combinaciones**. Se reparten así:

| | Cantidad |
|---|---|
| Negativos | 2.147.483.648 |
| Cero | 1 |
| Positivos | 2.147.483.647 |

```
INT_MIN = -2147483648
INT_MAX =  2147483647
```

**El rango no es simétrico.** El cero ocupa una plaza del lado positivo, así que hay un negativo más que positivos.

### La trampa de `ft_putnbr`

Comprobado:

```c
int n = INT_MIN;
-n  →  -2147483648      ← sigue siendo negativo
```

`-(-2147483648)` debería dar 2.147.483.648. **Ese número no existe como `int`.** La operación se desborda y devuelve el mismo valor negativo.

Por eso `n *= -1` no funcionaba y tu bucle recibía un negativo cuando esperaba un positivo.

### Las dos soluciones

| | Cómo | Coste |
|---|---|---|
| **Caso especial** (la tuya) | Detectar `INT_MIN` e imprimirlo literal | La cadena está escrita a mano; si `int` cambiara de tamaño, quedaría mal |
| **Tipo mayor** | Copiar a un `long` (8 bytes) y operar ahí | `long` mide distinto en Windows (4 bytes) |

Ninguna es perfecta. Es una decisión de compromiso real.

### Por qué esto importa fuera de aquí

El **desbordamiento de enteros** es una familia entera de vulnerabilidades de seguridad. Un contador que da la vuelta, una comprobación de tamaño que pasa porque el número se desbordó y quedó pequeño. Ha causado fallos en navegadores, sistemas operativos y hasta en el cohete Ariane 5.

---

## 6. Recursión

### Las dos piezas

Una función que se llama a sí misma necesita siempre dos cosas:

1. **Caso base** — cuándo dejar de llamarse
2. **Reducción** — cada llamada trabaja sobre un problema más pequeño

En `ft_putnbr`:

```c
if (n >= 10)
    ft_putnbr(n / 10);   ← reducción: cada vez un dígito menos
number = n % 10 + '0';
ft_putchar(number);      ← el caso base es NO entrar en el if
```

El caso base no es un `return` explícito: es que la condición sea falsa. Con `n < 10` no hay llamada y la cadena se detiene.

### El orden lo es todo

Este fue tu segundo fallo, y es el más instructivo del proyecto:

```c
ft_putchar(number);      ft_putnbr(n / 10);
ft_putnbr(n / 10);       ft_putchar(number);
     ↓                        ↓
    "24"                     "42"
```

Con la recursión **antes** de imprimir, cada llamada espera a que terminen todas las de más adentro. Los dígitos salen de izquierda a derecha porque el más profundo es el primero que llega a su `ft_putchar`.

Con la recursión **después**, cada llamada imprime lo suyo antes de bajar. Sale al revés.

### Cada llamada tiene sus propias variables

Cuando `ft_putnbr(42)` llama a `ft_putnbr(4)`, existen **dos copias** de `n` y de `number` a la vez. La llamada interna no puede tocar las de la externa.

Por eso el `number` de la llamada externa sigue valiendo lo suyo cuando la interna termina.

Y por eso una recursión sin caso base agota la memoria: cada llamada ocupa espacio y nunca se libera. Es lo que te pasó en el primer intento, con el `exit 124`.

---

## 7. Variables sin inicializar

### Lo que descubriste

```c
int edad;
printf("%d", edad);    →  32759
```

**En C, declarar no es inicializar.** Se reserva el espacio y se te entrega con lo que hubiera dentro.

### Por qué salía siempre el mismo número

Lo comprobamos: al llamar a otra función antes, el valor pasaba a ser **444** — literalmente lo que esa función había dejado en esa posición.

**No es aleatorio: es lo que había antes.** Como el arranque del programa hace siempre lo mismo, deja siempre los mismos restos.

### Por qué eso es peor que si fuera aleatorio

Si cambiara cada vez, lo detectarías al primer intento. Al salir siempre igual, **el programa parece correcto**. Y entonces:

- Compilas con `-O2` en vez de `-O0` → cambia
- Lo pasas del Mac al Ubuntu → cambia
- Añades una función antes → cambia

"En mi máquina funciona" nace exactamente de aquí.

### Te pasó a ti

En una de las versiones de `ft_putnbr`, `number` se calculaba dentro de un `if` y se imprimía fuera. Con números de un dígito, `number` nunca se asignaba e imprimías basura:

```
7  ->  ␀      (un byte cero invisible)
```

Y `-Wall` lo detectó en cuanto lo compilamos.

> **Regla: inicializa siempre**, aunque vayas a sobrescribir el valor. Las variables **globales** sí valen 0 garantizado, y el motivo se verá más adelante.

---

## 8. Compilar

### Las cuatro etapas

`gcc` no es un programa: es un director de orquesta que llama a cuatro.

| # | Etapa | Qué hace | Flag para parar ahí |
|---|---|---|---|
| 1 | Preprocesador | Pega los `#include`, expande macros | `-E` |
| 2 | Compilador | Traduce C a ensamblador | `-S` |
| 3 | Ensamblador | Ensamblador a código máquina (`.o`) | `-c` |
| 4 | Enlazador | Junta los `.o` y las librerías | *(ninguna)* |

Saber esto sirve para diagnosticar: un `undefined reference` viene de la **etapa 4**, no de la 2. Significa que el código está bien pero falta algo que enlazar.

### Por qué el ejecutable pesa 200 veces más

Tu `hola.c` medía 76 bytes y `hola` casi 16.000.

**No es porque `printf` esté copiado dentro.** Comprobado:

```
$ nm -u hola | grep printf
                 U printf          ← U = undefined, NO está aquí

$ ldd hola
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6
```

`printf` vive en un fichero aparte del sistema y se busca **al ejecutar**.

El tamaño viene de tres cosas:
- Código máquina real (~1,4 KB) — una línea de C son varias instrucciones
- **Código de arranque** que añade el compilador: lo que prepara `argc`/`argv` y llama a tu `main`
- **Símbolos e información de depuración** (`-g`). `strip hola` quita 1,5 KB de golpe

### Las flags

**`-Wall`** — avisos comunes. Pese al nombre, no son todos.

**`-Wextra`** — una segunda capa: parámetros sin usar, comparaciones entre signo y sin signo.

**`-Werror`** — convierte cada aviso en error y **no genera el ejecutable**.

Sin `-Werror` un aviso aparece, el programa compila igual, y sigues adelante. Con quince acumulados dejas de leerlos. Con `-Werror` no puedes avanzar hasta arreglarlo.

Y los avisos de C no son quisquillosidades: en tu propio `ft_putnbr`, el `number` sin inicializar era exactamente lo que `-Wall` señala.

### El truco de revisar una función sola

```bash
gcc -Wall -Wextra -Werror -c ft_putnbr.c -o /dev/null
```

- **`-c`** compila sin enlazar → no necesita `main` ni las demás funciones
- **`-o /dev/null`** tira el resultado → no deja ficheros sueltos

Un segundo, y sabes si hay variables sin inicializar, tipos mal o includes que faltan.

---

## 9. Make

### Qué resuelve

Un Makefile responde a: *"¿qué hay que hacer para construir esto, y cuándo hace falta rehacerlo?"*

```makefile
hello: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o hello
```

```
objetivo: dependencias
	comando
```

### Compara fechas, no contenidos

```bash
$ make
gcc ...
$ make
make: 'hello' is up to date.
```

Make mira la **fecha de modificación** del objetivo y de todas sus dependencias. Si el ejecutable es más reciente que todos los fuentes, no hace nada.

Consecuencia práctica: **`touch fichero.c` fuerza una recompilación** sin haber cambiado nada. Y si las fechas se desajustan, make puede decidir que no hay trabajo cuando sí lo hay — de ahí que exista `make re`.

### El tabulador

La línea del comando lleva **tabulador**, no espacios. Es la causa número uno de Makefiles rotos:

```
Makefile:16: *** missing separator.  Stop.
```

### Las cuatro reglas estándar

| Regla | Qué hace |
|---|---|
| `all` | Construye todo (objetivo por defecto) |
| `clean` | Borra los intermedios (`.o`) |
| `fclean` | `clean` + borra el ejecutable |
| `re` | `fclean` + `all` — reconstrucción total |

`.PHONY` marca las reglas que **no producen un fichero con ese nombre**. Sin eso, si existiera un fichero llamado `clean`, make pensaría que ya está hecho.

---

## Resumen

Lo que este proyecto deja fijado:

- **`write` es una syscall**; `printf` es un envoltorio con buffer
- Los **descriptores** 0, 1 y 2, y por qué el error va aparte
- **`&` da la dirección**; `write` trabaja con direcciones y cantidades
- **Los caracteres son números** y los dígitos son consecutivos
- El **rango de `int` no es simétrico**, y por eso `INT_MIN` rompe cosas
- La **recursión** necesita caso base, y el orden decide el resultado
- **Declarar no es inicializar**; la basura determinista es más peligrosa que la aleatoria
- **`gcc` son cuatro etapas**; `-Werror` es disciplina, no burocracia
- **Make compara fechas** y necesita tabuladores

---

[← Volver al enunciado](SUBJECT.md) · [Al camino](../README.md)
