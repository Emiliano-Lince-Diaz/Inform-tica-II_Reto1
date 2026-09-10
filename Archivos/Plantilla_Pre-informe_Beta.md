# Plantilla Pre-Informe — Desafío I: Sweet Crush

**Curso:** Informática II, semestre 2026-2
**Elaborado:** 9 de septiembre de 2026
**Propósito:** plan de desarrollo para el codigo del desafio.

**Autores:** Emiliano de Jesus Lince Diaz - Esteban Garces Atehortua

---

# Diseño de la interfaz de usuario

## Para todo menú:

**IMPORTANTE** En todo menú que se abra para el usuario hacer verificación de entrada de datos por el usuario, también poner una opción de ayuda para los comandos validos de entrada del usuario y la opción de Salir del juego.

## Inicio del Juego

### Menú de opciones de inicio del juego

1. **determinar el tamaño del tablero:** Pedir que ingrese cantidad de filas y cantidad de columnas por separado.

### Menú en partida

1. **Eliminar ficha:** Pedir al usuario las coordenadas en posición de la ficha a eliminar en la fila y columna correspondiente de dicha ficha.
2. **Agregar fila:** Pedir al usuario la fila a agregar.
2. **Eliminar fila:** Pedir al usuario la fila a eliminar.
2. **Agregar columna:** Pedir al usuario la columa a agregar.
2. **Eliminar columna:** pedir al usuario la columna a eliminar.

---

# Diseño codificacion de bits

## Representación de las fichas

| Ficha | Representacion bits | Tipo | R.grafica |
|---|---|---|---|
| 1 | 001 | Normal |  |
| 2 | 010 | Normal |  |
| 3 | 011 | Normal |  |
| 4 | 100 | Normal |  |
| 5 | 101 | Normal |  |
| 6 | 110 | Normal |  |
| 7 | 111 | Especial |  |
| 8 | 000 | Especial |  |

**Definición de los estdos especiales:** La ficha 8 que en su representación de bits es "000" representa el estado especial "vacío". La ficha 7 que en su representación de bits es "111" representa el estado especial "Eliminación".

- **Ficha 8:** Definimos que esta ficha va representar el estado "vacío", como una representación de que no hay fichas en esa posición.
- **Ficha 7:** Definimos que esta ficha va representar el estado "Eliminación", como una confirmación de que la ficha en la posición que está recorriendo se debe eliminar.

