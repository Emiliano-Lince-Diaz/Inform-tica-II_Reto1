#ifndef LOGICAJUEGO_H
#define LOGICAJUEGO_H

// Inicializa el reloj interno para que los números sean realmente aleatorios cada partida
void inicializarSemillaAleatoria();

// Recorre el tablero llenando los vacíos sin crear combinaciones
void generarFichasAleatorias(unsigned char* tablero, int filas, int columnas);

void eliminarFicha(unsigned char* tablero, int* estadoJuego);

void gravedad(unsigned char* tablero, int* estadoJuego);

void rellenar(unsigned char* tablero, int* estadoJuego);

#endif // LOGICAJUEGO_H