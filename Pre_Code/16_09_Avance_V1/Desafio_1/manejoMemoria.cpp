#include "manejoMemoria.h"

const int FILAS = 0;
const int COLUMNAS = 1;
const int BYTESRESERVADOS = 2;

unsigned char* inicializarTablero(int *estadoJuego){
    int filas = estadoJuego[FILAS];
    int columnas = estadoJuego[COLUMNAS];

    int bitsTotales = 3 * filas * columnas;
    int bytesNecesitados = (bitsTotales + 7) / 8;

    unsigned char* tablero = new unsigned char[bytesNecesitados]();

    estadoJuego[BYTESRESERVADOS] = bytesNecesitados;

    return tablero;

}