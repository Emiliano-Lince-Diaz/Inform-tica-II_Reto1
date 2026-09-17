#ifndef MANEJOMEMORIA_H
#define MANEJOMEMORIA_H

unsigned char* inicializarTablero(int* estadoJuego);

unsigned char* agregarFila(unsigned char* tableroViejo, int* estadoJuego);

unsigned char* eliminarFila(unsigned char* tablero, int* estadoJuego);

unsigned char* agregarColumna(unsigned char* tableroViejo, int* estadoJuego);

unsigned char* eliminarColumna(unsigned char* tablero, int* estadoJuego);

#endif // MANEJOMEMORIA_H
