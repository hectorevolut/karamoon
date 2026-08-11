# Karamoon

Aprender C construyendo. Once miniproyectos que terminan en un juego.

Cada proyecto es **una unidad cerrada**: su enunciado, su código, su Makefile y su defensa. Se empieza, se termina, se defiende, se pasa al siguiente.

---

## El camino

| # | Proyecto | Qué construyes | Estado |
|---|---|---|---|
| [**00**](00-ft_hello/) | `ft_hello` | Escribir en pantalla sin `printf` | ✅ Defendido · [teoría](00-ft_hello/THEORY.md) |
| [**01**](01-ft_string/) | `ft_string` | Medir, copiar y comparar cadenas a mano | ✅ Defendido · [teoría](01-ft_string/THEORY.md) |
| 02 | `ft_memory` | Memoria dinámica y arrays que crecen | 🟡 Siguiente |
| 03 | `ft_canvas` | Un lienzo en memoria y una **imagen en disco** | 🔒 |
| 04 | `ft_draw` | Líneas, rectángulos, círculos | 🔒 |
| 05 | `ft_window` | Tu lienzo en una ventana de verdad | 🔒 |
| 06 | `ft_input` | Teclado: mover algo por la pantalla | 🔒 |
| 07 | `ft_sprites` | Dibujar personajes | 🔒 |
| 08 | `ft_world` | Mapas, scroll y colisiones | 🔒 |
| 09 | `ft_engine` | Entidades, estados, bucle de juego | 🔒 |
| 10 | `beast` | **El juego** | 🔒 |

Un proyecto se desbloquea cuando el anterior está **defendido**, no solo compilado.

---

## Reglas del camino

**1. Todo en C.** Sin excepciones, aunque cueste más.

**2. Compila con estas flags o no cuenta:**
```
-Wall -Wextra -Werror
```

**3. Funciones permitidas.** Cada proyecto lista las suyas. Si no está en la lista, se escribe a mano. Es el punto: entender qué hay debajo.

**4. Se defiende.** Cada proyecto tiene preguntas al final. Si no se responden sin mirar el código, el proyecto no está terminado — aunque funcione.

**5. Un proyecto, una carpeta.** Nada se mezcla.

---

## Estructura de un proyecto

```
NN-nombre/
├── SUBJECT.md     ← qué hay que hacer y cómo se evalúa
├── THEORY.md      ← la teoría que salió, escrita AL TERMINAR
├── Makefile
├── src/           ← tu código
└── tests/         ← programas para probarlo
```

**El `THEORY.md` se escribe después de defender el proyecto**, no antes. Recoge lo que apareció mientras escribías el código: los conceptos que tocaste, los errores que cometiste y por qué ocurrían.

No es material de estudio previo. Es consolidación de lo ya vivido.

---

## Empezar

```bash
cd 00-ft_hello
cat SUBJECT.md
```

El destino es un juego inspirado en *Shadow of the Beast* (Psygnosis, 1989). Karamoon es su mundo.
